#include <iostream>
#include <pthread.h>
#include "../constants.h"
#include "../../lib/timing.h"

void foo(int * x)
{
	int num = DOM_ACCESSES + NON_DOM_ACCESSES*3;
	for(int i = 0; i < num; i++)
	{
		#if DELAY
		for(int j = 0; j < DELAY; j++) ;
		#endif	
		*(x) = *(x) + 1;
	}
}	

#define NUM_THREADS 1			
int main()
{
	pthread_t threads[NUM_THREADS];
	
	int * x = new int(0);
	int * y = new int(0);
	
	unsigned long long start = get_time();
	for(int i = 0; i < NUM_THREADS; i++)
	{
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) x);
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	unsigned long long end = get_time();
	std::cout << "time: " << end - start << std::endl;

//	std::cout << "x: " << *x << " y: " << *y << std::endl;
}
