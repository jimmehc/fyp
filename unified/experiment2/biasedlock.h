#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>



typedef struct lll {
	//Lock2 t;
	pthread_spinlock_t n; //LockN
	void (*func)(int * const y, struct lll * l);
} Lock;

class threaddata
{
	public:
	int *threadid;
	int * const x;
	int * const y;
	Lock *lock;
	threaddata():x(NULL), y(NULL){}
	threaddata(int * _threadid, int * const _x, int * const _y) : threadid(_threadid), x(_x), y(_y){}
	bool done;
};

inline void biased_lock(Lock * l, int * i) __attribute__((always_inline));
inline void biased_unlock_owner(threaddata * td) __attribute__((always_inline));
inline void biased_unlock(Lock * l, int * i) __attribute__((always_inline));
inline void incy(threaddata* td) __attribute__((always_inline));
#endif
