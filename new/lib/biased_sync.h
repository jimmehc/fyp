#ifndef BSYNC
#define BSYNC

#include <pthread.h>
#include <stdlib.h>
#include "blalgorithms.h"
#include "myspinlock.h"


template <typename T>
struct shared_data;


template <typename T>
struct shared_data{
	volatile Lock<T> l;
	T d;
};


template <typename T>
void critical_section_owner (int threadid, void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params = NULL){
	if (sd->l.biased_mode){
//		if(threadid == sd->l.owner){
			work (sd, params);
			poll (sd, params);
//		} else {
//			push_work (work, sd, params);
//		}
	} else {
		spinlock::lockN (sd->l.n);
		work (sd, params);
		spinlock::unlockN (sd->l.n);
	}
}

template <typename T>
void critical_section (int threadid, void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params = NULL){
	if (sd->l.biased_mode){
//		if(threadid == sd->l.owner){
//			work (sd, params);
//			poll (sd, params);
//		} else {
			push_work (work, sd, params, threadid);
//		}
	} else {
		spinlock::lockN (sd->l.n);
		work (sd, params);
		spinlock::unlockN (sd->l.n);
	}
}

template <typename T>
void get (shared_data<T> * sd, void * ret){
	ret = (void*) sd->d;
}

template <typename T> 
void set(shared_data<T> * sd, void * val){
	T * temp = (T*) val;
	sd->d = *temp;
}

#endif
