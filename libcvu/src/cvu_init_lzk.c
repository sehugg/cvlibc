#include "cvu_compression.h"

#include <string.h>

void cvu_init_lzk(struct cvu_lzk_state *restrict state, uint8_t (* input)(void), uint8_t escape)
{
	state->input = input;
	state->escape = escape;
	state->left = 0;
	state->start = 0;
	memset(state->buffer, 0, 64);
}

