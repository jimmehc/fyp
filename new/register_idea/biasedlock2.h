#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <pthread.h>

struct Lock;

struct threaddata
{
	//private
	int *threadid;

	//shared
	volatile Lock *lock;
	int * x;
	int * y;
	bool done;
};

#ifdef VAS
struct Lock {
	pthread_spinlock_t n;
	bool request;
	bool grant;
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE); \
	lock->request = false; \
	lock->grant = false;

#define biased_lock_owner(lock) while(lock->grant){}
#define biased_unlock_owner(lock)	\
	if(lock->request) \
	{	\
		lock->request = false; \
		asm volatile ("sync");\
		lock->grant = true;\
	}

#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->request = true; \
	while(!lock->grant){  }
#define biased_unlock(lock) \
	asm volatile ("sync"); \
	lock->grant = false; \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	(*td->y) = (*td->y) + 1;

#endif

#ifdef VASVAR
struct Lock {
	pthread_spinlock_t n;
	bool request;
	bool grant;
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE); \
	lock->request = false; \
	lock->grant = false;

#define biased_lock_owner(lock) 
#define biased_unlock_owner(lock)	\
	if(lock->request) \
	{	\
		lock->request = false; \
		asm volatile ("sync");\
		lock->grant = true;\
		while(lock->grant){}\
	}

#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->request = true; \
	while(!lock->grant){  }
#define biased_unlock(lock) \
	asm volatile ("sync"); \
	lock->grant = false; \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	(*td->y) = (*td->y) + 1;

#endif


#ifdef FP
struct Lock {
	pthread_spinlock_t n;
	int done;
	void (*func)(int * y, volatile Lock * l);
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->y, lock);				/*XXX: REVISIT*/\
		lock->func = NULL;\
		asm volatile("sync");\
		lock->done = 1;\
	}
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ }\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incy;						/*XXX: REVISIT*/

inline void incy (int * y, volatile Lock * l)		/* GENERALIZE? */
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef AFP
struct Lock {
	pthread_spinlock_t n;
	void (*func)(int * y, volatile Lock * l);
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->y, lock);		/*XXX: REVISIT*/\
		asm volatile("sync");\
	}
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	while(lock->func != NULL){ }

#define biased_unlock(lock) \
	asm volatile ("sync"); \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incy;

inline void incy (int * y, volatile Lock * l)
{
	l->func = NULL;
	asm volatile ("sync");
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef MP
struct Lock {
	pthread_spinlock_t n;
	int done;
	int token;
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->token = 0;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->token) \
	{	\
		switch(lock->token) 	/*Change to function handling messages?*/ \
		{ 			\
		case 1: \
				*td->x = *td->x + 1; \
				lock->token = 0;\
				lock->done = 1;\
				asm volatile("sync");\
				break;\
		}\
	}	
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ }\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->token = 1;

#endif

#ifdef AMP
struct Lock {
	pthread_spinlock_t n;
	int token;
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->token = 0;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->token) \
	{	\
		switch(lock->token) 	/*Change to function handling messages?*/ \
		{ 			\
		case 1: \
				lock->token = 0;\
				*td->x = *td->x + 1; \
				break;\
		}\
	}	
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	while(lock->token != 0) {  }

#define biased_unlock(lock) \
	asm volatile("sync");\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->token = 1;

#endif

#ifdef QFP

#include "../lib/myqueue.h"

typedef void (*fp)(int*, volatile Lock*);

struct Lock {
	pthread_spinlock_t n;
	myqueue<fp> * q;
};

void (*func)(int * y, volatile Lock * l);

#define lock_init(lock) \
	lck->q = new myqueue<void (*)(int*, volatile Lock*)>;\
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->q->m_Read != lock->q->m_Write) 	\
		while(lock->q->popElement(&func)) func (td->y, lock);	/*XXX: REVISIT*/
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); 

#define biased_unlock(lock) \
	asm volatile ("sync");\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	func = &incy;	\
	while(!td->lock->q->pushElement(&func));

inline void incy (int * y, volatile Lock * l)
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef MPQ

#include "../lib/myqueue.h"

struct Lock {
	pthread_spinlock_t n;
	myqueue<int> * q;
};
int el;

#define lock_init(lock) \
	lck->q = new myqueue<int>;\
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->q->m_Read != lock->q->m_Write) 	\
		while(lock->q->popElement(&el)) /*XXX: REVISIT*/\
			switch(el)\
					{\
						case 1:\
							(*td->x) = (*td->x) + 1;\
							asm volatile("sync");\
							break;\
					}

#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); 

#define biased_unlock(lock) \
	asm volatile ("sync");\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	el = 1;	\
	while(!td->lock->q->pushElement(&el));

#endif

#endif
