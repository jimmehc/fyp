#ifndef MYSPINLOCK
#define MYSPINLOCK

#include <pthread.h>

#define CAS __sync_bool_compare_and_swap
#define SPIN_COUNT 100 
namespace spinlock
{
inline void lockN (volatile int * lck)
{
	int success = 0;
	success = CAS(lck, 0, 1);
	while(!success)	
	{
		for (int i =0; i < SPIN_COUNT; i++) { asm volatile("pause"); }
		success = CAS(lck, 0, 1);
	}
}

inline void unlockN (volatile int * lck)
{
	*lck = 0;
}
}
#endif
