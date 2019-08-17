#include "cv.h"

extern volatile void(*cv_vint_handler)(void);

void *cv_get_vint_handler(void)
{
  return(cv_vint_handler);
}
