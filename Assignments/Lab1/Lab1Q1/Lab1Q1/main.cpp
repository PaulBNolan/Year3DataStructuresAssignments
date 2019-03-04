#include <iostream>

template <typename T> T ScalarProduct(T array1[], T array2[])
{
	return T(array1[0] * array2[0] + array1[1] * array2[1] + array1[2] * array2[2]);
}

int main()
{
	int iVector1[] = { 2, 5, 7 };
	int iVector2[] = { 9, 2, 1 };

	std::cout << "-----Int Vectors-----" << std::endl;
	std::cout << "{ " << iVector1[0] << ", " << iVector1[1] << ", " << iVector1[2] << " }" << std::endl;
	std::cout << "{ " << iVector2[0] << ", " << iVector2[1] << ", " << iVector2[2] << " }" << std::endl;
	
	int iScalarProduct = ScalarProduct(iVector1, iVector2);
	std::cout << "Scalar Product: " << iScalarProduct << std::endl;

	system("Pause");

	float fVector1[] = { 2.7f, 5.1f, 7.9f };
	float fVector2[] = { 9.6f, 2.3f, 1.5f};

	std::cout << "-----Int Vectors-----" << std::endl;
	std::cout << "{ " << fVector1[0] << ", " << fVector1[1] << ", " << fVector1[2] << " }" << std::endl;
	std::cout << "{ " << fVector2[0] << ", " << fVector2[1] << ", " << fVector2[2] << " }" << std::endl;

	float fScalarProduct = ScalarProduct(fVector1, fVector2);
	std::cout << "Scalar Product: " << fScalarProduct << std::endl;

	system("Pause");

	double dVector1[] = { 2.65, 5.98, 7.34 };
	double dVector2[] = { 9.98, 2.09, 1.67 };

	std::cout << "-----Int Vectors-----" << std::endl;
	std::cout << "{ " << dVector1[0] << ", " << dVector1[1] << ", " << dVector1[2] << " }" << std::endl;
	std::cout << "{ " << dVector2[0] << ", " << dVector2[1] << ", " << dVector2[2] << " }" << std::endl;

	double dScalarProduct = ScalarProduct(dVector1, dVector2);
	std::cout << "Scalar Product: " << dScalarProduct << std::endl;

	system("Pause");
}