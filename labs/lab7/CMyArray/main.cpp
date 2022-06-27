#include "CMyArray.h"

int main()
{
	CMyArray<int> array(5);
	std::cout << array.GetSize() << std::endl;
	return 0;
}
