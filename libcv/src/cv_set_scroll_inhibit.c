#include "cv_graphics.h"

#include "cv_support.h"

extern uint8_t cv_vdpreg[2];

void cv_set_scroll_inhibit(enum cv_scroll_inhibit inhibit)
{
	cv_vdpout(0x0, cv_vdpreg[0] = inhibit | (cv_vdpreg[0] & ~0xc0));
}

