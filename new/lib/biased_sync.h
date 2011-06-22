#ifndef BSYNC
#define BSYNC

#include <pthread.h>
#include <stdlib.h>

template <typename T>
struct shared_data;

template <typename T>
struct Lock{
	int owner;
	bool biased_mode;
	pthread_spinlock_t * n;
	void * params;
	void (*func)(shared_data<T> *, void * params);
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	biased_mode = true;
	n = new pthread_spinlock_t;
	pthread_spin_init(n, PTHREAD_PROCESS_PRIVATE);
	func = NULL;
	params = malloc(10*sizeof(void*));
}

template <typename T>
struct shared_data{
	volatile Lock<T> l;
	T d;
};

template <typename T>
void poll(shared_data<T> * sd){
	if(sd->l.func != NULL) 	
	{	
		sd->l.func (sd,sd->l.params );
		sd->l.func = NULL;
		asm volatile("mfence");
	}
}

template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params){
	pthread_spin_lock(sd->l.n);
	sd->l.func = work;
	sd->l.params = params;
	while (sd->l.func != NULL){ asm volatile ("pause"); }
	pthread_spin_unlock(sd->l.n);
}

template <typename T>
void critical_section (int threadid, void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params = NULL){
	if (sd->l.biased_mode){
		if(threadid == sd->l.owner){
			work (sd, params);
			poll (sd);
		} else {
			push_work (work, sd, params);
		}
	} else {
		pthread_spin_lock (sd->l.n);
		work (sd, params);
		pthread_spin_unlock (sd->l.n);
	}
}
#endif
