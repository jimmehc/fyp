#ifndef SPINLOCK
#define SPINLOCK

#include <pthread.h>
#include <unistd.h>
#include "spinlock.h"

#define CAS __sync_bool_compare_and_swap
namespace spinlock
{

inline void lockN (int * lck);
inline void unlockN (int * lck);

void lockN (int * lck)
{
	int success = 0;
	do
	{
		while (*lck != 0);
		success = CAS(lck, 0, 1);
	}while(!success);
}

void unlockN (int * lck)
{
	*lck = 0;
}
}
#endif
