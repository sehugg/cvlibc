#include "cvu_graphics.h"

#include "cv_graphics.h"

extern void cv_vmemset_fast(int c, size_t n);
extern void cv_vmemset_slow(int c, size_t n);

void cvu_vmemset(cv_vmemp dest, int c, size_t n)
{
	cv_set_write_vram_address(dest);
	if(cv_get_screen_active() &&
		cv_get_screen_mode() != CV_SCREENMODE_TEXT &&
		cv_get_screen_mode() != CV_SCREENMODE_MULTICOLOR)
		cv_vmemset_slow(c, n);
	else
		cv_vmemset_fast(c, n);
}

