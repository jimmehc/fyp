#include <pthread.h>
#include "peterson.h"


void peterson::lock2 (int threadid, int * flag, int * turn)
{
	flag[threadid] = 1;

	*turn = !threadid;

	asm volatile ("sync");

	while(flag[!threadid] == 1 && *turn == !threadid);
}

void peterson::unlock2 (int threadid, int * flag)
{
	asm volatile ("sync");
	flag[threadid] = 0;
}
