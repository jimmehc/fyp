#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include "../../lib/mcs.h"

typedef struct 
{
	pthread_mutex_t * m;
	int *threadid;
	int * x;
	int * y;
	bool done;
	qnode ** L;
} threaddata;

#endif
