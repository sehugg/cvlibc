#include "cvu_input.h"

int_fast8_t cvu_spinners[2];

void cvu_spint_handler(uint_fast8_t port0, uint_fast8_t port1)
{
	if(!(port0 & 0x10))
	{
		if(port0 & 0x20)
			cvu_spinners[0]++;
		else
			cvu_spinners[0]--;
	}

	if(!(port1 & 0x10))
	{
		if(port1 & 0x20)
			cvu_spinners[1]++;
		else
			cvu_spinners[1]--;
	}
}

int_fast8_t cvu_get_spinner(uint_fast8_t controller)
{
	int_fast8_t spinner;

	// We need to disable the spint interrupt while reading and zeroing, to ensure no spinner movement is missed.

	cv_set_spint_handler(0);

	spinner = cvu_spinners[controller];
	cvu_spinners[controller] = 0;

	cv_set_spint_handler(cvu_spint_handler);

	return(spinner);
}

