#include <iostream>
#include <pthread.h>

void foo(int * x)
{
	for(int i = 0; i < 12000000; i++)
	{
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
		*(x) = *(x) + 1;
	}
}	

#define NUM_THREADS 1			
int main()
{
	pthread_t threads[NUM_THREADS];
	
	int * x = new int(0);
	int * y = new int(0);
	for(int i = 0; i < NUM_THREADS; i++)
	{
		pthread_create(&threads[i], NULL, (void* (*)(void*)) foo, (void *) x);
	}	
	for(int i = 0; i < NUM_THREADS; i++)
		pthread_join(threads[i], NULL);

	std::cout << "x: " << *x << " y: " << *y << std::endl;
}