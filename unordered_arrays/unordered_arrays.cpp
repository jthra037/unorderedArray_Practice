// unordered_arrays.cpp : Defines the entry point for the console application.
//


//This is a change.

#include "stdafx.h"
#include <iostream>
#include <cassert>
#include<cstring>
using namespace std;

class UnorderedArray
{
private:
	int *m_array;

	int maxSize;
	int numElements;

public:
	UnorderedArray(int size) :
		m_array(NULL), maxSize(0), numElements(0)
	{
		if (size)
		{
			maxSize = size;
			m_array = new int[maxSize];
			memset(m_array, 0, sizeof(int) * maxSize); // sets all items in the array to 0
		}
	}

	~UnorderedArray()
	{
		if (m_array != NULL)
		{
			delete[] m_array;
			m_array = NULL;
		}
	}

	void push(int val)
	{
		assert(m_array != NULL);

		if (numElements >= maxSize)
		{
			cout << " Array full item not inserted";
		}
		else
		{
			m_array[numElements] = val;
			numElements++;
		}
	}

	// removes the last item that was inserted
	void pop()
	{
		if (numElements > 0)
			numElements--;
		else
			cout << " Array empty - nothing to remove";
	}

	// removes an index from the array by shifting everything down by one
	void efficientRemove(int index)
	{
		assert(m_array != NULL);

		if (index >= numElements)
		{
			return;
		}
		if (numElements>1)
			m_array[index] = m_array[numElements - 1]; // copy last item into the position to be deleted
		numElements--;
	}

	// removes an index from the array by shifting everything down by one
	void remove(int index)
	{
		assert(m_array != NULL);

		if (index >= numElements)
		{
			return;
		}

		for (int k = index; k < numElements - 1; k++)
		{
			m_array[k] = m_array[k + 1];
		}
		numElements--;
	}

	void insertionSortAsc() {

	}

	void selectionSortAsc() {

	}

	void bubbleSortAsc() {

	}

	int binarySearch(int item) {
		return -1;
	}


	int search(int val)
	{
		assert(m_array != NULL);

		for (int i = 0; i < numElements; i++)
		{
			if (m_array[i] == val)
				return i;
		}

		return -1;
	}

	void listItems() {
		assert(m_array != NULL);
		if (numElements>0) {
			for (int x = 0; x< numElements; x++) {
				cout << m_array[x] << "   ";
			}
			cout << endl;
		}
		else
			cout << "List Empty.." << endl;
	}

	void DisposeObject() {
		delete this;
	}

	int& operator[](int index)
	{
		assert(m_array != NULL && index < numElements);
		return m_array[index];
	}

	// removes all items from the array
	void clear() { numElements = 0; }
	int GetSize() { return numElements; }
	int GetMaxSize() { return maxSize; }

};

int main() {
	UnorderedArray u = UnorderedArray(4);
	cout << u.GetSize() << endl;
	cout << u.GetMaxSize() << endl;
	u.listItems();
	u.push(34);
	u.push(23);
	u.push(8);
	u.push(24);
	cout << u[2] << endl;
	u.listItems();


	return 0;
}