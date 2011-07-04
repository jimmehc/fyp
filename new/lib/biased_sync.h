#ifndef BSYNC
#define BSYNC

#include <pthread.h>
#include <stdlib.h>
#include "blalgorithms.h"
#include "volatile_functions.h"
#include "myspinlock.h"

// BIASED_MODE is harder than I though, getting rid of it in here

template <typename T>
struct shared_data;

template<typename T>
struct Lock;

template <typename T>
struct shared_data{
	volatile Lock<T> l;
	T d;
};

#if defined (FP) || (ISPL) || (AFP) || (FPQ) || (SPL) || (BQ) || (VAS)
template <typename T>
struct func_struct
{
	void (*func)(shared_data<T> *, void *);
	void * params;
	int creatorid;
	void operator=(volatile const func_struct& fs) volatile;
};

template <typename T>
void func_struct<T>::operator=(volatile const func_struct& fs) volatile
{
	func = fs.func;
	params = fs.params;
	creatorid = fs.creatorid;
}


template <typename T>
void critical_section (int threadid, void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params = NULL, shared_data<T> * mysd = NULL){
	if(threadid == sd->l.owner){
		atstart();
		work (sd, params);
		poll (sd, params);
	} else {
		push_work (work, sd, params, threadid, mysd);
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

#if defined (MP) || (AMP) || (ISPLMP) || (MPQ)
template <typename T>
struct msg_struct
{
	int msg;
	void * params;
	void operator=(volatile const msg_struct& fs) volatile;
};

template <typename T>
void msg_struct<T>::operator=(volatile const msg_struct& ms) volatile
{
	msg = ms.msg;
	params = ms.params;
}

void message_handler(int token, shared_data<int> * sd, void * params){
	switch(token){
		case 1:		// inc
			vol_inc(sd->d);
		break;
		
		case 2:		// dec
			sd->d--;
		break;

		case 3:		//setrand
			sd->d = rand();
		break;
	}
}

void critical_section (int threadid, int msg, shared_data<int> * sd, void * params = NULL, shared_data<int> * mysd = NULL){
	if(threadid == sd->l.owner){
		message_handler (msg, sd, params);
		poll (sd, params);
	} else {
		push_work (msg, sd, params, threadid, mysd);
	}
}

#endif
#endif
