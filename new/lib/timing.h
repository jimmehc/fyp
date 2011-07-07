#include <sys/time.h>


/* timing code */
unsigned long long get_time()
{
 unsigned long long int result=0;
 unsigned long int upper, lower,tmp;
 __asm__ volatile(
               "0:                  \n"
               "\tmftbu   %0           \n"
               "\tmftb    %1           \n"
               "\tmftbu   %2           \n"
               "\tcmpw    %2,%0        \n"
               "\tbne     0b         \n"
               : "=r"(upper),"=r"(lower),"=r"(tmp)
               );
 result = upper;
 result = result<<32;
 result = result|lower;

 return(result);
	/*unsigned long long res;

	timeval t;

	gettimeofday(&t, NULL);
    res = t.tv_sec;
	res *= (1000 * 1000);
	res += t.tv_usec;

	return res;*/
}

