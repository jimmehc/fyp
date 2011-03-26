#ifndef BIASEDLOCK
#define BIASEDLOCK

#include "../../lib/myqueue.h"
#include <sched.h>
#include <sys/types.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>

class Lock;

typedef void (*fp)(int*, Lock*);

class Lock
{
	public:
	//Lock2 t;
	int n; //LockN
	int done;
	myqueue<fp> * q;
};

class threaddata
{
	public:
	int *threadid;
	int * x;
	int * y;
	Lock *lock;
};

#endif
