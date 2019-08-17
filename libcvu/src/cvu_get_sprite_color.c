#include "cv.h"
#include "cvu_graphics.h"

enum cv_color cvu_get_sprite_color(const struct cvu_sprite *sprite)
{
	return(sprite->tag & 0xf);
}
