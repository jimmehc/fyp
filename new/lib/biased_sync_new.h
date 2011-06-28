#ifndef BSYNC
#define BSYNC

#include <pthread.h>
#include <stdlib.h>
#include "blalgorithms_new.h"

template <typename T>
struct shared_data;

template <typename T>
struct Lock;

template <typename T>
struct func_struct;

template <typename T>
struct func_struct
{
	void (*func)(shared_data<T> *, void *); __attribute__ ((always_inline))
	void * params;
};

template <typename T>
struct shared_data{
	volatile Lock<T> l;
	T d;
};


template <typename T>
void critical_section (int threadid, func_struct<T> fs, shared_data<T> * sd){
	if (sd->l.biased_mode){
		if(threadid == sd->l.owner){
			fs.func (sd, fs.params);
			poll (sd, fs.params);
		} else {
			push_work (fs.func, sd, fs.params);
		}
	} else {
		pthread_spin_lock (sd->l.n);
		fs.func (sd, fs.params);
		pthread_spin_unlock (sd->l.n);
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
