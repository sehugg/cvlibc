#include "cv_graphics.h"

#include <stdint.h>

extern uint8_t cv_vdpreg[2];

bool cv_get_external_video(void)
{
  return(cv_vdpreg[0] & 0x02);
}
