#include <sys/types.h>
#include "biasedlock.h"
#include <iostream>
#include "myqueue.h"
#include "spinlock.h"
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

/*inline void biased_unlock_owner(threaddata * td) 
{ 
	if(td->lock->func != NULL) 
		td->lock->func(td->y,td->lock); 
}*/

inline void noop(int * y, Lock * l)
{}
inline void incy (int * const y, Lock * l)
{
	(*y)++;
	l->done = 1;
	asm volatile("sync");
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
	void (*fp)(int * y, Lock * l);
	if(*(td->threadid) == 0)
	{
		std::cout << "owner" << *(td->threadid) << std::endl;
		for(int i = 0; i < 1000000000; i++)
		{
		//	biased_lock_owner(td->lock, td->threadid);
			*(td->x) = (*td->x) + 1;
			if(td->lock->q->m_Read != td->lock->q->m_Write)
				while(td->lock->q->popElement(&fp)) fp(td->x, td->lock);
	//		biased_unlock_owner(td);
		}
		std::cout << "dom thread done" << std::endl;
		std::cout << *td->x << std::endl;
	}
	else
	{
		timespec * t = new timespec;
		t->tv_nsec = 10000;
		for(int i = 0; i < 33333333; i++)
		{
			biased_lock(td->lock, td->threadid);
			//asm volatile ("sync");i
			fp = &incy;
			while(!td->lock->q->pushElement(&fp));
			//asm volatile ("sync");
			biased_unlock(td->lock, td->threadid);
//			nanosleep(t,NULL);
		}
		std::cout << "time: " << get_time() - start << std::endl;
		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	


#define NUM_THREADS 4	
int main()
{
	pthread_t threads[NUM_THREADS];
	
	Lock * lck = new Lock;
	lck->q = new myqueue<void (*)(int*, Lock*)>;
	lck->done = 1;

	threaddata * j[NUM_THREADS];
	int * x = new int(0);
	int * y = new int(0);

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

	std::cout << "x: " << *x << " y: " << *y << std::endl;
	}
