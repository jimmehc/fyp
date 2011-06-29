#ifndef ALGS
#define ALGS

#include "biased_sync_new.h"

template <typename T>
struct shared_data;

template <typename T>
struct func_struct;
 
#if defined(FP) || defined(AFP) || defined(ISPL)
template <typename T>
struct Lock{
	int owner;
	bool biased_mode;
	pthread_spinlock_t * n;
	func_struct<T> fs;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	biased_mode = true;
	n = new pthread_spinlock_t;
	pthread_spin_init(n, PTHREAD_PROCESS_PRIVATE);
	fs.func = NULL;
	fs.params = malloc(10*sizeof(void*));
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	if(sd->l.fs.func != NULL) 	
	{	
		sd->l.fs.func (sd,sd->l.fs.params );
		sd->l.fs.func = NULL;
		asm volatile("mfence");
	}
}
#endif

#if defined(FP)
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params){
	pthread_spin_lock(sd->l.n);
	volatile func_struct<T> fs;
	fs.func = work;
	fs.params = params;
	sd->l.fs = fs;
	asm volatile ("mfence");
	while (sd->l.fs.func != NULL){ asm volatile ("pause"); }
	pthread_spin_unlock(sd->l.n);
}
#endif

#if defined(AFP)
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params){
	pthread_spin_lock(sd->l.n);
	while (sd->l.fs.func != NULL){ asm volatile ("pause"); }
	func_struct<T> fs;
	fs.func = work;
	fs.params = params;
	sd->l.fs = fs;
	asm volatile ("mfence");
	pthread_spin_unlock(sd->l.n);
}

#endif

#ifdef ISPL

#define CAS __sync_bool_compare_and_swap
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params){
	func_struct<T> fs;
	fs.func = work;
	fs.params = params;

	int success = 0;
	do
	{
		while (sd->l.fs != NULL) {asm volatile ("pause");}
		success = CAS(&sd->l.fs, NULL, &fs);
	}while(!success);
}
#endif

#ifdef FPQ	//XXX: CAN'T DO PARAMS SAFELY LIKE THIS

#include "myqueue.h"

template <typename T>
struct Lock{
	int owner;
	bool biased_mode;
	pthread_spinlock_t * n;
	void * params;
	myqueue<void (*)(shared_data<T> *, void * params)> * q;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	biased_mode = true;
	n = new pthread_spinlock_t;
	pthread_spin_init(n, PTHREAD_PROCESS_PRIVATE);
	q = new myqueue<void (*)(shared_data<T> *, void * params)>;
	q->m_Read = q->m_Write = 0;
	params = malloc(10*sizeof(void*));
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	void (*func)(shared_data<T> *, void * params);
	while(sd->l.q->popElement(&func))
		func (sd,sd->l.params );
}

template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params){
	pthread_spin_lock(sd->l.n);
	sd->l.params = params;
	while(!sd->l.q->pushElement(&work)) {asm volatile ("pause");}
	pthread_spin_unlock(sd->l.n);
}

#endif

#endif
