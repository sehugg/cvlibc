//	(c) 2005 Philipp Krause pkk@spth.de

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

// Replaced by hand-coded assembler code.
#include "cv.h"
#include "cvu_graphics.h"

void cvu_set_sprite_y(struct cvu_sprite *sprite, int y)
{
	if(y > 207)
		y = 207;
	if(y < -32)
		y = -32;
	if(y < 0)
		y += 256;

	sprite->y = y;
}

