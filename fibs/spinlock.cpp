#include <pthread.h>
#include <unistd.h>
#include "spinlock.h"

#define CAS __sync_bool_compare_and_swap

void spinlock::lockN (int * lck)
{
	int success = 0;
	do
	{
		while (*lck != 0);
		success = CAS(lck, 0, 1);
	}while(!success);
}

void spinlock::unlockN (int * lck)
{
	*lck = 0;
}

