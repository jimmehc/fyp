#ifndef ALGS
#define ALGS

#include "biased_sync.h"
#include "myspinlock.h"
template <typename T>
struct shared_data;

#if defined(FP) || defined(AFP) || defined(ISPL)
template <typename T>
struct Lock{
	int owner;
	bool biased_mode;
	volatile int * n;
	void (*func)(shared_data<T> *, void *);
	void * params;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	biased_mode = true;
	n = new int(0);
	func = NULL;
	params = NULL;
	params = malloc(10*sizeof(void*));
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	if(sd->l.func != NULL) 	
	{	
		sd->l.func (sd,sd->l.params );
		sd->l.func = NULL;
		asm volatile("mfence");
	}
}
#endif

#if defined(FP)
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid){
	spinlock::lockN(sd->l.n);
	sd->l.params = params;
	asm volatile ("mfence");
	sd->l.func = work;
	while (sd->l.func != NULL){ 
		if (!(sd->l.biased_mode)){
			work(sd, params);
			break;
		}
		asm volatile ("pause"); 
	}
	spinlock::unlockN(sd->l.n);
}
#endif

#if defined(AFP)
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid){
	spinlock::lockN(sd->l.n);
	while (sd->l.func != NULL){ asm volatile ("pause"); }
	sd->l.params = params;
	asm volatile ("mfence");
	sd->l.func = work;
	spinlock::unlockN (sd->l.n);
}
#endif

#ifdef ISPL

#define CAS __sync_bool_compare_and_swap
template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid){
	int success = 0;
	do
	{
		while (sd->l.func != NULL) {asm volatile ("pause");}
		success = CAS(&sd->l.func, NULL, work);
	}while(!success);
}
#endif

#ifdef FPQ	//XXX: CAN'T DO PARAMS SAFELY LIKE THIS

#include "myqueue.h"

template <typename T>
struct Lock{
	int owner;
	bool biased_mode;
	volatile int * n;
	void * params;
	myqueue<void (*)(shared_data<T> *, void * params)> * q;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	biased_mode = true;
	n = new int(0);
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
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid){
	spinlock::lockN(sd->l.n);
	sd->l.params = params;
	while(!sd->l.q->pushElement(&work)) {asm volatile ("pause");}
	spinlock::unlockN(sd->l.n);
}

#endif

#ifdef VASVAR
	template <typename T>
	struct Lock{
		int owner;
		bool biased_mode;
		volatile int * n;
		bool request;
		bool grant;
		Lock();
	};	

	template <typename T>
	Lock<T>::Lock(){
		owner = 0;
		biased_mode = true;
		n = new int(0);
		request = false;
		grant = false;
	}

	template <typename T>
	void poll(shared_data<T> * sd, void * params)
	{
		if(sd->l.request) 
		{	
			sd->l.request = false; 
			asm volatile ("mfence");
			sd->l.grant = true;
			while(sd->l.grant){asm volatile ("pause");}
		}
	}
	template <typename T>
	void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid){
		spinlock::lockN(sd->l.n); 
		sd->l.request = true; 
		while(!sd->l.grant){ asm volatile ("pause"); }
		work(sd, params);
		asm volatile ("mfence"); 
		sd->l.grant = false; 
		spin::unlockN(sd->l.n);
	}

#endif

#ifdef BQ

#include "myqueue.h"

template <typename T>
struct Lock{
	int owner;
	bool biased_mode;
	volatile int * n;
	void * params;
	bool done[NUM_THREADS];
	myqueue<void (*)(shared_data<T> *, void * params)> * q;
	Lock();
};	

template <typename T>
Lock<T>::Lock(){
	owner = 0;
	biased_mode = true;
	n = new int(0);
	q = new myqueue<void (*)(shared_data<T> *, void * params)>;
	q->m_Read = q->m_Write = 0;
	params = malloc(10*sizeof(void*));
	for(int i = 0;i < NUM_THREADS; i++) done[i] = true;
}

template <typename T>
void poll(shared_data<T> * sd, void * params){
	void (*func)(shared_data<T> *, void * params);
	while(sd->l.q->popElement(&func))
		func (sd,sd->l.params );
}

template <typename T>
void push_work(void (*work)(shared_data<T> *, void *), shared_data<T> * sd, void * params, int threadid){
	spinlock::lockN(sd->l.n);
	sd->l.done[threadid] = false;
	asm volatile("mfence");
	while(!sd->l.q->pushElement(&work)) {asm volatile ("pause"); }
	while(!sd->l.done[threadid]) { asm volatile("pause"); }
	spinlock::unlockN(sd->l.n);
}

#endif

#endif
