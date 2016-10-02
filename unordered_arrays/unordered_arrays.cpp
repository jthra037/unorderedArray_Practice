#include "stdafx.h"
#include <iostream>
#include <cassert>
#include<cstring>
using namespace std;

///Stuff up here is the same as all the stuff in class. This is how you set up a home made array.
class intArray
{
private:
	int *m_array;

	int maxSize;
	int numElements;

public:
	///Here be the constructor for the new intArray class
	intArray(int size) : m_array(NULL), maxSize(0), numElements(0)
	{
		if (size)
		{
			maxSize = size;
			m_array = new int[maxSize];
			memset(m_array, 0, sizeof(int) * maxSize); //this sets all items in the array to 0
		}
	}
	
	///Here be a destructor for the new intArray class
	~intArray()
	{
		if (m_array != NULL)
		{
			delete[] m_array;
			m_array = NULL;
		}
	}

	///Access operator overload for intArray
	int& operator[](int index)
	{
		assert(m_array != NULL && index < numElements);
		return m_array[index];
	}

	///"Removes" all items from the array
	void clear() { numElements = 0; }
	///Gets the number of elements held in the array
	int getSize() { return numElements; }
	///Gets the number of elements that can be held in the array
	int getMaxSize() { return maxSize; }

	///Default push, puts the element to be inserted in the last position of array
	///if there is space.
	void push(int val)
	{
		assert(m_array != NULL); //No null pointers.

		if (numElements >= maxSize) // If the array is full
		{
			cout << " Array full item not inserted";
		}
		else
		{
			m_array[numElements] = val; // or set value in the last position
			numElements++; //and increment that position.
		}
	}

	///Removes the last item that was in the array
	///if there is one.
	void pop()
	{
		// If there are elements in the array
		if (numElements > 0)
			numElements--; // decrement the number of elements accessible.
		else
			cout << " Array empty - nothing to remove";
	}

	///Default remove function. 
	///Shifts down all elements after index, keeping order.
	void remove(int index)
	{
		assert(m_array != NULL); // No null pointers.

		//Is index out of bounds?
		if (index >= numElements)
		{
			cout << "Index out of bounds." << endl;
			return;
		}

		//Starting at index to be removed, until the end of the array
		for (int k = index; k < numElements - 1; k++)
		{
			m_array[k] = m_array[k + 1]; // move elements down one
		}
		numElements--; // then decrement the number of accessible items.
	}

	///Default search.
	///Uses linear search, very safe, very slow.
	int search(int val)
	{
		assert(m_array != NULL); //No null pointers.

		// For every element in the array
		for (int i = 0; i < numElements; i++)
		{
			if (m_array[i] == val) // is it this one?
				return i;
		}

		return -1; // -1 is standard for "didn't work"
	}

	///List items in the array. 
	///Print directly to console.
	void listItems() {
		assert(m_array != NULL); // No null pointers.

		// If there are elements in the array
		if (numElements > 0) 
		{
			// print the contents of each to the console.
			for (int x = 0; x < numElements; ++x) 
			{
				cout << m_array[x] << "   ";
			}
			cout << endl;
		}
		else
			cout << "List Empty.." << endl;
	}
};



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
		assert(m_array != NULL);

		if (numElements >= 2)
		{
			for (int i = 1; i < numElements; ++i)
			{
				int temp = m_array[i];
				int j = i;

				while (j > 0 && m_array[j - 1] > temp)
				{
					--j;
					m_array[j+1] = m_array[j];
				}

				m_array[j] = temp;
			}
		}
	}

	void insertionSortDsc() {
		assert(m_array != NULL);
		
		if (numElements >= 2)
		{
			for (int i = 1; i < numElements; ++i)
			{
				int temp = m_array[i];
				int j = i;

				while (j > 0 && m_array[j - 1] < temp)
				{
					--j;
					m_array[j + 1] = m_array[j];
				}

				m_array[j] = temp;
			}
		}
	}

	void selectionSortAsc() {
		assert(m_array != NULL);

		for (int i = 0; i < numElements; ++i)
		{
			int pos = i;

			for (int j = i; j < numElements; ++j)
			{
				if (m_array[j] < m_array[pos])
					pos = j;
			}

			if (pos != i)
			{
				int temp = m_array[i];
				m_array[i] = m_array[pos];
				m_array[pos] = temp;
			}
		}
	}

	void selectionSortDsc() {
		assert(m_array != NULL);

		for (int i = 0; i < numElements; ++i)
		{
			int pos = i;

			for (int j = i; j < numElements; ++j)
			{
				if (m_array[j] > m_array[pos])
					pos = j;
			}

			if (pos != i)
			{
				int temp = m_array[i];
				m_array[i] = m_array[pos];
				m_array[pos] = temp;
			}
		}
	}

	void bubbleSortAsc() {

	}

	int binarySearch(int item) {
		int hi = numElements;
		int lo = 0;

		while (hi > lo)
		{
			int mid = (hi + lo) / 2;

			if (m_array[mid] == item)
				return mid;
			else if (m_array[mid] < item)
				lo = mid + 1;
			else
				hi = mid - 1;
		}
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

	u.insertionSortDsc();
	u.listItems();

	u.insertionSortAsc();
	u.listItems();	

	cout << u.binarySearch(9) << endl;
	cout << u.binarySearch(8) << endl;
	cout << u.binarySearch(13) << endl;
	cout << u.binarySearch(24) << endl;

	return 0;
}