#include <iostream>
#include <pthread.h>
#include "../../lib/timing.h"

int main()
{
	pthread_spinlock_t lck;
	pthread_spin_init(&lck, PTHREAD_PROCESS_PRIVATE);
	int x;
	
	unsigned long long start = get_time();
	for (int i = 0; i < 1000000000; i++)
	{
		pthread_spin_lock(&lck);
		x = i;
		pthread_spin_unlock(&lck);
	}
	
	std::cout << get_time() - start << std::endl;
	std::cout << x << std::endl;
}
