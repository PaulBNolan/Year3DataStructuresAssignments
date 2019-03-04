#include <iostream>
#include <vector>
#include <array>
#include <string>

class Gamer
{
public:
	Gamer() {}
	// Destructor function
	~Gamer()
	{
		std::cout << "Destructor called" << std::endl;
	}
	// Define a copy constructor
	Gamer(Gamer const & copy)
	{
		std::cout << "Copy constructor called" << std::endl;
	}
};

int main()
{
	std::vector<Gamer> m_vector1;
	m_vector1.resize(10);
	for (int i = 0; i < m_vector1.size(); i++)
	{
		m_vector1[i] = Gamer();
	}

	std::cout << "Capacity: " << m_vector1.capacity() << std::endl;
	std::cout << "Size: " << m_vector1.size() << std::endl;

	std::cout << "Vector Cleared" << std::endl;
	m_vector1.clear();
	std::cout << "Capacity: " << m_vector1.capacity() << std::endl;
	std::cout << "Size: " << m_vector1.size() << std::endl;

	std::cout << "Vector Pointer" << std::endl;
	std::vector<Gamer*> m_vector2;
	m_vector2.resize(10);
	for (int i = 0; i < m_vector2.size(); i++)
	{
		m_vector2[i] = new Gamer();
	}

	std::cout << "Capacity: " << m_vector2.capacity() << std::endl;
	std::cout << "Size: " << m_vector2.size() << std::endl;

	std::cout << "Vector Cleared" << std::endl;
	m_vector2.clear();
	std::cout << "Capacity: " << m_vector2.capacity() << std::endl;
	std::cout << "Size: " << m_vector2.size() << std::endl;

	system("Pause");
}