#include "cv.h"
#include "cvu_graphics.h"

// Replaced by assembler code.
int cvu_get_sprite_y(const struct cvu_sprite *sprite)
{
	if(sprite->y > 255 - 32)
		return((int)(sprite->y) - 256);
	return(sprite->y);
}

