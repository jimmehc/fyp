#include "biasedlock.h"
#include "../lib/biased_sync.h"
#include "../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include "../lib/volatile_functions.h"
#include <pthread.h>
#include <cstdlib>

#include "../lib/myspinlock.h"

volatile unsigned long long start;

void inc(shared_data<int> * sd, void * params = NULL){
	sd->d++;
}

void foo(threaddata<int> * td)
{
	#if defined (FP) || (AFP) || (ISPL) || (FPQ) || (BQ) || (VAS)
	for(int i = 0; i < DOM_ACCESSES; i++)
		critical_section(td->threadid, &inc, td->sd);
	#elif defined SPL
	for(int i = 0; i < DOM_ACCESSES; i++)
	{
		spinlock::lockN(td->sd->l.n);
		td->sd->d++;
		spinlock::unlockN(td->sd->l.n);
	}
	#else
	for(int i = 0; i < DOM_ACCESSES; i++)
		critical_section(td->threadid, 1, td->sd);
	#endif

#ifndef SPL
#ifdef LOOP
	while(!td->done)
	{
		pause();
		poll(td->sd, NULL);
	}
	restorepr();
#endif
#endif
}
	

void bar(threaddata<int> * td)
{
	#if defined (FP) || (AFP) || (ISPL) || (FPQ) || (BQ) || (VAS)
	for(int i = 0; i < NON_DOM_ACCESSES; i++)
		critical_section(td->threadid, &inc, td->sd);
	#elif defined SPL
	for(int i = 0; i < NON_DOM_ACCESSES; i++)
	{
		spinlock::lockN(td->sd->l.n);
		td->sd->d++;
		spinlock::unlockN(td->sd->l.n);
	}
	#else
	for(int i = 0; i < NON_DOM_ACCESSES; i++)
		critical_section(td->threadid, 1, td->sd);
	#endif

	td->done = true;
}	

int main()
{
	pthread_t threads[NUM_THREADS];

	threaddata<int> j[NUM_THREADS];
	int * x = new int(0);

	shared_data<int> * sd = new shared_data<int>;

	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].sd = sd;
		j[i].done = false;
		j[i].threadid = i;
	}	

	start = get_time();

	pthread_create(&threads[0], NULL, (void* (*)(void*)) foo, (void *) &j[0] );

	for(int i = 1; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, (void* (*)(void*)) bar, (void *) &j[i] );
#ifdef LOOP		
	for(int i = 1; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	j[0].done = true;
	fence();
	pthread_join(threads[0], NULL);
#else
//	pthread_join(threads[0], NULL);	//wait for dom thread

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);
/*		if(!j[i].done)
			std::cout << "Tipping point hit, non dom threads not complete, x: " << *x << std::endl;*/
#endif

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sd->d << std::endl;
}
