#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include "spinlock.h"
#include <sys/types.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>



typedef struct lll {
	cpu_set_t* ownercpu;
	cpu_set_t* defaultcpus;
	cpu_set_t* test;
	//Lock2 t;
	int n; //LockN
	bool request;
	bool grant;
	int done;
	void (*func)(int * y, struct lll * l);
} Lock;

typedef struct 
{
	int *threadid;
	Lock *lock;
	int * x;
	int * y;
} threaddata;

inline void biased_lock(Lock * l, int * i) __attribute__((always_inline));
inline void biased_unlock_owner(threaddata * td) __attribute__((always_inline));
inline void biased_unlock(Lock * l, int * i) __attribute__((always_inline));
inline void incy(threaddata* td) __attribute__((always_inline));


inline void biased_unlock(Lock * l, int * i)
{
	spinlock::unlockN(&(l->n));
}

inline void biased_lock(Lock * l, int * i)
{
	spinlock::lockN(&(l->n));
}

inline void biased_unlock_owner(threaddata * td) 
{ 
	if(td->lock->func != NULL) 
		td->lock->func(td->y,td->lock); 
}

#endif
