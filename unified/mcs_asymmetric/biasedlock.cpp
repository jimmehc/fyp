#include <sys/types.h>
#include "biasedlock.h"
#include "../../lib/spinlock.h"
#include "../../lib/mcs.h"
#include "../../lib/timing.h"
#include <iostream>
#include <sched.h>
#include <stdio.h>

unsigned long long start;

inline void biased_lock_owner(Lock * l, int * i)
{
	while (l->grant);
}

inline void biased_unlock_owner(Lock * l, int * i)
{
	if(l->request)
	{
		l->request = false;
		asm volatile ("mfence");
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
	asm volatile ("mfence");
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
				asm volatile ("mfence");
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
		td->done = true;
}	

 			
int main()
{
	pthread_t threads[NUM_THREADS];
	
	int * flag = (int *) malloc(sizeof(int)*2);
	flag[0] = flag[1] = 0;
	int turn;

	qnode ** lck = new qnode*;
	
	Lock * lock = new Lock;

	pthread_spin_init(&lck->n, PTHREAD_PROCESS_PRIVATE);
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
		j[i].done = false;
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}	
	pthread_join(threads[0], NULL);	//wait for dom thread

	for(int i = 1; i < NUM_THREADS; i++)
		if(!j[i].done)
			std::cout << "Tipping point hit, non dom threads not complete, x: " << *x << std::endl;

	unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
