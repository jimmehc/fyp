#include <sys/types.h>
#include "biasedlock.h"
#include "spinlock.h"
#include <iostream>
#include <sched.h>
#include <stdio.h>
#include "../constants.h"


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

void foo(threaddata * td)
{
	if(*td->threadid == 0)
	{
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
			pthread_mutex_lock(td->m);
			*td->x = *td->x + 1;
			pthread_mutex_unlock(td->m);
		}
	}
	else
	{
		for(int i = 0; i < NON_DOM_ACCESSES; i++)
		{
			pthread_mutex_lock(td->m);
			*td->x = *td->x + 1;
			pthread_mutex_unlock(td->m);
		}
	}
}	

#define NUM_THREADS 4			
int main()
{
	pthread_t threads[NUM_THREADS];
	pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;

	threaddata j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);

	start = get_time();

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
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
