#include "cvu_compression.h"

void cvu_init_rle(struct cvu_rle_state *restrict state, uint8_t (* input)(void), uint8_t escape)
{
	state->input = input;
	state->escape = escape;
	state->left = 0;
}

