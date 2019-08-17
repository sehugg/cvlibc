#include "cvu_c.h"

cvu_f cvu_cdot(const struct cvu_c *l)
{
	return(cvu_fmul2(l->r, l->r) + cvu_fmul2(l->i, l->i));
}

void cvu_cfmul(struct cvu_c *l, cvu_f r)
{
	l->r = cvu_fmul2(l->r, r);
	l->i = cvu_fmul2(l->i, r);
}

