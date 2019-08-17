#include "cv.h"
#include "cvu_sound.h"

extern const uint16_t notes[];

struct cvu_music music;

void play(void)
{
	cvu_play_music(&music);
}

void main(void)
{
	cvu_init_music(&music);
	music.notes = notes;
	cv_set_vint_handler(&play);
	cv_set_colors(CV_COLOR_BLACK, CV_COLOR_BLACK);
	cv_set_screen_active(true);
	for(;;);
}

