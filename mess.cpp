#include <iostream>

struct yeah
{
	int x;
	int hi()
	{
		return x++;
	}
};

int main()
{
	yeah * y = new yeah;
	int (yeah::*fp)() = &yeah::hi;

	y->x = 9;

	std::cout << (y->*fp)() << std::endl;
	std::cout << (y->*fp)() << std::endl;
	std::cout << (y->*fp)() << std::endl;
	std::cout << (y->*fp)() << std::endl;
}
