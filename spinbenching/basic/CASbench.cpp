#include <iostream>

#define CAS __sync_bool_compare_and_swap
int main()
{
	int x;

	for(int i = 0; i < 1000000000; i++)
		CAS(&x, x, i);

	std::cout << x << std::endl;
}
