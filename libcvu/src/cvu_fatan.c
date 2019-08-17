#include "cvu_f.h"

#include <stdlib.h>

// Rather good approximation for -PI/4 <= x <= PI/4.
// abs error < 0.015.
// Better, but more expensive: x/(1+0.22..*x*x) (abs error < 0.005)
static cvu_f cvu_fatan_approx1(cvu_f x)
{
	return(x - cvu_fmul2(CVU_I2F(2) / 9, cvu_fmul2(x, cvu_fmul2(x, x))));
}

cvu_f cvu_fatan2(cvu_f y, cvu_f x)
{
	cvu_f tmp;

	if(abs(y) <= abs(x))
		tmp = cvu_fatan_approx1(cvu_fdiv2(y, x));
	else
		tmp = (((x < 0)^(y < 0)) ? -CVU_F_PI_2 : CVU_F_PI_2) - cvu_fatan_approx1(cvu_fdiv2(x, y));

	if(x < 0)
	{
		if(y >= 0)
			tmp += CVU_F_PI;
		else
			tmp -= CVU_F_PI;
	}

	return(tmp);
}

