#include <string.h>

#include "cv.h"
#include "cvu.h"

#define IMAGE ((const cv_vmemp)0x1c00)

#define NUM_PIECES 6

#ifdef CV_SMS
extern const unsigned char pattern[];
#define LINELENGTH 32
#else
#define LINELENGTH 40
#endif

const char *const titles[NUM_PIECES] = {"Duet 1", "Duet 3", "Duet 4", "Duet 7", "Duet 9", "Duet 10"};
extern const uint16_t duet_1_1[], duet_1_2[], duet_3_1[], duet_3_2[], duet_4_1[], duet_4_2[], duet_7_1[], duet_7_2[], duet_9_1[], duet_9_2[], duet_10_1[], duet_10_2[];
const uint16_t *const voices1[NUM_PIECES] = {duet_1_1, duet_3_1, duet_4_1, duet_7_1, duet_9_1, duet_10_1};
const uint16_t *const voices2[NUM_PIECES] = {duet_1_2, duet_3_2, duet_4_2, duet_7_2, duet_9_2, duet_10_2};

struct cvu_music voice1, voice2;

volatile bool change;

void play(void)
{
	if(change)
		return;
	cvu_play_music(&voice1);
	cvu_play_music(&voice2);
}

void main(void)
{
	uintptr_t a;
	uint_fast8_t i;
	struct cv_controller_state cs;

	// Init screen.
	cv_set_image_table(IMAGE);
	cv_set_colors(CV_COLOR_LIGHT_GREEN, CV_COLOR_BLACK);
#ifndef CV_SMS // Use ColecoVision builtin font
	a = *(int *)(0x6c);
	a -= 0x30 * 8;
	cvu_memtovmemcpy(0x1800, (void *)(a), 2048);
	cv_set_character_pattern_t(0x1800);
	cv_set_screen_mode(CV_SCREENMODE_TEXT);
#else
	cvu_memtovmemcpy(0x0000, pattern, 2048);
	cvu_memtovmemcpy(0x0800, pattern, 2048);
	cvu_memtovmemcpy(0x1000, pattern, 2048);
	cvu_vmemset(0x2000, CV_COLOR_BLACK | (CV_COLOR_LIGHT_GREEN << 4), 6144);
	cv_set_color_table(0x3fff);
	cv_set_character_pattern_t(0x1fff);
	cv_set_screen_mode(CV_SCREENMODE_BITMAP);
#endif

	cvu_vmemset(IMAGE, ' ', 24 * LINELENGTH);
	cvu_memtovmemcpy(IMAGE + 1, "Mozart's horn duets:", 20);
	for(i = 0; i < NUM_PIECES; i++)
	{
#ifndef CV_SMS
		cvu_voutb('1' + i, IMAGE + 3 * LINELENGTH + 2 * LINELENGTH * i + 1);
		cvu_voutb(':', IMAGE + 3 * LINELENGTH + 2 * LINELENGTH * i + 2);
#endif
		cvu_memtovmemcpy(IMAGE + 3 * LINELENGTH + 2 * LINELENGTH * i + 4, titles[i], strlen(titles[i]));
	}
	cv_set_screen_active(true);

	// Init music.
	cvu_init_music(&voice1);
	cvu_init_music(&voice2);

	cv_set_vint_handler(&play);

#ifdef CV_SMS
	i = 0;
#endif

	for(;;)
	{
#ifdef CV_SMS
		cvu_voutb('*', IMAGE + 3 * LINELENGTH + 2 * LINELENGTH * i + 2);
#endif
		do
		{
			cv_get_controller_state(&cs, 0);
#ifndef CV_SMS
		}
		while(cs.keypad < 1 || cs.keypad > NUM_PIECES);
#else
			if(cs.joystick & CV_FIRE_1)
			{
				cvu_voutb(' ', IMAGE + 3 * LINELENGTH + 2 * LINELENGTH * i + 2);
				do
					cv_get_controller_state(&cs, 0);
				while(cs.joystick & CV_FIRE_1);
				i++;
				if(i >= NUM_PIECES)
					i = 0;
				cvu_voutb('*', IMAGE + 3 * LINELENGTH + 2 * LINELENGTH * i + 2);
			}
		}
		while(!(cs.joystick & CV_FIRE_0));
#endif

		change = true;
		cvu_init_music(&voice1);
		cvu_init_music(&voice2);
		voice1.channel = CV_SOUNDCHANNEL_0;
		voice2.channel = CV_SOUNDCHANNEL_1;
		voice1.sixteenth_notes_per_second = 5;
		voice2.sixteenth_notes_per_second = 5;
#ifndef CV_SMS
		voice1.notes = voices1[cs.keypad - 1];
		voice2.notes = voices2[cs.keypad - 1];
#else
		voice1.notes = voices1[i];
		voice2.notes = voices2[i];
#endif
		change = false;
	}
}

