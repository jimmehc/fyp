#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <boost/interprocess/detail/atomic.hpp>
#include <unistd.h>
#include "mcs.h"

typedef struct _threaddata threaddata;

struct _threaddata
{
	int * threadid;
	int * x;
	int * y;
	qnode ** L;
};

#endif
