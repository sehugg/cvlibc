#include "cv_input.h"

extern volatile void (*cv_vint_handler)(void);

void cv_set_vint_handler(void (*handler)(void))
{
__asm
	di
__endasm;
	cv_vint_handler = handler;
__asm
	ei
__endasm;
}

