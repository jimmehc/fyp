#include <pthread.h>
#include <iostream>

typedef struct {
	int w;
	int x;
	int y;
	int z;
} threaddata;

void writex(threaddata * td)
{
	for(int i = 0; i < 1000000000; i++)
	{
		td->x = i;
		asm volatile ("mfence");
	}
}

void writey(threaddata * td)
{
	for(int i = 0; i < 1000000000; i++)
	{
		td->y = i;
		asm volatile ("mfence");
	}
}

void writez(threaddata * td)
{
	for(int i = 0; i < 1000000000; i++)
	{
		td->z = i;
		asm volatile ("mfence");
	}
}

void writew(threaddata * td)
{
	for(int i = 0; i < 1000000000; i++)
	{
		td->w = i;
		asm volatile ("mfence");
	}
}

int main()
{
	pthread_t threads[4];
	threaddata * td = new threaddata;

	std::cout << "w: " << &td->w << std::endl;
	std::cout << "x: " << &td->x << std::endl;
	std::cout << "y: " << &td->y << std::endl;
	std::cout << "z: " << &td->z << std::endl;
	
	td->w = td->x = td->y = td->z = 0;

	pthread_create(&threads[0], NULL, (void* (*)(void*)) writew, td);
	pthread_create(&threads[1], NULL, (void* (*)(void*)) writex, td);
	pthread_create(&threads[2], NULL, (void* (*)(void*)) writey, td);
	pthread_create(&threads[3], NULL, (void* (*)(void*)) writez, td);

	for(int i = 0; i < 4; i++)
		pthread_join(threads[i], NULL);
}	

	
	
