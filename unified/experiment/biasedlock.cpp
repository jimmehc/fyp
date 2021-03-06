#include <sys/types.h>
#include "biasedlock.h"
#include "../../lib/spinlock.h"
#include "../../lib/timing.h"
#include <iostream>
#include <sched.h>
#include <stdio.h>
#include "../constants.h"

unsigned long long start;
/*
inline void biased_unlock_owner(threaddata * td) 
{ 
	if(td->lock->func != NULL) 
		td->lock->func(td->y,td->lock); 
}*/

inline void noop(int * y, volatile Lock * l)
{}
inline void incy (int * y, volatile Lock * l)
{
	#if DELAY
	for(int j = 0; j < DELAY; j++) ;
	#endif	
	(*y) = (*y) + 1;
	l->func = NULL;
	l->done = 1;
	asm volatile("mfence");
}

inline void biased_lock(volatile Lock * l, int * i)
{
	pthread_spin_lock(&(l->n));
}

inline void biased_unlock(volatile Lock * l, int * i)
{
	pthread_spin_unlock(&(l->n));
}

void foo(threaddata * td)
{
	if(*(td->threadid) == 0)
	{
		int x = 0;
//		std::cout << "owner" << *(td->threadid) << std::endl;
		for(int i = 0; i < DOM_ACCESSES; i++)
		{
		//	biased_lock_owner(td->lock, td->threadid);
	//		if(td->lock->func != NULL) td->lock->func (td->x, td->lock);
			#if DELAY
			for(int j = 0; j < DELAY; j++) ;
			#endif	
			x++;
			if(td->lock->func != NULL) td->lock->func (&x, td->lock);

	//		biased_unlock_owner(td);
		}
		std::cout << "dom thread done" << " x == " << x << std::endl;
//		std::cout << "time: " << get_time() - start << std::endl;
//		std::cout << *td->x << std::endl;
		//while(1) if(td->lock->func != NULL) td->lock->func(td->x, td->lock);
	}
	else
	{
		timespec * t = new timespec;
		t->tv_nsec = 1;
		for(int i = 0; i < NON_DOM_ACCESSES; i++)
		{
			biased_lock(td->lock, td->threadid);
			td->lock->done = 0;
			//asm volatile ("mfence");
			td->lock->func = &incy;
			asm volatile ("mfence");
			while((!td->lock->done)){ asm volatile ("pause");}
			biased_unlock(td->lock, td->threadid);
//			nanosleep(t,NULL);
		}
		td->done = true;
//		std::cout << "time: " << get_time() - start << std::endl;
//		std::cout << "thread " << *(td->threadid) << " done" << std::endl;
	}
}	


 
int main()
{
	pthread_t threads[NUM_THREADS];
	
	volatile Lock * lck = new Lock;

	pthread_spin_init(&lck->n, PTHREAD_PROCESS_PRIVATE);
	lck->func = NULL;
	lck->done = 1;

//	int * wat = new int(1);
//	int * wat2 = new int(1);

//	std::cout << &lck->n <<std::endl;

/*	int* padding[64];

	for(int i=0;i< 64; i++)
		padding[i] = new int(0);*/
	
	threaddata * j[NUM_THREADS];

	void (*fp)(int * y, volatile Lock * l) = &incy;

/*	std::cout << "lck: " << lck << std::endl;
	std::cout << "lck->func: " << lck->func << std::endl;
	std::cout << "incy: " << &fp << std::endl;
	std::cout << "x: " << x << std::endl;
	std::cout << "y: " << y << std::endl;*/
	
	start = get_time();
	for(int i = 0; i < NUM_THREADS; i++)
	{
		int * u = new int(i);
		j[i] = new threaddata;
		j[i]->done = false;
		j[i]->threadid = u;
		j[i]->lock = lck;

		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) j[i] );
	}	
	pthread_join(threads[0], NULL);	//wait for dom thread

	for(int i = 1; i < NUM_THREADS; i++)
		if(!j[i]->done)
			std::cout << "Tipping point hit, non dom threads not complete, "<< std::endl;

	unsigned long long end = get_time();

	std::cout << "time: " << end - start << std::endl;

//	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
