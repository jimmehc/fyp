#include <sys/types.h>
#include "biasedlock.h"
#include "../../lib/spinlock.h"
#include "../../lib/timing.h"
#include <iostream>
#include <sched.h>
#include <stdio.h>
#include "../constants.h"

unsigned long long start;

/*inline void biased_unlock_owner(threaddata * td) 
{ 
	if(td->lock->func != NULL) 
		td->lock->func(td->y,td->lock); 
}*/

inline void noop(int * y, Lock * l)
{}
/*inline void incy (int * const y, Lock * l)
{
	(*y)++;
	l->func = NULL;
	l->done = 1;
	asm volatile("mfence");
}*/

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
//		std::cout << "owner" << *(td->threadid) << std::endl;
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
		//	biased_lock_owner(td->lock, td->threadid);
			#ifdef DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
			*(td->x) = (*td->x) + 1;
			if(td->lock->token)
			{	
				switch(td->lock->token)
				{
					case 1:
						#ifdef DELAY
						for(int j = 0; j < DELAY; j++) ;
						#endif	
						*td->x = *td->x + 1;
						td->lock->token = 0;
						td->lock->done = 1;
						asm volatile("mfence");
						break;
				}
			}		
	//		biased_unlock_owner(td);
		}
//		std::cout << "dom thread done" << std::endl;
//		std::cout << *td->x << std::endl;
		//while(1) if(td->lock->func != NULL) td->lock->func(td->x, td->lock);
	}
	else
	{
		timespec * t = new timespec;
		t->tv_nsec = 10000;
		for(int i = 0; i < NON_DOM_ACCESSES; i++)
		{
			biased_lock(td->lock, td->threadid);
			td->lock->done = 0;
			//asm volatile ("mfence");
			td->lock->token = 1;
			asm volatile ("mfence");
			while(!(td->lock->done));
			biased_unlock(td->lock, td->threadid);
		//	nanosleep(t,NULL);
		}
//		std::cout << "time: " << get_time() - start << std::endl;
//		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	


#define NUM_THREADS 4	
int main()
{
	pthread_t threads[NUM_THREADS];
	
	Lock * lck = new Lock;
	lck->token = 0;
	lck->done = 1;


/*	int* padding[64];

	for(int i=0;i< 64; i++)
		padding[i] = new int(0);*/
	
	threaddata * j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);

/*	std::cout << "lck: " << lck << std::endl;
	std::cout << "x: " << x << std::endl;
	std::cout << "y: " << y << std::endl;
*/	
	start = get_time();
	for(int i = 0; i < NUM_THREADS; i++)
	{
		int * u = new int(i);
		j[i] = new threaddata;
		j[i]->x = x;	
		j[i]->y = y;
		j[i]->threadid = u;
		j[i]->lock = lck;

		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) j[i] );
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	unsigned long long end = get_time();

	std::cout << "time: " << end - start << std::endl;

//	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
