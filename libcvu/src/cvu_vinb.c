#include "cvu_graphics.h"

#include "cv_graphics.h"

uint8_t cvu_vinb(const cv_vmemp dest)
{
	cv_set_read_vram_address(dest);
	return(cv_vinb());
}
