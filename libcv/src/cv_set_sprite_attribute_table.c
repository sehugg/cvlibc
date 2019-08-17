#include "cv_graphics.h"

#include "cv_support.h"

void cv_set_sprite_attribute_table(cv_vmemp loc)
{
  cv_vdpout(0x5, loc >> 7);
}
