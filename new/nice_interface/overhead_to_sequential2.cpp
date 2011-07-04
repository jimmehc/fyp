#include "biasedlock.h"
#include "../lib/biased_sync.h"
#include "../../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include "../lib/volatile_functions.h"
#include <pthread.h>


#define NUM_ITS 1000000

volatile unsigned long long start;

void inc(shared_data<int> * sd, void* params = NULL){
	sd->d++;
}

void foo(threaddata<int> * td)
{
	for(volatile int i = 0; i < NUM_ITS; i++)
		td->sd->d++;
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
