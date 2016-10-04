#include "stdafx.h"
#include <iostream>
#include <cassert>
#include<cstring>
using namespace std;

///Stuff up here is the same as all the stuff in lab. This is how you set up a home made array.
class intArray
{
protected: //This is the notable exception.
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

	/// There is also this.
	/// I copied this out of my lab work, but I'm not fully sure what it is 
	/// at the moment of me writing this so I haven't touched it at all.
	void DisposeObject() {
		// I mean it seems pretty self explanatory, I'm just not sure what I'll use it for yet.
		delete this; 
	}

	///Default push, puts the element to be inserted in the last position of array
	///if there is space. Dynamically resizes if array is full.
	void push(int val, int resizeMod = 1)
	{
		assert(m_array != NULL); //No null pointers.

		if (numElements >= maxSize) // If the array is full
		{
			if (resizeMod == 0)
			{
				cout << "Array full. Not inserted." << endl;
				return;
			}
			else
				resize(maxSize + resizeMod);
		}

		m_array[numElements] = val; // or set value in the last position
		numElements++; //and increment that position.
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

	void resize(int newSize)
	{
		assert(m_array != NULL);

		// We NEED this much space.
		int numSpace = (newSize < numElements) ? newSize : numElements; // Whichever is less, newSize or the number of elements

		if (newSize < maxSize)
		{
			cout << "New size is smaller." << endl;
			// If the smaller size is less than the number of elements
			if (newSize < numElements)
			{
				// warn and adjust numElements.
				cout << "Some elements will be missing." << endl;
				numElements = newSize;
			}
		}

		int *n_array; // Get a new pointer.
		n_array = new int[newSize]; // Make a new array of the correct size with it.
		memset(n_array, 0, sizeof(int) * newSize); // Sets all items in the array to 0
		maxSize = newSize; // Adjust the maxSize

		memcpy(n_array, m_array, sizeof(int) * numSpace); // Copy a block the size of of numSpace * int's from m_array into n_array

		// Delete the array, and adjust the pointer.
		delete[] m_array; 
		m_array = n_array;
	}
};

///This is my new inherited class implementing an unordered integer array.
class uIntArray : public intArray
{
public:
	///Non-default constructor taking size 
	///and calling base constructor with that size.
	uIntArray(int size) : intArray(size) {};
	
	///Override intArray.remove() with an efficient version.
	void remove(int index)
	{
		assert(m_array != NULL); // No null pointers.

		// If index out of bounds
		if (index >= numElements)
		{
			cout << "Index out of bounds." << endl;
			return;
		}

		// If the array has more than one element 
		if (numElements > 1)
			m_array[index] = m_array[numElements - 1]; // copy last item into the position to be deleted.
		numElements--; // Decrement the number of accessible elements.
	}
};

/// Child class of intArray, implementing an ordered integer array.
class oIntArray : public intArray
{
public:
	/// Constructor calling parent constructor.
	oIntArray(int size) : intArray(size) {};

	///Override push from intArray to always keep elements sorted.
	void push(int val, int resizeMod = 1)
	{
		assert(m_array != NULL); //No null pointers.

		if (numElements >= maxSize) // If the array is full
		{
			if (resizeMod == 0)
			{
				cout << "Array full. Item not inserted." << endl;
				return;
			}
			else
				resize(maxSize + resizeMod);
		}		
		
		// If array has nothing in it
		if (numElements == 0)
		{
			m_array[numElements] = val; // set value in the last position
			numElements++; //and increment that position.
		}
		// But if you really have to put this in the array in the correct place...
		else 
		{
			// Use a modified insertion sort to insert the new element.
			
			/******** First check if it's already in the array ********/
			if (search(val) != -1)
			{
				cout << "Element already contained in the array. Did not push." << endl;
				return;
			}

			++numElements; // Create a space at the end of the array.
			// For each element in the array, starting at the end
			for (int i = numElements - 1; i >= 1; --i)
			{
				// If the new value is less than the current value
				if (m_array[i - 1] > val)
				{
					m_array[i] = m_array[i - 1]; // move it up in the array.
				}
				// Otherwise
				else
				{
					m_array[i] = val; // on the last duplicated, or the newest spot.
					return;
				}
			}
			// We made it to the bottom without placing the element, means it's 
			// the smallest thing in the array.
			m_array[0] = val;
		}
	}

	/// Override intArray search to use binary search, since all elements are sorted.
	int search(int val) {
		// We have the top and bottom of the array.
		int hi = numElements;
		int lo = 0;

		// While the head of our search is still before the tail 
		while (hi > lo)
		{
			// find the middle.
			int mid = (hi + lo) / 2;

			// If our search value is in the middle
			if (m_array[mid] == val)
				return mid; // return it's position.
			else if (m_array[mid] < val) // Higher?
				lo = mid + 1; // Search the upper half only.
			else // Lower?
				hi = mid - 1; // Search the lower half only.
		}
		return -1; // -1 is standard for "didn't work".
	}
};

int main() {
	cout << "Making an integer array." << endl;

	intArray myArray = intArray(200000);
	myArray.listItems();

	cout << myArray.getSize() << endl;
	cout << myArray.getMaxSize() << endl;

	myArray.push(91);
	myArray.push(23);
	myArray.push(6);
	myArray.push(42);
	myArray.push(50);
	myArray.push(13);
	for (int i = myArray.getSize(); i < myArray.getMaxSize(); ++i)
	{
		myArray.push(i);
	}
	
	myArray.push(7);

	cout << myArray.getSize()
		<< " / " << myArray.getMaxSize()
		<<endl;
	//myArray.listItems();

	myArray.remove(1);
	//myArray.listItems();

	cout << "Making an unordered integer array." << endl;
	uIntArray uArray = uIntArray(6);
	uArray.listItems();

	cout << uArray.getSize() << endl;
	cout << uArray.getMaxSize() << endl;

	uArray.push(91);
	uArray.push(23);
	uArray.push(6);
	uArray.push(42);
	uArray.push(50);
	uArray.push(13);
	
	uArray.push(7, 0);

	cout << uArray.getSize()
		<< " / " << uArray.getMaxSize() 
		<< endl;
	uArray.listItems();

	uArray.remove(1);
	uArray.listItems();

	cout << "Making an ordered integer array." << endl;
	oIntArray oArray = oIntArray(6);
	oArray.listItems();

	cout << oArray.getSize() << endl;
	cout << oArray.getMaxSize() << endl;

	oArray.push(23);
	oArray.push(91);
	oArray.push(6);
	oArray.push(42);
	oArray.push(50);
	oArray.push(13);

	oArray.push(7, 5);

	cout << oArray.getSize()
		<< "/ " << oArray.getMaxSize()
		<< endl;
	oArray.listItems();

	oArray.remove(1);
	oArray.listItems();

	oArray.push(42);
	cout << oArray.getSize() << endl;
	oArray.listItems();
	oArray.push(78);
	oArray.listItems();

	cout << "Trying to resize array." << endl;
	myArray.push(100);
	cout << myArray.getMaxSize() << endl;
	//myArray.listItems();
	myArray.resize(8);
	cout << myArray.getMaxSize() << endl;
	//myArray.listItems();
	myArray.push(777);
	myArray.listItems();
	cout << myArray.getSize() << endl;

	cout << "Trying to resize a child array." << endl;
	uArray.listItems();
	cout << uArray.getMaxSize() << endl;
	uArray.resize(5);
	uArray.listItems();
	cout << uArray.getSize() << endl;
	cout << uArray.getMaxSize() << endl;
	uArray.resize(10);
	cout << uArray.getSize() << endl;
	cout << uArray.getMaxSize() << endl;

	return 0;
}