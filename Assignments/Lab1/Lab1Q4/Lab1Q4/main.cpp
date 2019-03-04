#include <iostream>
#include <vector>
#include <array>
#include <string>
template<typename T>
std::pair<T,T> minMax(std::vector<T> &vec)
{
	T min = vec[0];
	T max = vec[0];
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] < min)
		{
			min = vec[i];
		}

		if (vec[i] > max)
		{
			max = vec[i];
		}
	}

	return std::make_pair(min, max);
}

int main()
{
	std::vector<int> iVec = { 2,9,1 };

	std::cout << "---Int Vector---" << std::endl;
	std::cout << "[";
	for (int i = 0; i < iVec.size(); i++)
	{
		std::cout << " "<< iVec[i];
	}
	std::cout << " ]" << std::endl;

	std::pair<int, int> lowHighInt = minMax(iVec);

	std::cout << lowHighInt.first << " " << lowHighInt.second << std::endl;


	std::vector<std::string> sVec = { "17","6","11" };

	std::cout << "---String Vector---" << std::endl;
	std::cout << "[";
	for (int i = 0; i < sVec.size(); i++)
	{
		std::cout << " " << sVec[i];
	}
	std::cout << " ]" << std::endl;

	std::pair<std::string, std::string> lowHighString = minMax(sVec);

	std::cout << lowHighString.first << " " << lowHighString.second << std::endl;

	system("Pause");
}