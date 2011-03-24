#include <pthread.h>
#include "peterson.h"


void peterson::lock2 (int threadid, int * flag, int * turn)
{
	flag[threadid] = 1;

	*turn = !threadid;

	asm volatile ("mfence");

	while(flag[!threadid] == 1 && *turn == !threadid);
}

void peterson::unlock2 (int threadid, int * flag)
{
	asm volatile ("mfence");
	flag[threadid] = 0;
}
