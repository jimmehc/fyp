#include "biasedlock.h"
#include "../lib/biased_sync.h"
#include "../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include <pthread.h>


#define NUM_ITS 100000000

volatile unsigned long long start;

void inc(shared_data<int> * sd, void* params = NULL){
	sd->d++;
}

void switch_to_dom(shared_data<int> * sd, void* params){
	sd->l.biased_mode = true;
	sd->l.owner = (long) params;
	std::cout << "SWITCH" << sd->l.owner << std::endl;
}

void switch_to_unbiased(shared_data<int> * sd, void* params = NULL){
	sd->l.biased_mode = false;
}

void foo(threaddata<int> * td)
{
	
	usleep(5);
#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_dom, td->sd, (void*) td->threadid);
#endif
	for(int i = 0; i < NUM_ITS; i++)
		critical_section(td->threadid, &inc, td->sd);

	asm volatile ("sync");
#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_unbiased, td->sd);
#endif
	usleep(5);
#ifdef SWITCH	
//	critical_section(td->threadid, &switch_to_dom, td->sd,(void*) td->threadid);
#endif
	for(int i = 0; i < NUM_ITS; i++)
		critical_section(td->threadid, &inc, td->sd);
#ifdef SWITCH	
//	critical_section(td->threadid, &switch_to_unbiased, td->sd);
#endif
}

void bar(threaddata<int> * td)
{
	for(;;)
	{
		usleep(1);
		critical_section(td->threadid, &inc, td->sd);
	}

	std::cout << "thread: " << td->threadid << std::endl;
	td->done = true;
}	

int main()
{
	pthread_t threads[NUM_THREADS];

	threaddata<int> j[NUM_THREADS];
	int * x = new int(0);

	shared_data<int> * sd = new shared_data<int>;

	sd->l.owner = 1;
	sd->l.biased_mode = false;

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

	pthread_join(threads[0], NULL);	//wait for dom thread

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sd->d << std::endl;
}
