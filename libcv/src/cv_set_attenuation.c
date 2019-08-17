#include "cv_sound.h"

#ifndef CV_SMS
static volatile __sfr __at 0xff port;
#else
static volatile __sfr __at 0x7f port;
#endif

void cv_set_attenuation(enum cv_soundchannel channel, uint8_t dezibel)
{
	channel += 1;
	dezibel >>= 1;
	dezibel &= 0xf;
	if(dezibel == 0)
		dezibel = 0xf;
	port = (0x80 | (channel << 4) | dezibel);
}

