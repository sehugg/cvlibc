#include "cv_graphics.h"

#include "cv_support.h"

void cv_set_colors(enum cv_color foreground, enum cv_color background)
{
  cv_vdpout(0x07, (foreground << 4) | background);
}
