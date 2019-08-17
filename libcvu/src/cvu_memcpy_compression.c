#include "cvu_compression.h"

extern struct cvu_compression_state *_common_state;

void *cvu_memcpy_compression(void *restrict dest, struct cvu_compression_state *state, size_t n)
{
	size_t i = 0;
	_common_state = state;
	for(; n > 0; n--)
		((uint8_t *restrict)(dest))[i++] = cvu_get_rle(&_common_state->rle);

	return(dest);
}

