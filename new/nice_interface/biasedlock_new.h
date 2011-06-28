#ifndef BIASEDLOCK
#define BIASEDLOCK

#include "../lib/biased_sync_new.h"

template <typename T>
struct threaddata
{
	//private
	int threadid;

	//shared
	shared_data<T> * sd;
	int done;
};


#endif
