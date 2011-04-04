#include <sys/types.h>
#include "biasedlock.h"
#include "../../lib/spinlock.h"
#include "../../lib/timing.h"
#include <iostream>
#include <sched.h>
#include <stdio.h>
#include "../constants.h"


unsigned long long start;

void foo(threaddata * td)
{
	if(*td->threadid == 0)
	{
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
			pthread_mutex_lock(td->m);
			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
			*td->x = *td->x + 1;
			pthread_mutex_unlock(td->m);
		}
	}
	else
	{
		for(int i = 0; i < NON_DOM_ACCESSES/NUM_THREADS; i++)
		{
			pthread_mutex_lock(td->m);
			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
			*td->x = *td->x + 1;
			pthread_mutex_unlock(td->m);
		}
	}
}	

 			
int main()
{
	pthread_t threads[NUM_THREADS];
qnode ** lck1 = new qnode*;
	pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

	threaddata j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);

	start = get_time();

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
j[i].L = lck1; 
		j[i].y = y;
		j[i].m = &mymutex;
		j[i].threadid = new int(i);
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

//	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
