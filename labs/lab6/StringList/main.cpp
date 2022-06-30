#include "CStringList.h"

int main()
{
	CStringList list;
	std::cout << list.GetSize() << std::endl;
	list.PushBack("World");
	std::cout << list.GetSize() << std::endl;
	list.PushFront("Hello");
	std::cout << list.GetSize() << std::endl;

	std::cout << "---" << std::endl;

	auto it = list.begin();
	std::cout << (*it).GetData() << std::endl;
	it++;
	std::cout << (*it).GetData() << std::endl;
	it--;
	std::cout << (*it).GetData() << std::endl;
	std::cout << (it == list.end()) << std::endl;

	return 0;
}
