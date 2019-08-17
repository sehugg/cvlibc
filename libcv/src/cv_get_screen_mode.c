#include "cv_graphics.h"

#include <stdint.h>

extern uint8_t cv_vdpreg[2];

enum cv_screenmode cv_get_screen_mode(void)
{
  return((cv_vdpreg[0] & 0x06) | (cv_vdpreg[1] & 0x18));
}

