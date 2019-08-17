//	(c) 2010 Philipp Klaus Krause philipp@colecovision.eu

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

static void ringbuffer_insert(struct cvu_lzk_state *state, const uint8_t c)
{
	state->buffer[++(state->start)] = c;
	state->start %= 64;
}

static uint8_t ringbuffer_get(struct cvu_lzk_state *state)
{
	uint8_t ret;
	uint_fast8_t i = (state->start++ + 64 - state->offset);
	state->start %= 64;
	i %= 64;
	return(state->buffer[i]);
}

uint8_t cvu_get_lzk(struct cvu_lzk_state *state)
{
	uint8_t next;

	if(state->left)
		goto output;

	next = state->input();

	if(next != state->escape)
	{
		ringbuffer_insert(state, next);
		return(next);
	}

	next = state->input();

	if(!next)
	{
		ringbuffer_insert(state, state->escape);
		return(state->escape);
	}

	state->offset = 0;
	if(!(next & 0xf))
	{
		state->left = ((next >> 4) & 0x3);
		state->offset = (next >> 6);
		next = state->input();
	}

	state->left += (next & 0xf);
	state->left++;
	state->offset += (next >> 4);

output:
	state->left--;
	return(ringbuffer_get(state));
}

