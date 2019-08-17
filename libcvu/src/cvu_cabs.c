#include "cvu_c.h"

#include <stdlib.h>	// For abs()

cvu_f cvu_cabs(const struct cvu_c *l)
{
	return(abs(l->r) + abs(l->i));
}

