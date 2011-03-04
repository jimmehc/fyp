#include <sys/types.h>
#include "biasedlock.h"
#include "spinlock.h"
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
		asm volatile ("mfence");
		l->grant = true;
	}
}

inline void biased_lock(Lock * l, int * i)
{
	spinlock::lockN(&(l->n));
	l->request = true;
	while(!l->grant);
}

void biased_unlock(Lock * l, int * i)
{
	asm volatile ("mfence");
	l->grant = false;
	spinlock::unlockN(&(l->n));
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
			asm volatile ("mfence");
			while (td->lock->flag[!*(td->threadid)] == true)
			{
				if(td->lock->turn == *(td->threadid))
				{
					td->lock->flag[*(td->threadid)] = false;
					while(td->lock->turn != *(td->threadid));
					td->lock->flag[*(td->threadid)] = true;
					asm volatile ("mfence");
				}
			}
			asm volatile ("mfence");
					
			while (td->lock->grant);

			*(td->x) = (*td->x) + 1;
		//	biased_unlock_owner(td->lock, td->threadid);
			
			if(td->lock->request)
			{
				td->lock->request = false;
				asm volatile ("mfence");
				td->lock->grant = true;
			}
			asm volatile ("mfence");
			td->lock->turn == !*(td->threadid);
			td->lock->flag[*td->threadid] = false;
		}
		std::cout << "dom thread " << *(td->threadid) << " done" << std::endl;
/*		while(1)
			if(td->lock->request)
			{	
	        		td->lock->request = false;
			        asm volatile ("mfence");
				td->lock->grant = true;
			}*/
	}
	else
	{
		timespec * t = new timespec;
		t->tv_nsec = 1;
		for(int i = 0; i < 33333; i++)
		{
			biased_lock(td->lock, td->threadid);
			*(td->x) = (*td->x) + 1;
			biased_unlock(td->lock, td->threadid);
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
