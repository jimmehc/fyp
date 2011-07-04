#include "biasedlock.h"
#include "../lib/biased_sync.h"
#include "../../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include "../lib/volatile_functions.h"
#include <pthread.h>


#define NUM_ITS 1000000

volatile unsigned long long start;

void inc(volatile shared_data<int> * sd, void* params = NULL){
	sd->d++;
}

void dec(volatile shared_data<int> * sd, void* params = NULL){
	sd->d--;
}

void switch_to_dom(volatile shared_data<int> * sd, void* params){
	sd->l.owner = (long) params;
	fence();
	sd->l.biased_mode = true;
	fence();
	std::cout << "SWITCH" << sd->l.owner << std::endl;
}

void FUCK_YOU(volatile shared_data<int> * sd, void * params = NULL){
	std::cout << "FUCK YOU" << std::endl;
}
void switch_to_unbiased(volatile shared_data<int> * sd, void* params = NULL){
	sd->l.biased_mode = false;
	fence();
	sd->l.func =&FUCK_YOU;
	std::cout << "SWITCHUN" << sd->l.owner << std::endl;
}


void foo(threaddata<int> * td)
{
	
	for(volatile int j = 0; j < 100000000; j++){ pause();} restorepr(); 
#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_dom, td->sd, (void*) td->threadid);
#endif
	for(int i = 0; i < NUM_ITS; i++)
	{
		for(volatile int j = 0; j < 1; j++);	
		critical_section(td->threadid, &inc, td->sd);
	}

	fence();
#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_unbiased, td->sd);
#endif
	for(volatile int j = 0; j < 100000000; j++){ pause();} restorepr(); 
#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_dom, td->sd,(void*) td->threadid);
#endif
	for(int i = 0; i < NUM_ITS; i++)
	{
		for(volatile int j = 0; j < 1; j++);	
		critical_section(td->threadid, &inc, td->sd);
	}
#ifdef SWITCH	
	critical_section(td->threadid, &switch_to_unbiased, td->sd);
#else
	for(;;){ poll(td->sd, NULL); }
#endif
	std::cout << "thread: " << td->threadid << std::endl;
}

void bar(threaddata<int> * td)
{
	for(int i = 0; i < NUM_ITS/(NUM_THREADS - 1); i++)
	{
		critical_section(td->threadid, &dec, td->sd);
		for(volatile int j = 0; j < (NDD*(NUM_THREADS-1)); j++) { pause();} restorepr(); 
	}

	std::cout << "thread: " << td->threadid << std::endl;
	td->done = true;
}	

int main()
{
	pthread_t threads[NUM_THREADS];

	threaddata<int> j[NUM_THREADS];
	int * x = new int(0);

	volatile shared_data<int> * sd = new shared_data<int>;
#ifdef SWITCH
	sd->l.owner = 1;
	sd->l.biased_mode = false;
#endif
	for(int i = 0; i < NUM_THREADS; i++)
	{
		j[i].sd = sd;
		j[i].done = false;
		j[i].threadid = i;
	}	

	start = get_time();

	pthread_create(&threads[0], NULL, (void* (*)(void*)) foo, (void *) &j[0] );

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_create(&threads[i], NULL, (void* (*)(void*)) bar, (void *) &j[i] );

	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);	//wait for dom thread

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sd->d << std::endl;
}
