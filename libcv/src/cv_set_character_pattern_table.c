#include "cv_graphics.h"

#include "cv_support.h"

void cv_set_character_pattern_t(cv_vmemp loc)
{
  cv_vdpout(0x4, loc >> 11);
}
