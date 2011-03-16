#include <sys/types.h>
#include "biasedlock.h"
#include <iostream>
#include "mcs.h"
#include <boost/thread/thread.hpp> 
#include <boost/thread.hpp> 
#include <sched.h>
#include <stdio.h>

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
	qnode * I = new qnode;
	if(*td->threadid == 0)
	{
		for(int i = 0; i < 1000000000; i++)
		{
			acquire_lock(td->L, I);
			*td->x = *td->x + 1;
			release_lock(td->L, I);
		}
	}
	else
	{
		for(int i = 0; i < 100000; i++)
		{
			acquire_lock(td->L, I);
			*td->x = *td->x + 1;
			release_lock(td->L, I);
		}
	}	
}	


#define NUM_THREADS 128	
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
