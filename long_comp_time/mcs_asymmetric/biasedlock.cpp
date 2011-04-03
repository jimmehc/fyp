#include <sys/types.h>
#include "biasedlock.h"
#include "spinlock.h"
#include "mcs.h"
#include <iostream>
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


inline void biased_lock_owner(Lock * l, int * i)
{
	while (l->grant);
}

inline void biased_unlock_owner(Lock * l, int * i)
{
	if(l->request)
	{
		l->request = false;
		asm volatile ("sync");
		l->grant = true;
	}
}

inline void biased_lock(qnode * I, qnode ** L, Lock * l)
{
	acquire_lock(L,I);
	l->request = true;
	while(!l->grant);
}

void biased_unlock(qnode * I, qnode ** L, Lock * l)
{
	asm volatile ("sync");
	l->grant = false;
	release_lock(L,I);
}


void foo(threaddata * td)
{
	if(*(td->threadid) == 0)
	{
		std::cout << "owner" << *(td->threadid) << std::endl;
		for(int i = 0; i < 1000000000; i++)
		{
			while (td->lock->grant);
	
			/* start critical section */
				
			*(td->x) = (*td->x) + 1;
			
			/* end critical section */

			if(td->lock->request)
			{
				td->lock->request = false;
				asm volatile ("sync");
				td->lock->grant = true;
			}
		}
		std::cout << "dom thread done" << std::endl;
	}
	else
	{
		qnode * I = new qnode;
		timespec * t = new timespec;
		t->tv_nsec = 1;
		for(int i = 0; i < 3333333; i++)
		{
			biased_lock(I, td->L, td->lock);
			*(td->x) = (*td->x) + 1;
			biased_unlock(I, td->L, td->lock);
		//	nanosleep(t,NULL);	
		}
		std::cout << "time: " << get_time() - start << std::endl;
		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	

#define NUM_THREADS 4			
int main()
{
	pthread_t threads[NUM_THREADS];
	
	int * flag = (int *) malloc(sizeof(int)*2);
	flag[0] = flag[1] = 0;
	int turn;

	qnode ** lck = new qnode*;
	
	Lock * lock = new Lock;
	lock->request = false;
	lock->grant = false;
	
	threaddata j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);

	start = get_time();

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
		j[i].y = y;
		j[i].L = lck;
		j[i].lock = lock;
		j[i].threadid = new int(i);
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
