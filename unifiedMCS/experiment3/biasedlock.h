#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../lib/mcs.h"



typedef struct lll {
	//Lock2 t;
	pthread_spinlock_t n; //LockN
	int done;
	int  token;
} Lock;

class threaddata
{
	public:
	int *threadid;
	int * x;
	int * y;
	Lock *lock;
	threaddata():x(NULL), y(NULL){}
	bool done;
	qnode ** L;
};

inline void biased_lock(Lock * l, int * i) __attribute__((always_inline));
inline void biased_unlock_owner(threaddata * td) __attribute__((always_inline));
inline void biased_unlock(Lock * l, int * i) __attribute__((always_inline));
inline void incy(threaddata* td) __attribute__((always_inline));
#endif
