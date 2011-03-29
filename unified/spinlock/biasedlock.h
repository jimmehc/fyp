#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
	int n; //LockN
} Lock;

typedef struct 
{
	int *threadid;
	Lock *lock;
	int * x;
	int * y;
} threaddata;

#endif
