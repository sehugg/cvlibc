#include "cv_graphics.h"

#include "cv_support.h"

void cv_set_image_table(cv_vmemp loc)
{
	cv_vdpout(0x2, loc >> 10);
}

