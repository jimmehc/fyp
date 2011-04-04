#include <sys/types.h>
#include "biasedlock.h"
#include "../../spinlock.h"
#include "../../timing.h"
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
		asm volatile ("sync");
		l->grant = true;
	}
}

inline void biased_lock(Lock * l, int * i)
{
	acquire_lock(td->L, I);
	l->request = true;
	while(!l->grant);
}

void biased_unlock(Lock * l, int * i)
{
	asm volatile ("sync");
	l->grant = false;
	release_lock(td->L, I);
}

void foo(threaddata * td)
{
	if(*(td->threadid) == 0 || *(td->threadid) == 1)
	{
		std::cout << "owner" << *(td->threadid) << std::endl;
		for(int i = 0; i < 5000000; i++)
		{
			//biased_lock_owner(td->lock, td->threadid);
			td->lock->flag[*(td->threadid)] = true;
			asm volatile ("sync");
			while (td->lock->flag[!*(td->threadid)] == true)
			{
				if(td->lock->turn == *(td->threadid))
				{
					td->lock->flag[*(td->threadid)] = false;
					while(td->lock->turn != *(td->threadid));
					td->lock->flag[*(td->threadid)] = true;
					asm volatile ("sync");
				}
			}
			asm volatile ("sync");
					
			while (td->lock->grant);

			*(td->x) = (*td->x) + 1;
		//	biased_unlock_owner(td->lock, td->threadid);
			
			if(td->lock->request)
			{
				td->lock->request = false;
				asm volatile ("sync");
				td->lock->grant = true;
			}
			asm volatile ("sync");
			td->lock->turn == !*(td->threadid);
			td->lock->flag[*td->threadid] = false;
		}
		std::cout << "dom thread " << *(td->threadid) << " done" << std::endl;
/*		while(1)
			if(td->lock->request)
			{	
	        		td->lock->request = false;
			        asm volatile ("sync");
				td->lock->grant = true;
			}*/
	}
	else
	{
		timespec * t = new timespec;
qnode * I = new qnode;
		t->tv_nsec = 1;
		for(int i = 0; i < 33333; i++)
		{
			acquire_lock(td->L, I);
			*(td->x) = (*td->x) + 1;
			release_lock(td->L, I);
			nanosleep(t,NULL);	
		}
		std::cout << "time: " << get_time() - start << std::endl;
		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	

#define NUM_THREADS 2			
int main()
{
	pthread_t threads[NUM_THREADS];
qnode ** lck1 = new qnode*;
	
	int * flag = (int *) malloc(sizeof(int)*2);
	flag[0] = flag[1] = 0;
	int turn;

	Lock * lck = new Lock;

	
	lck->request = false;
	lck->grant = false;
	lck->flag[0] = false;
	lck->flag[1] = false;
	lck->turn = false;

	
	threaddata j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);

	start = get_time();

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
j[i].L = lck1; 
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
