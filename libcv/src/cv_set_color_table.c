#include "cv_graphics.h"

#include "cv_support.h"

void cv_set_color_table(cv_vmemp loc)
{
  cv_vdpout(0x3, loc >> 6);
}
