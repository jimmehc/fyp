#include <iostream>
#include "../../lib/timing.h"

#define CAS __sync_bool_compare_and_swap
int main()
{
	int x;

	unsigned long long start = get_time();
	for(int i = 0; i < 1000000000; i++)
		CAS(&x, x, i);
	std::cout << get_time() - start << std::endl;
	std::cout << x << std::endl;
}
