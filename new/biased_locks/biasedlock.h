#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <pthread.h>
#include "../lib/myspinlock.h"

struct Lock;

struct threaddata
{
	//private
	volatile int *threadid;

	//shared
	volatile Lock *lock;
	volatile long * x;
	volatile bool done;
};

#ifdef CONTROL
struct Lock {
};

#define lock_init(lock) 

#define biased_lock_owner(lock) 
#define biased_unlock_owner(lock)

#define biased_lock(lock) 
#define biased_unlock(lock)

#define non_dom_crit_sec() \

#endif


#ifdef SPL 
struct Lock {
	volatile int n;
};

#define lock_init(lock) \
	lock->n = 0;

#define biased_lock_owner(lock) spinlock::lockN(&lock->n);

#define biased_unlock_owner(lock) spinlock::unlockN(&lock->n);	

#define biased_lock(lock) spinlock::lockN(&lock->n);
#define biased_unlock(lock)	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	(*td->x) = (*td->x) + 1;

#endif

#ifdef MYSPL 

#include "../lib/myspinlock.h"

struct Lock {
	int n;
};

#define lock_init(lock) \
	lock->n = 0;

#define biased_lock_owner(lock) spinlock::lockN(&lock->n, 400);

#define biased_unlock_owner(lock) spinlock::unlockN(&lock->n);	

#define biased_lock(lock) spinlock::lockN(&lock->n, 400);
#define biased_unlock(lock)	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	(*td->x) = (*td->x) + 1;

#endif


#ifdef VAS
struct Lock {
	volatile int n;
	volatile bool request;
	volatile bool grant;
};

#define lock_init(lock) \
	lock->n = 0;\
	lock->request = false; \
	lock->grant = false;

#define biased_lock_owner(lock) while(lock->grant){asm volatile ("pause");}
#define biased_unlock_owner(lock)	\
	if(lock->request) \
	{	\
		lock->request = false; \
		asm volatile ("mfence");\
		lock->grant = true;\
	}

#define biased_lock(lock) \
	spinlock::lockN(&lock->n); \
	lock->request = true; \
	while(!lock->grant){ asm volatile ("pause"); }
#define biased_unlock(lock) \
	asm volatile ("mfence"); \
	lock->grant = false; \
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	(*td->x) = (*td->x) + 1;

#endif

#ifdef VASVAR
struct Lock {
	volatile int n;
	bool request;
	bool grant;
};

#define lock_init(lock) \
	lock->n = 0;\
	lock->request = false; \
	lock->grant = false;

#define biased_lock_owner(lock) 
#define biased_unlock_owner(lock)	\
	if(lock->request) \
	{	\
		lock->request = false; \
		asm volatile ("mfence");\
		lock->grant = true;\
		while(lock->grant){asm volatile ("pause");}\
	}

#define biased_lock(lock) \
	spinlock::lockN(&lock->n); \
	lock->request = true; \
	while(!lock->grant){ asm volatile ("pause"); }
#define biased_unlock(lock) \
	asm volatile ("mfence"); \
	lock->grant = false; \
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	(*td->x) = (*td->x) + 1;

#endif

#ifdef DUMMYFP
struct Lock {
	volatile int n;
	int done;
	void (*func)(volatile long * y, volatile Lock * l);
};

#define lock_init(lock) \
	lock->n = 0;\
	lock->func = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		/*lock->func (td->x, lock);*/				/*XXX: REVISIT*/\
		*td->x = *td->x + 1; \
		lock->func = NULL;\
		asm volatile("mfence");\
		lock->done = 1;\
	}
	
#define biased_lock(lock) \
	spinlock::lockN(&lock->n); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ asm volatile ("pause");}\
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incy;						/*XXX: REVISIT*/

inline void incy (volatile long * y, volatile Lock * l)		/* GENERALIZE? */
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef DUMMYFP2
struct Lock {
	volatile int n;
	int done;
	int sig;
};

#define lock_init(lock) \
	lock->n = 0;\
	lock->sig = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->sig != 0) 	\
	{	\
		/*lock->func (td->x, lock);*/				/*XXX: REVISIT*/\
		*td->x = *td->x + 1; \
		lock->sig = 0;\
		asm volatile("mfence");\
		lock->done = 1;\
	}
	
#define biased_lock(lock) \
	spinlock::lockN(&lock->n); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ asm volatile ("pause");}\
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->sig = 1;						/*XXX: REVISIT*/

#endif

#ifdef FP
struct Lock {
	volatile int n;
	int done;
	void (*func)(volatile long * y, volatile Lock * l);
};

#define lock_init(lock) \
	lock->n = 0;\
	lock->func = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->x, lock);				/*XXX: REVISIT*/\
		lock->func = NULL;\
		asm volatile("mfence");\
		lock->done = 1;\
	}
	
#define biased_lock(lock) \
	spinlock::lockN(&lock->n); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ asm volatile ("pause");}\
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incy;						/*XXX: REVISIT*/

inline void incy (volatile long * y, volatile Lock * l)		/* GENERALIZE? */
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef AFP
struct Lock {
	volatile int n;
	void (*func)(volatile long * y, volatile Lock * l);
};

#define lock_init(lock) \
	lock->n = 0;\
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->x, lock);		/*XXX: REVISIT*/\
		asm volatile("mfence");\
	}
	
#define biased_lock(lock) \
	spinlock::lockN(&lock->n); \
	while(lock->func != NULL){ asm volatile ("pause");}

#define biased_unlock(lock) \
	asm volatile ("mfence"); \
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incy;

inline void incy (volatile long * y, volatile Lock * l)
{
	l->func = NULL;
	asm volatile ("mfence");
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef MP
struct Lock {
	volatile int n;
	int done;
	int token;
};

#define lock_init(lock) \
	lock->n = 0;\
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
				asm volatile("mfence");\
				break;\
		}\
	}	
	
#define biased_lock(lock) \
	spinlock::lockN(&lock->n); \
	lock->done = 0;

#define biased_unlock(lock) \
	while((!lock->done)){ asm volatile ("pause");}\
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->token = 1;

#endif

#ifdef AMP
struct Lock {
	volatile int n;
	int token;
};

#define lock_init(lock) \
	lock->n = 0;\
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
	spinlock::lockN(&lock->n); \
	while(lock->token != 0) { asm volatile ("pause"); }

#define biased_unlock(lock) \
	asm volatile("mfence");\
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->token = 1;

#endif

#ifdef ISPL
typedef void (*fp)(volatile long*, volatile Lock*);

#define CAS __sync_bool_compare_and_swap

struct Lock {
	void (*func)(volatile long * y, volatile Lock * l);
};

#undef SPIN_COUNT
#define SPIN_COUNT 400
inline void pushWork (volatile fp * lck, fp func)
{
	int success = 0;
	success = CAS(lck, NULL, func);
	while(!success)	
	{
		for(int i = 0; i < SPIN_COUNT; i++){ asm volatile ("pause");}
		success = CAS(lck, NULL, func);
	}
}

#define lock_init(lock) \
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->x, lock);		/*XXX: REVISIT*/\
		asm volatile("mfence");\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->func, &incy);

#define biased_unlock(lock) \
	asm volatile ("mfence"); 

#define non_dom_crit_sec() 

inline void incy (volatile long * y, volatile Lock * l)
{
	l->func = NULL;
	asm volatile ("mfence");
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef ISPLMP
#define CAS __sync_bool_compare_and_swap

struct Lock {
	int token;
};

inline void pushWork (volatile int * lck, int token)
{
	int success = 0;
	success = CAS(lck, 0, token);
	while(!success)	
	{
		for(int i = 0; i < SPIN_COUNT; i++){ asm volatile ("pause");}
		success = CAS(lck, 0, token);
	}
}

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
				asm volatile("mfence");\
				*td->x = *td->x + 1; \
				break;\
		}\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->token, 1);

#define biased_unlock(lock) \
	asm volatile ("mfence"); 

#define non_dom_crit_sec() 


#endif

#ifdef QFP

#include "../../lib/myqueue.h"

typedef void (*fp)(volatile long*, volatile Lock*);

struct Lock {
	volatile int n;
	myqueue<fp> * q;
};

void (*func)(volatile long * y, volatile Lock * l);

#define lock_init(lock) \
	lck->q = new myqueue<void (*)(volatile long*, volatile Lock*)>;\
	lock->n = 0;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->q->m_Read != lock->q->m_Write) 	\
		while(lock->q->popElement(&func)) func (td->x, lock);	/*XXX: REVISIT*/
	
#define biased_lock(lock) \
	spinlock::lockN(&lock->n); 

#define biased_unlock(lock) \
	asm volatile ("mfence");\
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	func = &incy;	\
	while(!td->lock->q->pushElement(&func));

inline void incy (volatile long * y, volatile Lock * l)
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef MPQ

#include "../../lib/myqueue.h"

struct Lock {
	volatile int n;
	myqueue<int> * q;
};
int el;

#define lock_init(lock) \
	lck->q = new myqueue<int>;\
	lock->n = 0;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->q->m_Read != lock->q->m_Write) 	\
		while(lock->q->popElement(&el)) /*XXX: REVISIT*/\
			switch(el)\
					{\
						case 1:\
							(*td->x) = (*td->x) + 1;\
							asm volatile("mfence");\
							break;\
					}

#define biased_lock(lock) \
	spinlock::lockN(&lock->n); 

#define biased_unlock(lock) \
	asm volatile ("mfence");\
	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	el = 1;	\
	while(!td->lock->q->pushElement(&el));

#endif

#endif

#ifdef ISPLBL
typedef void (*fp)(volatile long*, volatile Lock*);

#define CAS __sync_bool_compare_and_swap

struct Lock {
	void (*func)(volatile long * y, volatile Lock * l);
	bool done;
};
#define SPIN_COUNT 400
inline void pushWork (volatile fp * lck, fp func)
{
	int success = 0;
	success = CAS(lck, NULL, func);
	while(!success)	
	{
		for(int i = 0; i < SPIN_COUNT; i++){ asm volatile ("pause");}
		success = CAS(lck, NULL, func);
	}
}

#define lock_init(lock) \
	lock->done = true;\
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->x, lock);		/*XXX: REVISIT*/\
		lock->done = true;\
		asm volatile("mfence");\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->func, &incy);\
	while(lock->func != NULL) {asm volatile("pause");}\
	while(!lock->done) { asm volatile ("pause");}

#define biased_unlock(lock) \
	asm volatile ("mfence"); 

#define non_dom_crit_sec() 

inline void incy (volatile long * y, volatile Lock * l)
{
	l->done = false;
	l->func = NULL;
	asm volatile ("mfence");
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef ISPLMPBL
#define CAS __sync_bool_compare_and_swap

struct Lock {
	int token;
	bool done;
};

inline void pushWork (volatile int * lck, int token)
{
	int success = 0;
	success = CAS(lck, 0, token);
	while(!success)	
	{
		for(int i = 0; i < SPIN_COUNT; i++){ asm volatile ("pause");}
		success = CAS(lck, 0, token);
	}
}

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
				asm volatile("mfence");\
				*td->x = *td->x + 1; \
				break;\
		}\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->token, 1);

#define biased_unlock(lock) \
	asm volatile ("mfence"); 

#define non_dom_crit_sec() 


#endif

