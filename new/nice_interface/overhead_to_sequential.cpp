#include "biasedlock.h"
#include "../lib/biased_sync.h"
#include "../lib/timing.h"
#include "../lib/volatile_functions.h"
#include "../constants.h"
#include <iostream>
#include <pthread.h>
#include <cstdlib>

#define NUM_ITS 100000000

volatile unsigned long long start;

void incsd(shared_data<int> * sd, void* params = NULL){
	for (int j = 0; j < CS_SIZE; j++)
		vol_inc(sd->d);
}

void foo(threaddata<int> * td)
{

	for(int i = 0; i < NUM_ITS; i++)
	#if defined (SEQ)
	{
		for (int j = 0; j < CS_SIZE; j++)
			vol_inc(td->sd->d);
	}	
	
//		td->sd->d = x;
		asm volatile ("mfence");
	#elif defined (FP) || (AFP) || (ISPL) || (FPQ) || (BQ) || (VAS)
		critical_section(td->threadid, &incsd, td->sd);
	#elif defined SPL
	{
		spinlock::lockN(td->sd->l.n);
		for (int j = 0; j < CS_SIZE; j++)
			vol_inc(td->sd->d);
		spinlock::unlockN(td->sd->l.n);
	}
	#else
		for (int j = 0; j < CS_SIZE; j++)
			critical_section(td->threadid, 1, td->sd);
	#endif

	std::cout << td->sd->d << std::endl;
}

int main()
{
	pthread_t thread;

	threaddata<int> j;
	int * x = new int(0);

	shared_data<int> * sd = new shared_data<int>;

	j.sd = sd;
	j.threadid = 0;
		
	start = get_time();

	pthread_create(&thread, NULL, (void* (*)(void*)) foo, (void *) &j);

	pthread_join(thread, NULL);	//wait for dom thread

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sd->d << std::endl;
}
