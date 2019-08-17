#include "cv_input.h"

#ifndef CV_SMS

static const uint8_t keytable[16] = {0xf, 8, 4, 5, 0xf, 7, 0xb, 2, 0xf, 0xa, 0, 9, 3, 1, 6, 0xf};	// sdcc can't put local constants into ROM.

static volatile __sfr __at 0xfc port0;
static volatile __sfr __at 0xff port1;
static volatile __sfr __at 0x80 port2;
static volatile __sfr __at 0xc0 port3;

void cv_get_controller_state(struct cv_controller_state *state, uint_fast8_t controller)
{
	uint8_t key, joy;

	port2 = 42; // The meaning of life, the universe and everything. Read the keypad.

	key = controller ? port1 : port0;
	state->keypad = keytable[key & 0xf];  // Decode key
  
	port3 = 42; // The meaning of life, the universe and everything. Read the joystick.

	joy = ~(controller ? port1 : port0);
  	if(!(key & 0x40))
		joy |= CV_FIRE_1;
	else
		joy &= ~CV_FIRE_1;
	if((key & 0xf) == 8)
		joy |= CV_FIRE_2;
	else
		joy &= ~CV_FIRE_2;
	if((key & 0xf) == 4)
		joy |= CV_FIRE_3;
	else
		joy &= ~CV_FIRE_3;

  	state->joystick = joy;
}

#else

static volatile __sfr __at 0xdc port0;
static volatile __sfr __at 0xdd port1;

void cv_get_controller_state(struct cv_controller_state *state, uint_fast8_t controller)
{
	uint8_t joy = ~(!controller ? port0 : ((port0 >> 6) | (port1 << 2)));
	state->joystick = joy & 0x3f;
}

#endif

