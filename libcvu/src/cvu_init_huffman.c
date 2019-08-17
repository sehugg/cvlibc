#include "cvu_compression.h"

void cvu_init_huffman(struct cvu_huffman_state *restrict state, uint8_t (* input)(void), const struct cvu_huffman_node *restrict tree, uint8_t root, uint8_t ls, uint8_t bs, uint8_t rs)
{
	state->input = input;
	state->nodes = tree;
	state->root = root;
	state->ls = ls;
	state->bs = bs;
	state->rs = rs;
	state->bit = 8;
#ifdef CVU_HUFFMAN_RECURSIVE
	state->current = state->root;
#endif
}

