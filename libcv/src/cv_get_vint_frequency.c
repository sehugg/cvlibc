#include <stdint.h>

#ifndef CV_SMS
static uint8_t __at 0x69 cv_vint_frequency;
#else
extern extern uint8_t cv_machine_config;
#endif

unsigned char cv_get_vint_frequency(void)
{
#ifndef CV_SMS
	return(cv_vint_frequency);
#else
	return(cv_machine_config & 0x03f);
#endif
}

