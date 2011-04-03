#ifndef BIASEDLOCK
#define BIASEDLOCK

#include "../../lib/myqueue.h"
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

class Lock;

class Lock
{
	public:
	//Lock2 t;
	pthread_spinlock_t n; //LockN
	int done;
	myqueue<int> * q;
};

class threaddata
{
	public:
	int *threadid;
	int * x;
	int * y;
	Lock *lock;
	bool done;
};

#endif
