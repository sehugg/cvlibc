#include "cv_graphics.h"

#include "cv_support.h"

void cv_set_vscroll(uint8_t offset)
{
	cv_vdpout(0x9, offset);
}

