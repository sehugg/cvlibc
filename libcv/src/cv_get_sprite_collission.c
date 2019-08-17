#include "cv_graphics.h"

#include <stdint.h>

extern volatile uint8_t cv_vdpstat;

bool cv_get_sprite_collission(void)
{
  return(cv_vdpstat & 0x20);
}

