#include "cv_graphics.h"

#include <stdint.h>

extern uint8_t cv_vdpreg[2];

bool cv_get_sprite_big(void)
{
  return(cv_vdpreg[1] & 0x02);
}
