#include "multiple.h"
#include "../lib/biased_sync.h"
#include "../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include "../lib/volatile_functions.h"
#include <pthread.h>

#define NUM_ITS 100000000
#ifndef NDF
#define NDF 10000
#endif
#ifdef LOOP
pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sig;
int count = 0;
#endif

volatile unsigned long long start;

void inc(shared_data<int> * sd, void * params = NULL){
	sd->d++;
}

void nothing(shared_data<int> * sd, void * params = NULL){
	for(volatile int i = 0; i < 10; i++);
}

void foo(threaddata<int> * td)
{
	for(int i = 0; i < NUM_ITS; i++)
	{
		#if defined (FP) || (AFP) || (ISPL) || (FPQ) || (BQ) || (VAS)
		if(i % NDF == 0)
			critical_section(td->threadid, &inc, td->sds[(td->threadid + 1)%NUM_THREADS], NULL, td->sds[td->threadid]);
		else
			critical_section(td->threadid, &inc, td->sds[td->threadid], NULL, td->sds[td->threadid]);
		#elif defined SPL
		if(i % NDF == 0)
		{
			spinlock::lockN(td->sds[(td->threadid+1)%NUM_THREADS]->l.n);
			td->sds[(td->threadid+1)%NUM_THREADS]->d++;
			spinlock::unlockN(td->sds[(td->threadid+1)%NUM_THREADS]->l.n);
		}
		else
		{
			spinlock::lockN(td->sds[td->threadid]->l.n);
			td->sds[td->threadid]->d++;
			spinlock::unlockN(td->sds[td->threadid]->l.n);
		}
		#else
		if(i % NDF == 0)
			critical_section(td->threadid, 1, td->sds[(td->threadid + 1)%NUM_THREADS], NULL, td->sds[td->threadid]);
		else
			critical_section(td->threadid, 1, td->sds[td->threadid], NULL, td->sds[td->threadid]);
		
		#endif
	}
	
	//critical_section_owner(td->threadid, &switch_to_unbiased, td->sd);
#ifdef LOOP
	pthread_mutex_lock(&mymutex);
	count++;
	if(count == NUM_THREADS)
		pthread_cond_signal(&sig);
	pthread_mutex_unlock(&mymutex);
	
	while(!td->done)
	{
		pause();
		poll(td->sds[td->threadid], NULL);
	}
	restorepr();
#endif
}
	
int main()
{
#ifdef LOOP
	pthread_cond_init (&sig, NULL);
#endif
	pthread_t threads[NUM_THREADS];

	threaddata<int> j[NUM_THREADS];
	int * x = new int(0);

	shared_data<int> * sds[NUM_THREADS];
	for(int i = 0; i < NUM_THREADS; i++)
	{
	 	sds [i] = new shared_data<int>;
	#ifndef SPL
		sds[i]->l.owner = i;
	#endif
	}

	for(int i = 0; i < NUM_THREADS; i++)
	{
		for(int k = 0; k < NUM_THREADS; k++)
			j[i].sds[k] = sds[k];

		j[i].done = false;
		j[i].threadid = i;
	}	

	start = get_time();

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) &j[i] );
#ifdef LOOP		
	pthread_mutex_lock(&mymutex);
	pthread_cond_wait(&sig, &mymutex);
	pthread_mutex_unlock(&mymutex);

	for(int i = 0; i < NUM_THREADS; i++)
		j[i].done = true;

#else
//	pthread_join(threads[0], NULL);	//wait for dom thread

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);
/*		if(!j[i].done)
			std::cout << "Tipping point hit, non dom threads not complete, x: " << *x << std::endl;*/
#endif

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sds[1]->d << std::endl;
}
