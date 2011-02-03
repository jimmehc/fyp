#include <sys/types.h>
#include "biasedlock.h"
#include "spinlock.h"
#include <iostream>
#include <boost/thread/thread.hpp> 
#include <boost/thread.hpp> 
#include <sched.h>
#include <stdio.h>


inline void biased_unlock_owner(threaddata * td) 
{ 
	if(td->lock->func != NULL) 
		td->lock->func(td->y,td->lock); 
}

inline void noop(int * y, Lock * l)
{}
inline void incy (int * y, Lock * l)
{
	(*y)++;
		asm volatile("mfence");
		l->done = 1;
		l->func = NULL;
}

inline void biased_lock(Lock * l, int * i)
{
	spinlock::lockN(&(l->n));
}

inline void biased_unlock(Lock * l, int * i)
{
	spinlock::unlockN(&(l->n));
}

void foo(threaddata * td)
{
	if(*(td->threadid) == 0)
	{
		std::cout << "owner" << *(td->threadid) << std::endl;
		for(int i = 0; i < 120000000; i++)
		{
		//	biased_lock_owner(td->lock, td->threadid);
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			*(td->x) = (*td->x) + 1;
			if(td->lock->func != NULL) td->lock->func (td->y, td->lock);
	//		biased_unlock_owner(td);
		}
		std::cout << "dom thread done" << std::endl;
	}
	else
	{
		for(int i = 0; i < 2; i++)
		{
			biased_lock(td->lock, td->threadid);
			td->lock->done = 0;
			//asm volatile ("mfence");
			td->lock->func = &incy;
			while(!(td->lock->done));
			biased_unlock(td->lock, td->threadid);
			usleep(100);	
		}
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

	Lock * lck = new Lock;
	lck->request = false;
	lck->grant = false;
	lck->func = NULL;
	lck->done = 1;

	threaddata j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);
	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].x = x;
		j[i].y = y;
		j[i].lock = lck;
		j[i].threadid = new int(i);
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
