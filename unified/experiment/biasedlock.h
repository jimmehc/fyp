#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>



struct Lock {
	//Lock2 t;
	pthread_spinlock_t n; //LockN
	int done;
	void (*func)(int * y, volatile Lock * l);
};

class threaddata
{
	public:
	int *threadid;
	volatile Lock *lock;
	threaddata(){}
	bool done;
};

inline void biased_lock(Lock * l, int * i) __attribute__((always_inline));
inline void biased_unlock_owner(threaddata * td) __attribute__((always_inline));
inline void biased_unlock(Lock * l, int * i) __attribute__((always_inline));
inline void incy(threaddata* td) __attribute__((always_inline));
#endif
