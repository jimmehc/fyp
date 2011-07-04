#include "biasedlock.h"
#include "../lib/biased_sync.h"
#include "../../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include "../lib/volatile_functions.h"
#include <pthread.h>


#define NUM_ITS 10000
#define NUM_ITS2 100

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
	
#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_dom, td->sd, (void*) td->threadid);
#endif
	for(int i = 0; i < NUM_ITS; i++)
	{
		for(volatile int j = 0; j < 1; j++);
		critical_section(td->threadid, &inc, td->sd);
	}

	for(;;)
	{
		critical_section(td->threadid, &inc, td->sd);
		for(volatile int j = 0; j < (NDD*(NUM_THREADS-1)); j++) { pause();} restorepr(); 
	}
}
void foo2(threaddata<int> * td)
{
	
	for(int i = 0; i < NUM_ITS2; i++)
	{
		critical_section(td->threadid, &inc, td->sd);
		for(volatile int j = 0; j < (NDD*(NUM_THREADS-1)); j++) { pause();} restorepr(); 
	}

#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_dom, td->sd, (void*) td->threadid);
#endif
	for(int i = 0; i < NUM_ITS; i++)
	{
		for(volatile int j = 0; j < 1; j++);
		critical_section(td->threadid, &inc, td->sd);
	}
}

void bar(threaddata<int> * td)
{
	for(;;)
	{
		for(volatile int j = 0; j < (NDD*(NUM_THREADS-1)); j++) { pause();} restorepr(); 
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

/*	sd->l.owner = 1;
	sd->l.biased_mode = false;
*/
	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].sd = sd;
		j[i].done = false;
		j[i].threadid = i;
	}	

	start = get_time();

	pthread_create(&threads[0], NULL, (void* (*)(void*)) foo, (void *) &j[0] );
	pthread_create(&threads[1], NULL, (void* (*)(void*)) foo2, (void *) &j[1] );

	for(int i = 2; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, (void* (*)(void*)) bar, (void *) &j[i] );

	pthread_join(threads[1], NULL);	//wait for dom thread

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sd->d << std::endl;
}
