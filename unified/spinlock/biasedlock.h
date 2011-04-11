#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
	pthread_spinlock_t n; //LockN
} Lock;

typedef struct 
{
	int *threadid;
	Lock *lock;
	int * x;
	int * y;
	bool done;
} threaddata;

#endif
