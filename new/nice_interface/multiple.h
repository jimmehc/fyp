#ifndef BIASEDLOCK
#define BIASEDLOCK

#include "../constants.h"
#include "../lib/biased_sync.h"
#include <pthread.h>

template <typename T>
struct threaddata
{
	//private
	int threadid;


	//shared
	volatile shared_data<T> * sds[NUM_THREADS];
	volatile int done;
};


#endif
