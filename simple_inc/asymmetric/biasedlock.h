#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>

typedef struct {
	cpu_set_t* ownercpu;
	cpu_set_t* defaultcpus;
	cpu_set_t* test;
	//Lock2 t;
	int n; //LockN
	bool request;
	bool grant;
} Lock;

typedef struct 
{
	int *threadid;
	Lock *lock;
	int * x;
	int * y;
} threaddata;

void biased_lock(Lock * l, int * i);
void biased_unlock(Lock * l, int * i);
#endif
