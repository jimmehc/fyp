#include <iostream>


int hi()
{
	static int x = 0;
	return x++;
}

int main()
{
	int (*fp)() = &hi;

	fp->x = 9;

	std::cout << fp() << std::endl;
	std::cout << fp() << std::endl;
	std::cout << fp() << std::endl;
	std::cout << fp() << std::endl;
}
