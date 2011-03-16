#include <sys/types.h>
#include "biasedlock.h"
#include "../../lib/spinlock.h"
#include "../../lib/mcs.h"
#include "../constants.h"
#include <iostream>
#include <sched.h>
#include <stdio.h>
#include "/usr/local/papi/include/papi.h"

unsigned long long start;

/* timing code */
unsigned long long get_time()
{
 unsigned long lo,hi;
 __asm__ __volatile__("xorl %%eax,%%eax\n\
cpuid\n\
rdtsc" : "=a" (lo), "=d" (hi) : : "ebx", "ecx" );
 return ((unsigned long long)lo) + (unsigned long long)(hi<<32ULL);
}

#define biased_lock_owner() while(td->lock->grant){asm volatile ("pause");}
#define biased_unlock_owner()	\
	if(td->lock->request) \
	{	\
		td->lock->request = false; \
		asm volatile ("mfence");\
		td->lock->grant = true;\
		while(td->lock->grant){asm volatile ("pause");} \
	}


#define biased_lock() \
	spinlock::lockN(&(td->lock->n)); \
	td->lock->request = true; \
	while(!td->lock->grant){ asm volatile ("pause"); }
#define biased_unlock() \
	asm volatile ("mfence"); \
	td->lock->grant = false; \
	spinlock::unlockN(&(td->lock->n));

void foo(threaddata * td)
{
	if(*(td->threadid) == 0)
	{
		std::cout << "owner" << *(td->threadid) << std::endl;
		#ifdef CACHE_MISSES
		int events[1] = {PAPI_L1_DCM};
		PAPI_start_counters(events, 1);
		#endif
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
//			biased_lock_owner();
		
			*(td->x) = (*td->x) + 1;
		
			biased_unlock_owner();		
	
		}
		#ifdef CACHE_MISSES
		long long values[1];
		PAPI_read_counters(values, 1);
		std::cout << "L1 Data Cache Misses: " << values[0] << std::endl;
		#endif
		std::cout << "dom thread done" << std::endl;
		std::cout << *td->x << std::endl;
/*		while(1)
		{
			biased_unlock_owner();
		}
*/	}
	else
	{
		qnode * I = new qnode;
		timespec * t = new timespec;
		t->tv_nsec = 1;
		for(int i = 0; i < NON_DOM_ACCESSES; i++)
		{
			biased_lock();

			*(td->x) = (*td->x) + 1;

			biased_unlock();
//			nanosleep(t,NULL);	
		}
		std::cout << "time: " << get_time() - start << std::endl;
		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	

#define NUM_THREADS 4			
int main()
{
	pthread_t threads[NUM_THREADS];
	
	Lock * lck = new Lock;
	lck->request = false;
	lck->grant = false;

#if DEBUG
	std::cout << &lck->n << std::endl;
	std::cout << &lck->request << std::endl;
	std::cout << &lck->grant << std::endl;
#endif	
	threaddata j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);
	
#if DEBUG
	std::cout << x << std::endl;
	std::cout << y << std::endl;
#endif
	start = get_time();

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
		j[i].y = y;
		j[i].lock = lck;
		j[i].threadid = new int(i);
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
