#include <stdint.h>

extern volatile void (*cv_vint_handler)(void);
extern volatile uint8_t cv_vdpstat;
extern volatile uint8_t cv_vint_indicator;

#ifdef CV_MSX
static volatile __sfr __at 0x99 port;
#else
static volatile __sfr __at 0xbf port;
#endif

void cv_vint(void)
{
	cv_vint_indicator = 0xff;
	cv_vdpstat = port;
	if(cv_vint_handler) (*cv_vint_handler)();
}

