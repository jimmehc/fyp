#ifndef SPINLOCK
#define SPINLOCK

#include <pthread.h>
#include <unistd.h>

typedef void (*fp)(int*, Lock*);

#define CAS __sync_bool_compare_and_swap
namespace spinlock
{
inline void lockN (fp * func, fp work)
{
	int success = 0;
	do
	{
		while (*func != NULL) ;
		success = CAS(func, NULL, work);
	}while(!success);
}

/*inline void unlockN (int * lck)
{
	*lck = 0;
}*/
}
#endif
