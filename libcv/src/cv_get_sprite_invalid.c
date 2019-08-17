#include "cv_graphics.h"

#include <stdint.h>

extern volatile uint8_t cv_vdpstat;

bool cv_get_sprite_invalid(uint8_t *sprite)
{
	if(sprite)
		*sprite = cv_vdpstat & 0x1f;
	return(cv_vdpstat & 0x40);
}

