#include <iostream>


int main()
{
	int x;
	
	for (int i = 0; i < 1000000000; i++)
		x = i;
	
	std::cout << x << std::endl;
}
