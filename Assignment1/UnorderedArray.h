#pragma once
#include <cassert>
#include "Array.h"

template<class T>
class UnorderedArray : public Array<T>
{
public:

	// Constructor
	UnorderedArray(int size, int growBy = 1) : Array<T>(size, growBy)
	{}

	// Destructor
	~UnorderedArray()
	{
		if (Array<T>::m_array != nullptr)
		{
			delete[] Array<T>::m_array;
			Array<T>::m_array = nullptr;
		}
	}

	// Insertion (Fast insertion for UnorderedArray -- Big-O is O(1))
	void push(T val)
	{
		assert(Array<T>::m_array != nullptr); // Debugging purposes

		if (Array<T>::m_numElements >= Array<T>::m_maxSize)	// Check if the array has to expand to accommodate the new data.
		{
			Array<T>::Expand();
		}

		// My array has space for a new value. Let's add it!
		Array<T>::m_array[Array<T>::m_numElements] = val;
		Array<T>::m_numElements++;
	}
	
	// Searching -- Linear Search
	int search(T val)
	{
		assert(Array<T>::m_array != nullptr);

		// Brute-force Search
		for (int i = 0; i < Array<T>::m_numElements; i++)
		{
			if (Array<T>::m_array[i] == val)
			{
				return i;	// Return the index of where the item is located in the array
			}
		}

		return -1;
	}
};