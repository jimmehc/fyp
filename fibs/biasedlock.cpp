#include <sys/types.h>
#include "biasedlock.h"
#include <iostream>
#include <boost/thread/thread.hpp> 
#include <boost/thread.hpp> 
#include <sched.h>
#include <stdio.h>
#include "fibs.cpp"

inline void incy (int * y, Lock * l)
{
	(*y)++;
		asm volatile("mfence");
		l->done = 1;
		l->func = NULL;
}

void foo(threaddata * td)
{
	std::cout << fibs(10,td) << std::endl;
}	


#define NUM_THREADS 1	
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
