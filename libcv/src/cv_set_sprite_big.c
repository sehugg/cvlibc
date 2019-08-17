#include "cv_graphics.h"

#include "cv_support.h"

extern uint8_t cv_vdpreg[2];

void cv_set_sprite_big(bool status)
{
  cv_vdpout(0x1, cv_vdpreg[1] = (status ? 0x02 : 0x0) | (cv_vdpreg[1] & ~0x02));
}
