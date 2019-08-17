#include "cv_input.h"

extern volatile void (*cv_spint_handler)(uint_fast8_t, uint_fast8_t);

void cv_set_spint_handler(void (*handler)(uint_fast8_t, uint_fast8_t))
{
__asm
	di
__endasm;
	cv_spint_handler = handler;
	if(handler)
	{		
__asm
	ei
__endasm;
	}
}

