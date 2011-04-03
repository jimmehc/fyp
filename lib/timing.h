#include "../cpucycles-20060326/cpucycles.h"


/* timing code */
unsigned long long get_time()
{
	return cpucycles_powerpclinux();
}
