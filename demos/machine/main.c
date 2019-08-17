#include <string.h>

#include "cv.h"
#include "cvu.h"

#define IMAGE ((const cv_vmemp)0x1c00)

#ifdef CV_SMS
extern const unsigned char pattern[];
#define LINELENGTH 32
#else
#define LINELENGTH 40
#endif

void print(const cv_vmemp loc, const char *s)
{
	cvu_memtovmemcpy(loc, s, strlen(s));
}

volatile char vc;

void main(void)
{
	uintptr_t a;
	uint_fast8_t i;

for(unsigned int i = 0; i < 60000; i++)
  vc++;

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
	print(IMAGE + 1, "This machines seems to be a:");

	switch(cv_get_machine())
	{
#ifndef CV_SMS
	case CV_COLECOVISION:
		print(IMAGE + LINELENGTH + 1, "ColecoVision");
		break;
#else
	case CV_SG1000:
		print(IMAGE + LINELENGTH + 1, "Sega SG-1000");
		break;
	case CV_SC3000:
		print(IMAGE + LINELENGTH + 1, "Sega SC-3000");
		break;
	case CV_MARKIII:
		print(IMAGE + LINELENGTH + 1, "Sega Mark III or Master System");
		break;
#endif
	default:
		print(IMAGE + 1, "Unknown machine");
	}

	print(IMAGE + 3 * LINELENGTH + 1, "Vertical retrace frequencyy:");
	switch(cv_get_vint_frequency())
	{
	case 50:
		print(IMAGE + 4 * LINELENGTH + 1, "50 Hz (PAL or SECAM)");
		break;
	case 60:
		print(IMAGE + 4 * LINELENGTH + 1, "60 Hz (NTSC)");
		break;
	default:
		print(IMAGE + 4 * LINELENGTH + 1, "Unknown");
	}

	cv_set_screen_active(true);

	for(;;);
}

