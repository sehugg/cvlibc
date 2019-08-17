#include "cv.h"
#include "cvu_graphics.h"

// Replaced by assembler code.
int cvu_get_sprite_x(const struct cvu_sprite *sprite) __preserves_regs(b, c, d, e)
{
	if(sprite->tag & 0x80)
		return((int)(sprite->x) - 32);
	return(sprite->x);
}
