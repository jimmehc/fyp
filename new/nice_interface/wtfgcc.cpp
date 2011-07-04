#include <cstdlib>
#include <iostream>

int main()
{
	int x = 0;

	for (int i = 0; i < 10000000; i++)
		x = rand();

	std::cout << x << std::endl;
}
