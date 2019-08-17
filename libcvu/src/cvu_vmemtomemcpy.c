#include "cvu_graphics.h"

#include "cv_graphics.h"

extern void cv_vmemtomemcpy_fast(void *dest, size_t n);
extern void cv_vmemtomemcpy_slow(void *dest, size_t n);

void cvu_vmemtomemcpy(void *dest, cv_vmemp src, size_t n)
{
	cv_set_read_vram_address(src);
	if(cv_get_screen_active() &&
		cv_get_screen_mode() != CV_SCREENMODE_TEXT &&
		cv_get_screen_mode() != CV_SCREENMODE_MULTICOLOR)
		cv_vmemtomemcpy_slow(dest, n);
	else
		cv_vmemtomemcpy_fast(dest, n);
}

