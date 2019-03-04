#include <iostream>
#include "UnorderedArray.h"

int main()
{
	UnorderedArray <int> m_array(8,0);

	m_array.push(1);
	m_array.push(2);
	m_array.push(3);
	m_array.push(4);
	m_array.push(5);
	m_array.push(6);
	m_array.push(7);
	m_array.push(8);

	int index;
	std::cout << "Select Index to remove." << std::endl;
	std::cin >> index;

	m_array.remove(index);

	system("Pause");
}