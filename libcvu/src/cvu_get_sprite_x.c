#include "cv.h"
#include "cvu_graphics.h"

// Replaced by assembler code.
int cvu_get_sprite_x(const struct cvu_sprite *sprite)
{
	if(sprite->tag & 0x80)
		return((int)(sprite->x) - 32);
	return(sprite->x);
}
