#ifndef BIASEDLOCK
#define BIASEDLOCK

#include <pthread.h>

struct Lock;

struct threaddata
{
	//private
	volatile int *threadid;

	//shared
	volatile Lock *lock;
	volatile int * x;
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
	pthread_spinlock_t n;
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE); 

#define biased_lock_owner(lock) pthread_spin_lock(&lock->n);

#define biased_unlock_owner(lock) pthread_spin_unlock(&lock->n);	

#define biased_lock(lock) pthread_spin_lock(&lock->n);
#define biased_unlock(lock)	pthread_spin_unlock(&(lock->n));

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

#define biased_lock_owner(lock) spinlock::lockN(&lock->n);

#define biased_unlock_owner(lock) spinlock::unlockN(&lock->n);	

#define biased_lock(lock) spinlock::lockN(&lock->n);
#define biased_unlock(lock)	spinlock::unlockN(&(lock->n));

#define non_dom_crit_sec() \
	(*td->x) = (*td->x) + 1;

#endif


#ifdef VAS
struct Lock {
	volatile pthread_spinlock_t n;
	volatile bool request;
	volatile bool grant;
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
		lock->request = false; \
		fence();\
		lock->grant = true;\
		while(lock->grant){pause();} restorepr(); \
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

#ifdef DUMMYFP
struct Lock {
	pthread_spinlock_t n;
	int done;
	void (*func)(volatile int * y, volatile Lock * l);
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		/*lock->func (td->x, lock);*/				/*XXX: REVISIT*/\
		*td->x = *td->x + 1; \
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
	td->lock->func = &incy;						/*XXX: REVISIT*/

inline void incy (volatile int * y, volatile Lock * l)		/* GENERALIZE? */
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
}

#endif

#ifdef DUMMYFP2
struct Lock {
	pthread_spinlock_t n;
	int done;
	int sig;
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->sig = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->sig != 0) 	\
	{	\
		/*lock->func (td->x, lock);*/				/*XXX: REVISIT*/\
		*td->x = *td->x + 1; \
		lock->sig = 0;\
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
	td->lock->sig = 1;						/*XXX: REVISIT*/

#endif

#ifdef FP
struct Lock {
	pthread_spinlock_t n;
	int done;
	void (*func)(volatile int * y, volatile Lock * l);
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;\
	lock->done = 1;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->x, lock);				/*XXX: REVISIT*/\
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
	td->lock->func = &incy;						/*XXX: REVISIT*/

inline void incy (volatile int * y, volatile Lock * l)		/* GENERALIZE? */
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
	void (*func)(volatile int * y, volatile Lock * l);
};

#define lock_init(lock) \
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);\
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->x, lock);		/*XXX: REVISIT*/\
		fence();\
	}
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); \
	while(lock->func != NULL){ pause();} restorepr(); 

#define biased_unlock(lock) \
	fence(); \
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->func = &incy;

inline void incy (volatile int * y, volatile Lock * l)
{
	l->func = NULL;
	fence();
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
	while(lock->token != 0) { pause();} restorepr();

#define biased_unlock(lock) \
	fence();\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	td->lock->token = 1;

#endif

#ifdef ISPL
typedef void (*fp)(volatile int*, volatile Lock*);

#define CAS __sync_bool_compare_and_swap

struct Lock {
	void (*func)(volatile int * y, volatile Lock * l);
};

inline void pushWork (volatile fp * lck, fp func)
{
	int success = 0;
	do
	{
		while (*lck != NULL) {pause();} restorepr(); 
		success = CAS(lck, NULL, func);
	}while(!success);
}

#define lock_init(lock) \
	lock->func = NULL;

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->func != NULL) 	\
	{	\
		lock->func (td->x, lock);		/*XXX: REVISIT*/\
		fence();\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->func, &incy);

#define biased_unlock(lock) \
	fence(); 

#define non_dom_crit_sec() 

inline void incy (volatile int * y, volatile Lock * l)
{
	l->func = NULL;
	fence();
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

inline void pushWork (volatile volatile int * lck, int token)
{
	int success = 0;
	do
	{
		while (*lck != 0) ;
		success = CAS(lck, 0, token){ pause();} restorepr();
	}while(!success);
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
				fence();\
				*td->x = *td->x + 1; \
				break;\
		}\
	}
	
#define biased_lock(lock) \
	pushWork(&lock->token, 1);

#define biased_unlock(lock) \
	fence(); 

#define non_dom_crit_sec() 


#endif

#ifdef QFP

#include "../../lib/myqueue.h"

typedef void (*fp)(volatile int*, volatile Lock*);

struct Lock {
	pthread_spinlock_t n;
	myqueue<fp> * q;
};

void (*func)(volatile int * y, volatile Lock * l);

#define lock_init(lock) \
	lck->q = new myqueue<void (*)(volatile int*, volatile Lock*)>;\
	pthread_spin_init(&lock->n, PTHREAD_PROCESS_PRIVATE);

#define biased_lock_owner(lock)  
#define biased_unlock_owner(lock)	\
	if(lock->q->m_Read != lock->q->m_Write) 	\
		while(lock->q->popElement(&func)) func (td->x, lock);	/*XXX: REVISIT*/
	
#define biased_lock(lock) \
	pthread_spin_lock(&(lock->n)); 

#define biased_unlock(lock) \
	fence();\
	pthread_spin_unlock(&(lock->n));

#define non_dom_crit_sec() \
	func = &incy;	\
	while(!td->lock->q->pushElement(&func)) {pause();} restorepr(); 

inline void incy (volatile int * y, volatile Lock * l)
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
	while(!td->lock->q->pushElement(&el)){pause();} restorepr(); 

#endif

#endif
