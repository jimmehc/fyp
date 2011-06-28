#include <sys/time.h>

/* timing code */
unsigned long long get_time()
{
	unsigned long long res;

	timeval t;

	gettimeofday(&t, NULL);
    res = t.tv_sec;
	res *= (1000 * 1000);
	res += t.tv_usec;

	return res;
}

