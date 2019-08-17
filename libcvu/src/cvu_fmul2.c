//	(c) 2009 Philipp Klaus Krause philipp@colecovision.eu

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

#include <stdbool.h>

// Replaced by hand-coded asm.
extern uint32_t _u_16_16_mul(uint16_t l, uint16_t r);

int32_t cvu_s_16_16_mul(int16_t l_arg, int16_t r_arg)
{
	bool neg = false;
	int32_t ret;
	register int16_t l = l_arg;
	register int16_t r = r_arg;

	if(l < 0)
	{
		neg = !neg;
		l = -l;
	}
	if(r < 0)
	{
		neg = !neg;
		r = -r;
	}

	ret = _u_16_16_mul(l, r);

	if(neg)
		ret = -ret;

	return(ret);
}

cvu_f cvu_fmul2(cvu_f l, cvu_f r)
{
	int32_t tmp;
	tmp = cvu_s_16_16_mul(l, r);//(int32_t)l * r;
	return(tmp >> CVU_F_R);
}

