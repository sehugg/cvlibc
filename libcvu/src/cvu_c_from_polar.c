#include "cvu_c.h"

void cvu_c_from_polar(struct cvu_c *c, cvu_f phi, cvu_f d)
{
	c->r = cvu_fcos(phi);
	c->i = cvu_fsin(phi);
	if(d != CVU_I2F(1))
		cvu_cfmul(c, d);
}

