#include "cv_graphics.h"

#include <stdint.h>

#include "cv_support.h"

extern uint8_t cv_vdpreg[2];

void cv_set_external_video(bool status)
{
  cv_vdpout(0x0, cv_vdpreg[0] = status | (cv_vdpreg[0] & ~0x01));
}
