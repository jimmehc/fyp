#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <pthread.h>

#define startoffoo() 

struct Lock;

struct threaddata
{
	//private
	int *threadid;

	//shared
	volatile Lock *lock;
	volatile int * x;
	volatile bool done;
};

#ifdef SPL 
struct Lock {
	pthread_spinlock_t n;
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE); 

#define biased_lock_owner(lock) pthread_spin_lock(&lock->n);

#define biased_unlock_owner(lock) pthread_spin_unlock(&lock->n);	

#define biased_lock(lock) pthread_spin_lock(&lock->n);
#define biased_unlock(lock)	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	x = x + 1;

#endif

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

#define biased_lock_owner(lock) while(lock->grant){pause();} restorepr(); 
#define biased_unlock_owner(lock)	\
	if(lock->request) \
	{	\
		lock->request = false; \
		fence();\
		lock->grant = true;\
	}

#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->request = true; \
	while(!lock->grant){ pause();} restorepr();
#define biased_unlock(lock) \
	fence(); \
	lock->grant = false; \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	(*td->x) = (*td->x) + 1;

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
		*td->x = x;\
		lock->request = false; \
		fence();\
		lock->grant = true;\
		while(lock->grant){pause();} restorepr(); \
		x = *td->x;\
	}

#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->request = true; \
	while(!lock->grant){ pause();} restorepr();
#define biased_unlock(lock) \
	fence(); \
	lock->grant = false; \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	(*td->x) = (*td->x) + 1;

#endif


#ifdef FPR
struct Lock {
	pthread_spinlock_t n;
	int done;
	void (*func)(int * x, volatile Lock * l);
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (&x, lock);				/*XXX: REVISIT*/\
		lock->func = NULL;\
		fence();\
		lock->done = 1;\
	}
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ pause();} restorepr(); \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incx;						/*XXX: REVISIT*/

inline void incx (int * x, volatile Lock * l)		/* GENERALIZE? */
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*x) = (*x) + 1;
}

#endif

#ifdef AFPR
struct Lock {
	pthread_spinlock_t n;
	void (*func)(int * x, volatile Lock * l);
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (&x, lock);		/*XXX: REVISIT*/\
		fence();\
	}
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	while(lock->func != NULL){ pause();} restorepr(); 

#define biased_unlock(lock) \
	fence(); \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incx;

inline void incx (int * x, volatile Lock * l)
{
	l->func = NULL;
	fence();
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*x) = (*x) + 1;
}

#endif

#ifdef MPR
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
				x = x + 1; \
				lock->token = 0;\
				lock->done = 1;\
				fence();\
				break;\
		}\
	}	
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ pause();} restorepr(); \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->token = 1;

#endif

#ifdef AMPR
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
				x = x + 1; \
				break;\
		}\
	}	
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	while(lock->token != 0) { pause();} restorepr();

#define biased_unlock(lock) \
	fence();\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->token = 1;

#endif

#ifdef ISPLR
typedef void (*fp)(int*, volatile Lock*);

#define CAS __sync_bool_compare_and_swap

struct Lock {
	void (*func)(int * y, volatile Lock * l);
};

inline void pushWork (volatile fp * lck, fp func)
{
	int success = 0;
	do
	{
		while (*lck != NULL) { pause();} restorepr();
		success = CAS(lck, NULL, func);
	}while(!success);
}

#define lock_init(lock) \
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (&x, lock);		/*XXX: REVISIT*/\
		fence();\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->func, &incy);

#define biased_unlock(lock) \
	fence(); 

#define non_dom_crit_sec() 

inline void incy (int * y, volatile Lock * l)
{
	l->func = NULL;
	fence();
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef ISPLMPR
#define CAS __sync_bool_compare_and_swap

struct Lock {
	int token;
};

inline void pushWork (volatile int * lck, int token)
{
	int success = 0;
	do
	{
		while (*lck != 0) { pause();} restorepr(); 
		success = CAS(lck, 0, token);
	}while(!success);
}

/*#define SPIN_COUNT 200

inline void pushWork (volatile int * lck, int token)
{
	int success = CAS(lck, 0, token);

	while(!success)
	{
		for(int i = 0; i < SPIN_COUNT; i++) { pause();} restorepr();
		success = CAS(lck, 0, token);
	}
}*/

#define lock_init(lock) \
	lock->token = 0;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->token) 	\
	{	\
		switch(lock->token) 	/*Change to function handling messages?*/ \
		{ 			\
			case 1: \
				lock->token = 0;\
				fence();\
				x = x + 1; \
				break;\
		}\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->token, 1);

#define biased_unlock(lock) \
	fence(); 

#define non_dom_crit_sec() 


#endif



#ifdef QFPR

#include "../../lib/myqueue.h"

#undef startoffoo

#define startoffoo() \
	typedef void (*fp)(int*, volatile Lock*);\
	volatile int * m_Read = &lock->q->m_Read;\
	volatile int * m_Write = &lock->q->m_Write;\
	myqueue<fp> * q = lock->q

typedef void (*fp)(int*, volatile Lock*);

struct Lock {
	pthread_spinlock_t n;
	myqueue<fp> * q;
};

void (*func)(int * x, volatile Lock * l);

#define lock_init(lock) \
	lck->q = new myqueue<void (*)(int*, volatile Lock*)>;\
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->q->m_Read != lock->q->m_Write) 	\
	{\
		while(lock->q->popElement(&func)) func (&x, lock);	/*XXX: REVISIT*/\
	}
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); 

#define biased_unlock(lock) \
	fence();\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	func = &incx;	\
	while(!lock->q->pushElement(&func)) {pause();} restorepr(); 

#include <iostream>
#include "../lib/volatile_functions.h"

inline void incx (int * x, volatile Lock * l)
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*x) = (*x) + 1;
}

#endif

#ifdef MPQR

#include "../../lib/myqueue.h"

#undef startoffoo

#define startoffoo() \
	volatile int * m_Read = &lock->q->m_Read;\
	volatile int * m_Write = &lock->q->m_Write;\
	myqueue<int> * q = lock->q

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
	if(*m_Read != *m_Write) 	\
		while(q->popElement(&el)) /*XXX: REVISIT*/\
			switch(el)\
					{\
						case 1:\
							x = x + 1;\
							fence();\
							break;\
					}

#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); 

#define biased_unlock(lock) \
	fence();\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	el = 1;	\
	while(!q->pushElement(&el)) {pause();} restorepr(); 

#endif

#endif

#ifdef NEWFP 
typedef void (*fp)(int*, volatile Lock*);

#define CAS __sync_bool_compare_and_swap

struct Lock {
	pthread_spinlock_t n;
	void (*func)(int * y, volatile Lock * l);
	bool done;
};

inline void pushWork (volatile fp * lck, fp func)
{
	int success = 0;
	do
	{
		while (*lck != NULL); 
		success = CAS(lck, NULL, func);
	}while(!success);
}


#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (&x, lock);		/*XXX: REVISIT*/\
		lock->done = true;\
		fence();\
	}
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	lock-> done = false;\
	lock->func = &incy;
//	pushWork(&lock->func, &incy);	

#define biased_unlock(lock) \
	while(!lock->done){ pause();} restorepr();\
	pthread_spin_unlock(&(lock->n));\
	fence(); 

#define non_dom_crit_sec() 

inline void incy (int * y, volatile Lock * l)
{
	l->func = NULL;
	fence();
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif
#ifdef OHGOD

#include "../../lib/myqueue2.h"

#undef startoffoo

#define startoffoo() \
	typedef void (*fp)(int*, volatile Lock*);\
	myqueue<fp> * q = lock->q

typedef void (*fp)(int*, volatile Lock*);

struct Lock {
	pthread_spinlock_t n;
	myqueue<fp> * q;
};

void (*func)(int * x, volatile Lock * l);

#define lock_init(lock) \
	lck->q = new myqueue<void (*)(int*, volatile Lock*)>;\
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	while(q->popElement(&func)) func (&x, lock);	/*XXX: REVISIT*/
	
#define biased_lock(lock)

#define biased_unlock(lock) \
	fence();

#define non_dom_crit_sec() \
	func = &incx;	\
	q->pushElement(&func);

inline void incx (int * x, volatile Lock * l)
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*x) = (*x) + 1;
}

#endif

