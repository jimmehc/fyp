#include <iostream>
#include "../../lib/timing.h"


int main()
{
	int x;
	
	unsigned long long start = get_time();
	for (int i = 0; i < 1000000000; i++)
	{
		x = i;
		asm volatile ("sync");
	}
	std::cout << get_time() - start << std::endl;
	std::cout << x << std::endl;
}
