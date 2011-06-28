#include "biasedlock.h"
#include "../lib/biased_sync.h"
#include "../lib/timing.h"
#include "../constants.h"
#include <iostream>
#include <pthread.h>

volatile unsigned long long start;

void inc(shared_data<int> * sd, void * param){
	int * x = (int*) param;
	(*x)++;
}

void foo(threaddata<int> * td)
{
	int x = 0;
	for(int i = 0; i < DOM_ACCESSES; i++)
		critical_section(td->threadid, &inc, td->sd, (void*) &x);

	critical_section(td->threadid, &set, td->sd, (void*) &x);	

}
	

void bar(threaddata<int> * td)
{
	for(int i = 0; i < NON_DOM_ACCESSES; i++)
		critical_section(td->threadid, &inc, td->sd);

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
	asm volatile ("sync");
	//std::cout << "done should now be true " << &j[0].done << std::endl;
	pthread_join(threads[0], NULL);
#else
	pthread_join(threads[0], NULL);	//wait for dom thread

	for(int i = 1; i < NUM_THREADS; i++)
		if(!j[i].done)
			std::cout << "Tipping point hit, non dom threads not complete, x: " << *x << std::endl;
#endif

	volatile unsigned long long end = get_time();

	std::cout << "time: " << end-start << std::endl;

	std::cout << "x: " << sd->d << std::endl;
}
