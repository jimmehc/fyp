#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>



typedef struct lll {
	//Lock2 t;
	int n; //LockN
	void (*func)(int *  y, struct lll * l);
} Lock;

class threaddata
{
	public:
	int *threadid;
	int *  x;
	int *  y;
	Lock *lock;
	threaddata():x(NULL), y(NULL){}
	threaddata(int * _threadid, int *  _x, int *  _y) : threadid(_threadid), x(_x), y(_y){}
};

inline void biased_lock(Lock * l, int * i) __attribute__((always_inline));
inline void biased_unlock_owner(threaddata * td) __attribute__((always_inline));
inline void biased_unlock(Lock * l, int * i) __attribute__((always_inline));
inline void incy(threaddata* td) __attribute__((always_inline));
#endif
