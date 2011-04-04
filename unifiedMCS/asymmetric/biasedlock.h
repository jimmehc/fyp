#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../lib/mcs.h"

typedef struct {
/*	cpu_set_t* ownercpu;
	cpu_set_t* defaultcpus;
	cpu_set_t* test;*/
	//Lock2 t;
	int * n1;
	int * n2;
	pthread_spinlock_t n;
	bool request;
	bool grant;
} Lock;

typedef struct 
{
	//private
	int *threadid;

	//shared
	Lock *lock;
	int * x;
	int * y;
	bool done;
	qnode ** L;
} threaddata;

void biased_lock(Lock * l, int * i);
void biased_unlock(Lock * l, int * i);
#endif
