#include "CMyString.h"

int main()
{
	char* m =  "string";
	auto num = std::strlen(m);
	std::cout << num << std::endl;
	return 0;
}