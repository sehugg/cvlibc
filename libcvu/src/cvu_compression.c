//	(c) 2006 Philipp Klaus Krause philipp@colecovision.eu

//	This library is free software; you can redistribute it and/or modify it
//	under the terms of the GNU Library General Public License as published by the
//	Free Software Foundation; either version 2, or (at your option) any
//	later version.
   
//	This library is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//	GNU Library General Public License for more details.
   
//	You should have received a copy of the GNU Library General Public License
//	along with this program; if not, write to the Free Software
//	Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include "cvu_compression.h"

struct cvu_compression_state *_common_state;

extern uint8_t _read_from_array(void);

// reimplemented in assembler as _read_from_array() : hand-coded asm: 13 instructions, compiler generated 35
//static uint8_t read_from_array(void)
//{
//	return(*((_common_state->data)++));
//}

static uint8_t read_from_huffman(void)
{
	return(cvu_get_huffman(&_common_state->huffman));
}

void cvu_init_compression(const uint8_t *restrict data, struct cvu_compression_state *restrict state, const struct cvu_huffman_node *restrict tree, uint8_t root, uint8_t ls, uint8_t bs, uint8_t rs, uint8_t escape)
{
	state->data = data;
	cvu_init_huffman(&state->huffman, &_read_from_array, tree, root, ls, bs, rs);
	cvu_init_rle(&state->rle, &read_from_huffman, escape);
}

uint8_t cvu_get_compression(struct cvu_compression_state *state)
{
	_common_state = state;
	return(cvu_get_rle(&_common_state->rle));
}

void cvu_memtovmemcpy_compression(cv_vmemp dest, struct cvu_compression_state *state, size_t n)
{
	_common_state = state;
	cv_set_write_vram_address(dest);
	for(;n > 0; n--)
		cv_voutb(cvu_get_rle(&_common_state->rle));
}

