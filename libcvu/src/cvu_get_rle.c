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

uint8_t cvu_get_rle(struct cvu_rle_state *state)
{
	uint8_t next;

	if(state->left)
		goto output;

	next = (state->input)();

	if(next != state->escape)
		return(next);

	state->left = (state->input)();
	state->buffer = (state->input)();

output:
	state->left--;
	return(state->buffer);
}

