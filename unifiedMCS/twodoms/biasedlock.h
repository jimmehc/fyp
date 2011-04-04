#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../lib/mcs.h"

typedef struct {
	//Lock2 t;
	pthread_spinlock_t n; //LockN
	int t;
	bool request;
	bool grant;
	bool flag[2];
	int turn;
} Lock;

typedef struct 
{
	int *threadid;
	Lock *lock;
	int * x;
	int * y;
	bool done;
	qnode ** L;
} threaddata;

void biased_lock(Lock * l, int * i);
void biased_unlock(Lock * l, int * i);
#endif
