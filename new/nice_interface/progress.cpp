#include "progress.h"
#include "../lib/biased_sync.h"
#include "../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include "../lib/volatile_functions.h"
#include <pthread.h>

volatile unsigned long long start;

void inc(shared_data<int> * sd, void * params = NULL){
	sd->d++;
}

void foo(threaddata<int> * td)
{
	for(int i = 0; i < DOM_ACCESSES; i++)
	#if defined (FP) || (AFP) || (ISPL) || (FPQ) || (BQ) || (VAS)
	{
		for(volatile int j = 0; j < 1; j++);
		critical_section(td->threadid, &inc, td->sd);
	}
	#elif defined SPL
	{
		for(volatile int j = 0; j < 1; j++);

		spinlock::lockN(td->sd->l.n);
		td->sd->d++;
		spinlock::unlockN(td->sd->l.n);
	}
	#else
	{
		for(volatile int j = 0; j < 1; j++);
		critical_section(td->threadid, 1, td->sd);
	}
	#endif

}
	

void bar(threaddata<int> * td)
{
	td->done = true;
	for(;;)
	#if defined (FP) || (AFP) || (ISPL) || (FPQ) || (BQ) || (VAS)
	{
		for(volatile int j = 0; j < (NDD*(NUM_THREADS-1)); j++) { pause();} restorepr();
		critical_section(td->threadid, &inc, td->sd);
	}
	#elif defined SPL
	{
		for(volatile int j = 0; j < (NDD*(NUM_THREADS-1)); j++) { pause();} restorepr();

		spinlock::lockN(td->sd->l.n);
		td->sd->d++;
		spinlock::unlockN(td->sd->l.n);
	}
	#else
	{
		for(volatile int j = 0; j < (NDD*(NUM_THREADS-1)); j++) { pause();} restorepr();
		critical_section(td->threadid, 1, td->sd);
	}
	#endif

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
	{
		pthread_create(&threads[i], NULL, (void* (*)(void*)) bar, (void *) &j[i] );
	}
	pthread_join(threads[0], NULL);	//wait for dom thread

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sd->d << std::endl;

	std::cout << "total progress: " << ((double)(sd->d)/(double)(end-start))*1000 << " accesses per 1000 cycles" << std::endl;
	std::cout << "dom progress: " << ((double)(DOM_ACCESSES)/(double)(end-start))*1000 << " accesses per 1000 cycles" << std::endl;
	std::cout << "non-dom progress: " << ((double)(sd->d - DOM_ACCESSES)/(double)(end-start))*1000 << " accesses per 1000 cycles" << std::endl;
	std::cout << "actual dominance percentage: " << (double)DOM_ACCESSES/(double)(sd->d) << std::endl;
}
