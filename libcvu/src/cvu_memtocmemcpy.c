#include "cvu_graphics.h"

#include "cv_graphics.h"

extern void cv_memtovmemcpy_fast(const void *src, size_t n);
extern void cv_memtovmemcpy_slow(const void *src, size_t n);

void cvu_memtocmemcpy(cv_cmemp dest, const void *src, size_t n)
{
	cv_set_write_cram_address(dest);
	if(cv_get_screen_active() &&
		cv_get_screen_mode() != CV_SCREENMODE_TEXT &&
		cv_get_screen_mode() != CV_SCREENMODE_MULTICOLOR)
		cv_memtovmemcpy_slow(src, n);
	else
		cv_memtovmemcpy_fast(src, n);
}

