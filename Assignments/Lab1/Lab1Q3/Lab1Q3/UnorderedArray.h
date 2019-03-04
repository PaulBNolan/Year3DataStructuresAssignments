#ifndef UNORDEREDARRAY_H
#define UNORDEREDARRAY_H

#include <assert.h>
#include <cstring> // for memset
#include <iostream>

template<typename T>
class UnorderedArray {

private:
	T *m_array;			// Base address of this unordered array.
	int m_maxSize;		// The max. number of array elements.
    int m_growSize;		// The size this array will grow by when required.
    int m_numElements;  // The current number of elments in this array.

public:
	UnorderedArray(int size, int growBy = 1);

	~UnorderedArray();

	void push(T val);

	void pop();

	T & operator[](int index);

	void clear();
	int getSize();
	int getMaxSize();
	int getGrowSize();
	void setGrowSize(int val);


	void remove(int index);

private:
	bool expand();
   
};


#endif
