#include "cv_support.h"
#include "cv_sound.h"
#include "cv.h"

// Initialize the Colecovision library

volatile void (*cv_vint_handler)(void) = 0;
volatile void (*cv_spint_handler)(uint_fast8_t, uint_fast8_t);
volatile uint8_t cv_vdpstat;
volatile uint8_t cv_vint_indicator;
uint8_t cv_vdpreg[2];

#ifdef CV_SMS
extern uint8_t cv_machine_config;

static void cv_set_vint_bit(void)
{
	cv_machine_config |= 1;
}

void cv_find_vint_frequency(void)
{
	cv_set_vint_handler(&cv_set_vint_bit);
	cv_set_screen_active(true);
__asm;
	ld	de, #0
	ld	hl, #_cv_machine_config
	res	0, (hl)
wait1:
	bit 0, (hl)
	jr	z, wait1
	res	0, (hl)
wait2:
	inc	de
	bit 0, (hl)
	jr	z, wait2
	ld	a, #8
	cp	a, d
	jr	c, pal
ntsc:
	ld	a, #60
	jr cont
pal:
	ld	a, #50
cont:
	or	a, (hl)
	ld	(hl), a
__endasm;
	cv_set_screen_active(false);
	cv_set_vint_handler(0);
	cv_machine_config &= ~1;
}
#endif

void cv_init(void)
{
	// 16 KB of memory, NMI enabled.
	cv_vdpreg[1] = 0xa0;

	// Turn off sound.
	cv_set_attenuation(CV_SOUNDCHANNEL_0, 0);
	cv_set_attenuation(CV_SOUNDCHANNEL_1, 0);
	cv_set_attenuation(CV_SOUNDCHANNEL_2, 0);
	cv_set_attenuation(CV_SOUNDCHANNEL_NOISE, 0);

#ifdef CV_SMS

	// Find the vint frequency experimentally
	cv_find_vint_frequency();
#endif
}

