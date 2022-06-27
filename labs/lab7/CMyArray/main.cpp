#include "CMyArray.h"

int main()
{
	CMyArray<int> array(5);
	std::cout << array.GetSize() << std::endl;

	CMyArray<int> array2(0);

	array2 = array;
	std::cout << array.GetSize() << std::endl;
	std::cout << array2.GetSize() << std::endl;
	return 0;
}
