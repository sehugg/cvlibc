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

#ifdef CVU_HUFFMAN_ITERATIVE
// Iterative version
uint8_t cvu_get_huffman(struct cvu_huffman_state *state)
{
	uint8_t current;
	uint8_t ret;

	current = state->root;

	for(;;)
	{
		state->buffer >>= 1;
		if(state->bit == 8)
		{
			state->buffer = (state->input)();
			state->bit = 0;
		}
		state->bit++;

		if(!(state->buffer & 0x01))	// Left
		{
			if(current >= state->ls && current < state->rs)
			{
				ret = state->nodes[current].left;
				break;
			}

			current = state->nodes[current].left;
		}
		else	// Right
		{
			if(current >= state->bs)
			{
				ret = state->nodes[current].right;
				break;
			}

			current = state->nodes[current].right;
		}
	}
	
	return(ret);
}
#endif

#ifdef CVU_HUFFMAN_RECURSIVE
// Recursive version
uint8_t cvu_get_huffman(struct cvu_compression_state *state)
{
	bool direction;
	uint8_t ret;

	state->buffer >>= 1;
	if(state->bit == 8)
	{
		state->buffer = (state->input)();
		state->bit = 0;
	}
	direction = state->buffer & 0x01;
	state->bit++;

	if(!direction)	// Left
	{
		if(state->current >= state->ls && state->current < state->rs)
		{
			ret = state->nodes[state->current].left;
			state->current = state->root;
		}
		else
		{
			state->current = state->nodes[state->current].left;
			ret = cvu_get_huffman(state);
		}
	}
	else	// Right
	{
		if(state->current >= state->bs)
		{
			ret = state->nodes[state->current].right;
			state->current = state->root;
		}
		else
		{
			state->current = state->nodes[state->current].right;
			ret = cvu_get_huffman(state);
		}
	}

	return(ret);
}
#endif

