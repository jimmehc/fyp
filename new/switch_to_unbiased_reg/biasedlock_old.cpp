#include "biasedlock.h"
#include "../../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include "../lib/volatile_functions.h"
#include <pthread.h>

volatile unsigned long long start;

void foo(threaddata * td)
{
	int x = 0;
	volatile Lock * lock = td->lock;
	startoffoo();
	if(*(td->threadid) == 0)
	{
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
			biased_lock_owner(lock);

			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
	
			x = x + 1;
		
			biased_unlock_owner(lock);		
	
		}
		std::cout << "x == " << x << std::endl;
#ifndef AITP
		while(!td->done)
		{
			biased_unlock_owner(lock);
		}
#endif
	}
	else
	{
		timespec * t = new timespec;
		t->tv_nsec = 1;
		for(int i = 0; i < NON_DOM_ACCESSES; i++)
		{
			biased_lock(lock);

			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	

			non_dom_crit_sec();

			biased_unlock(lock);
//			nanosleep(t,NULL);	
		}
		td->done = true;
//		std::cout << "time: " << get_time() - start << std::endl;
//		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	

 			
int main()
{
	pthread_t threads[NUM_THREADS];

	Lock * lck = new Lock;

	lock_init(lck);

	threaddata j[NUM_THREADS];
	
	start = get_time();

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].lock = lck;
		j[i].threadid = new int(i);
		j[i].done = false;
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}

#ifdef AITP		//Abandon if Tipping Point
	pthread_join(threads[0], NULL);	//wait for dom thread

	for(int i = 1; i < NUM_THREADS; i++)
		if(!j[i].done)
			std::cout << "Tipping point hit, non dom threads not complete, x: " << *x << std::endl;

#else
	for(int i = 1; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	j[0].done = true;
	fence();
	//std::cout << "done should now be true " << &j[0].done << std::endl;
	pthread_join(threads[0], NULL);
#endif

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;
}
