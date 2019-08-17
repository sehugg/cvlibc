#include "cv.h"

extern uint8_t cv_machine_config;

enum cv_machine cv_get_machine(void)
{
	return(cv_machine_config >> 6);
}

