#include <iostream>

int main()
{
	char* ptr;
	
	if (1)
	{
		char c = 'h';
		ptr = &c;
	}

	char c = *ptr;
	std::cout << c << std::endl;

	return 0;
}
