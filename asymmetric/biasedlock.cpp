#include <sys/types.h>
#include "biasedlock.h"
#include "peterson.h"
#include "spinlock.h"
#include <iostream>
#include <boost/thread/thread.hpp> 
#include <boost/thread.hpp> 

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
		asm volatile ("mfence");
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
	if(*(td->threadid) == 0)
	{
		std::cout << "owner" << *(td->threadid) << std::endl;
		for(int i = 0; i < 60000000; i++)
		{
			biased_lock_owner(td->lock, td->threadid);
/*			std::cout << "owner has lock" << std::endl;
			sleep(1);
			std::cout << "owner still has lock" << std::endl;
			sleep(1);*/
			*(td->x) = (*td->x) + 1;
			biased_unlock_owner(td->lock, td->threadid);
//			boost::this_thread::sleep(boost::posix_time::microseconds(1));

		}
	}
	else
	{
//		std::cout << "notowner" << *(td->threadid) << std::endl;
		for(int i = 0; i < 2; i++)
		{
			biased_lock(td->lock, td->threadid);
/*			std::cout << "nonowner has lock " << (*td->threadid) << std::endl;
			sleep(1);
			std::cout << "nonowner still has lock " << (*td->threadid) << std::endl;
			sleep(1);*/
			*(td->y) = (*td->y) + 1;
			biased_unlock(td->lock, td->threadid);
			boost::this_thread::sleep(boost::posix_time::microseconds(10));
		}
	}
}	

#define NUM_THREADS 16			
int main()
{
	pthread_t threads[NUM_THREADS];
	
	int * flag = (int *) malloc(sizeof(int)*2);
	flag[0] = flag[1] = 0;
	int turn;

	Lock * lck = new Lock;
	lck->request = false;
	lck->grant = false;
	
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
