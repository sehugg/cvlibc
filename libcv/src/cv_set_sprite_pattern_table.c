#include "cv_graphics.h"

#include "cv_support.h"

void cv_set_sprite_pattern_table(cv_vmemp loc)
{
  cv_vdpout(0x6, loc >> 11);
}
