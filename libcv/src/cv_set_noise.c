#include "cv_sound.h"

#ifndef CV_SMS
static volatile __sfr __at 0xff port;
#else
static volatile __sfr __at 0x7f port;
#endif

void cv_set_noise(bool white, enum cv_shift shift)
{
	uint8_t n = 0xe0;
	if(white)
		n |= 0x04;
	n |= shift;
	port = n;
}
