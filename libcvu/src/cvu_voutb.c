#include "cvu_graphics.h"

#include "cv_graphics.h"

void cvu_voutb(const uint8_t value, const cv_vmemp dest)
{
	cv_set_write_vram_address(dest);
	cv_voutb(value);
}
