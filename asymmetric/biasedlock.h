#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sys/types.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>

typedef struct {
	pid_t owner;
	//Lock2 t;
	boost::uint32_t n; //LockN
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
