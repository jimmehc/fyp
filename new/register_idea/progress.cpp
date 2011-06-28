#include "biasedlock.h"
#include "../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include <pthread.h>

volatile unsigned long long start;

void foo(threaddata * td)
{
	int x = 0;
	volatile Lock * lock = td->lock;
	for(int i = 0; i < DOM_ACCESSES; i++)
	{
		for(volatile int j = 0; j < 1; j++);
		biased_lock_owner(lock);

		x = x + 1;
	
		biased_unlock_owner(lock);		
	}
	*td->x = x;
}
	

void bar(threaddata * td)
{
	volatile Lock * lock = td->lock;
	td->done = true;
	for(;;)
	{
		biased_lock(lock);

		non_dom_crit_sec();

		biased_unlock(lock);
		for(volatile int j = 0; j < (NDD*(NUM_THREADS - 1)); j++);
	}
}	

int main()
{
	pthread_t threads[NUM_THREADS];

	volatile Lock * lck = new Lock;

	lock_init(lck);

	threaddata j[NUM_THREADS];

	volatile int * x = new int(0);

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
		j[i].lock = lck;
		j[i].threadid = new int(i);
		j[i].done = false;
	}	

	start = get_time();

	pthread_create(&threads[0], NULL, (void* (*)(void*)) foo, (void *) &j[0] );

	for(int i = 1; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, (void* (*)(void*)) bar, (void *) &j[i] );

	pthread_join(threads[0], NULL);	//wait for dom thread

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << *x << std::endl;

	std::cout << "total progress: " << ((double)(*x)/(double)(end-start))*1000 << " accesses per 1000 cycles" << std::endl;
	std::cout << "dom progress: " << ((double)(DOM_ACCESSES)/(double)(end-start))*1000 << " accesses per 1000 cycles" << std::endl;
	std::cout << "non-dom progress: " << ((double)(*x - DOM_ACCESSES)/(double)(end-start))*1000 << " accesses per 1000 cycles" << std::endl;
	std::cout << "actual dominance percentage: " << (double)DOM_ACCESSES/(double)(*x) << std::endl;
}
