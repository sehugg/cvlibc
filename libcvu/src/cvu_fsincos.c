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

#include <stdlib.h>
#include <stdbool.h>

const uint_fast8_t cvu_fsintable[CVU_F_PI_2 + 1] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 32, 33, 34, 35, 36, 37, 37, 38, 39, 40, 41, 41, 42, 43, 44, 44, 45, 46, 46, 47, 48, 48, 49, 50, 50, 51, 52, 52, 53, 53, 54, 54, 55, 55, 56, 56, 57, 57, 58, 58, 59, 59, 59, 60, 60, 60, 61, 61, 61, 62, 62, 62, 62, 63, 63, 63, 63, 63, 63, 64, 64, 64, 64, 64, 64, 64, 64, };

cvu_f cvu_fsin(cvu_f x)
{
	bool neg;
	cvu_f ret;

	if(x < 0)
	{
		x = -x;
		neg = true;
	}
	else
		neg = false;

	while(x >= CVU_F_PI)
	{
		x -= CVU_F_PI;
		neg = !neg;
	}

	if(x < CVU_F_PI_2)
		ret = cvu_fsintable[x];
	else
		ret = cvu_fsintable[CVU_F_PI - x - 1];
		
	if(neg)
		ret = -ret;

	return(ret);
}

cvu_f cvu_fcos(cvu_f x)
{
	return(cvu_fsin(x + CVU_F_PI_2));
}

