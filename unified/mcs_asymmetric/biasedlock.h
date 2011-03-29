#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>
#include "mcs.h"

typedef struct {
	//Lock2 t;
	pthread_spinlock_t n; //LockN
	bool request;
	bool grant;
} Lock;

typedef struct 
{
	int *threadid;
	int * x;
	int * y;
	Lock * lock;
	qnode ** L;
} threaddata;

#endif
