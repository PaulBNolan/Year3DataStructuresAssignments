#include <iostream>
#include "UnorderedArray.h"
UnorderedArray <int> testArray(8,0);

int main()
{
	testArray.push(4);
	testArray.push(1);
	testArray.push(5);
	testArray.push(3);
	testArray.push(8);
	testArray.push(5);
	testArray.push(2);
	testArray.push(6);

	int value;
	std::cout << "Enter a value to search for in the array." << std::endl;
	std::cin >> value;

	int index = testArray.search(value);
	if (index >= 0)
	{
		std::cout << "The index of the value searched for is " << index << std::endl;
	}
	else
	{
		std::cout << "Value not found." << std::endl;
	}
	system("Pause");
}