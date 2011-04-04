#include <sys/types.h>
#include "biasedlock.h"
#include <iostream>
#include "../../lib/mcs.h"
#include "../../lib/timing.h"
#include <sched.h>
#include <stdio.h>
#include "../constants.h"

unsigned long long start;

void foo(threaddata * td)
{
	qnode * I = new qnode;
	if(*td->threadid == 0)
	{
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
			acquire_lock(td->L, I);
			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
			*td->x = *td->x + 1;
			release_lock(td->L, I);
		}
	}
	else
	{
		for(int i = 0; i < NON_DOM_ACCESSES/NUM_THREADS; i++)
		{
			acquire_lock(td->L, I);
			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
			*td->x = *td->x + 1;
			release_lock(td->L, I);
		}
	}	
}	


int main()
{
	pthread_t threads[NUM_THREADS];
	
	qnode ** lck = new qnode*;
	//*lck = new qnode;
	
	threaddata j[NUM_THREADS];
	int * const x = new int(0);
	int * const y = new int(0);

	start = get_time();
	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
		j[i].y = y;
		j[i].L = lck;
		j[i].threadid = new int(i);
		
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	unsigned long long end = get_time();

	std::cout << "time: " << end - start << std::endl;

	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
