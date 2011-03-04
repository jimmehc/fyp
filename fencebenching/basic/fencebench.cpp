#include <iostream>


int main()
{
	int x;
	
	for (int i = 0; i < 1000000000; i++)
	{
		x = i;
		asm volatile ("mfence");
	}
	
	std::cout << x << std::endl;
}
