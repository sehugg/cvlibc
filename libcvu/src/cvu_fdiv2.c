//	(c) 2009-2010 Philipp Klaus Krause philipp@colecovision.eu

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

#include "cvu_f.h"

#include <stdlib.h>

cvu_f cvu_fdiv2(cvu_f l_arg, cvu_f r)
{
	register cvu_f l = l_arg;
	uint_fast8_t shift;

	for(shift = CVU_F_R; shift && abs(l) <= (INT16_MAX >> 1); shift--)
		l <<= 1;

	return((l / r) << shift);
}

