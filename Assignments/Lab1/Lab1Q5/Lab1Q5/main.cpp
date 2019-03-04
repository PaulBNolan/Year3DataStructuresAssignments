#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <string>


class IsTarget {
public:
	bool operator() (int & num) const {
		return (num == m_target);
	}

	IsTarget(int & num) :
		m_target(num)
	{}
 private:
	 int m_target;
};


bool isTargetInVector(std::vector<int> const & numbers, int lookFor)
{
	auto targetNumber = std::find(std::begin(numbers), std::end(numbers), lookFor);
	/*if (lookFor == targetNumber)
	{

	}*/
	return targetNumber != std::end(numbers);
}


int main()
{
	std::vector<int> numberRange;
	numberRange.resize(10);

	for (int i = 0; i < numberRange.size(); i++)
	{
		numberRange[i] = rand() % 9 + 1;
		std::cout << numberRange[i] << std::endl;
	}
	int num = 0;
	std::cout << "Enter number to remove from Vector." << std::endl;
	std::cin >> num;
	std::cout << "-------------------------------" << std::endl;
	while (isTargetInVector(numberRange, num) == true)
	{
		numberRange.erase(std::remove(std::begin(numberRange), std::end(numberRange), num));
	}
	for (int i = 0; i < numberRange.size(); i++)
	{
		std::cout << numberRange[i] << std::endl;
	}

	num = 0;
	std::cout << "Enter another number to remove from Vector." << std::endl;
	std::cin >> num;
	IsTarget T(num);
	std::cout << "-------------------------------" << std::endl;

	/*numberRange.erase(std::remove_if(numberRange.begin(), numberRange.end(), IsTarget(num)), numberRange.end());
	for (int i = 0; i < numberRange.size(); i++)
	{
		std::cout << numberRange[i] << std::endl;
	}*/

	numberRange.erase(std::remove_if(numberRange.begin(), numberRange.end(), 
		[&](int i)
	{
		return i == num;
	}
		
		), numberRange.end());

	system("Pause");
}