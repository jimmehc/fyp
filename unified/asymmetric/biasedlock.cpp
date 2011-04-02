#include <sys/types.h>
#include "biasedlock.h"
#include "../../lib/spinlock.h"
#include "../../lib/mcs.h"
#include "../../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include <sched.h>
#include <stdio.h>

unsigned long long start;

#define biased_lock_owner() while(td->lock->grant){asm volatile ("pause");}
#define biased_unlock_owner()	\
	if(td->lock->request) \
	{	\
		td->lock->request = false; \
		asm volatile ("mfence");\
		td->lock->grant = true;\
	}


#define biased_lock() \
	pthread_spin_lock(&(td->lock->n)); \
	td->lock->request = true; \
	while(!td->lock->grant){ asm volatile ("pause"); }
#define biased_unlock() \
	asm volatile ("mfence"); \
	td->lock->grant = false; \
	pthread_spin_unlock(&(td->lock->n));

void foo(threaddata * td)
{
	if(*(td->threadid) == 0)
	{
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
			biased_lock_owner();

			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
	
			*(td->x) = (*td->x) + 1;
		
			biased_unlock_owner();		
	
		}
//		std::cout << *td->x << std::endl;
//		std::cout << "dom thread done" << std::endl;
//		std::cout << *td->x << std::endl;
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

			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
			
			*(td->y) = (*td->y) + 1;

			biased_unlock();
//			nanosleep(t,NULL);	
		}
		td->done = true;
//		std::cout << "time: " << get_time() - start << std::endl;
//		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	

#define NUM_THREADS 4			
int main()
{
	pthread_t threads[NUM_THREADS];
	
	Lock * lck = new Lock;

	pthread_spin_init(&lck->n, PTHREAD_PROCESS_PRIVATE);
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
		j[i].done = false;
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}	
	pthread_join(threads[0], NULL);	//wait for dom thread

	for(int i = 1; i < NUM_THREADS; i++)
		if(!j[i].done)
			std::cout << "Tipping point hit, non dom threads not complete, x: " << *x << std::endl;

	unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	//std::cout << "x: " << *x << " y: " << *y << std::endl;
}
