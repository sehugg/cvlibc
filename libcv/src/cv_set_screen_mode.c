#include "cv_graphics.h"

#include "cv_support.h"

extern uint8_t cv_vdpreg[2];

void cv_set_screen_mode(enum cv_screenmode mode)
{
  cv_vdpout(0x0, cv_vdpreg[0] = (mode & 0x06) | (cv_vdpreg[0] & ~0x06));
  cv_vdpout(0x1, cv_vdpreg[1] = (mode & 0x18) | (cv_vdpreg[1] & ~0x18));
}

