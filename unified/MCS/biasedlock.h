#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include "../../lib/mcs.h"

typedef struct _threaddata threaddata;

struct _threaddata
{
	int * threadid;
	int * x;
	int * y;
	qnode ** L;
	bool done;
};

#endif
