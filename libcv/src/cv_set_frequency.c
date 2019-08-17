#include "cv_sound.h"

#ifndef CV_SMS
static volatile __sfr __at 0xff port;
#else
static volatile __sfr __at 0x7f port;
#endif

void cv_set_frequency(enum cv_soundchannel channel, uint16_t frequency_divider)
{
	frequency_divider = frequency_divider >> 5;
	port = (0x80 | (channel << 4) | (frequency_divider & 0xf));
	port = (frequency_divider >> 4);
}
