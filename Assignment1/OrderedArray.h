#pragma once
#include <cassert>
#include "Array.h"

template<class T>
class OrderedArray : public Array<T>
{
public:

	// Constructor
	OrderedArray(int size, int growBy = 1) : Array<T>(size, growBy)
	{}

	// Destructor
	~OrderedArray()
	{
		if (Array<T>::m_array != nullptr)
		{
			delete[] Array<T>::m_array;
			Array<T>::m_array = nullptr;
		}
	}

	// Insertion -- Big-O = O(N)
	void push(T val)
	{
		assert(Array<T>::m_array != nullptr);
		//assert(search(val) != -1);
		if (search(val) != -1)
		{
			cout << "Error: ";
			cout << val;
			cout << " Already exists in Array" << endl;
		}
		if (Array<T>::m_numElements >= Array<T>::m_maxSize)
		{
			
			Array<T>::Expand();
		}

		int i, k;	// i - Index to be inserted. k - Used for shifting purposes
		// Step 1: Find the index to insert val
		for (i = 0; i < Array<T>::m_numElements; i++)
		{
			if (Array<T>::m_array[i] > val)
			{
				break;
			}
		}

		// Step 2: Shift everything to the right of the index(i) forward by one. Work backwards
		for (k = Array<T>::m_numElements; k > i; k--)
		{
			Array<T>::m_array[k] = Array<T>::m_array[k - 1];
		}

		// Step 3: Insert val into the array at index
		Array<T>::m_array[i] = val;

		Array<T>::m_numElements++;

		// return i;
	}

	// Searching -- Binary Search
	int search(T searchKey)
	{
		assert(Array<T>::m_array != nullptr);

		// Helper variables.
		int lowerBound = 0;
		int upperBound = Array<T>::m_numElements - 1;
		int current = 0;

		while (1)	// <-- Replaced with recursion
		{
			current = (lowerBound + upperBound) >> 1;	// Preview of bitwise operatrions. Divides by 2

			// Binary search steps:
			// Step 1: Check if the middle is the value we are looking for.
			if (Array<T>::m_array[current] == searchKey)
			{
				// Found the item in the middle of the array. Return the index
				return current;
			}
			// Step 2: Check that we've exhausted all options. Can't find the item
			else if (lowerBound > upperBound)
			{
				return -1;
			}
			// Step 3: Check which half of the array the value is in.
			else
			{
				if (Array<T>::m_array[current] < searchKey)
				{
					lowerBound = current + 1;	// Value may be in the upper half
				}
				else
				{
					upperBound = current - 1;	// Value may be in the lower half
				}
			}
		}

		return -1;	// Catch all return from danger.
	}
};