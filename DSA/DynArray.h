// DynArray.h - A dynamically-allocated resizeable array
//	(similar to the stl vector)

#pragma once

#if LAB_3
template<typename Type>
class DynArray {

	friend class TestSuite;	// Giving access to test code

	Type* mArray;
	unsigned int mSize;
	unsigned int mCapacity;

public:

	// Default constructor
//		Creates a new object
// In:	_startingCap		An initial size to start the array at (optional)
	DynArray(unsigned int _startingCap = 0) {
		//mArray = new Type[_startingCap];
		//mSize = 0;
		if (_startingCap == 0)
		{
			mArray = nullptr;
		}
		else
		{
			mArray = new Type[_startingCap];
		}
		mCapacity = _startingCap;
	}

	// Destructor
	//		Cleans up all dynamically allocated memory
	~DynArray() {
		Clear();
	}

	// Copy constructor
	//		Used to initialize one object to another
	// In:	_da				The object to copy from
	DynArray(const DynArray& _da) {
		*this = _da;
	}

	// Assignment operator
	//		Used to assign one object to another
	// In:	_da				The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	DynArray& operator=(const DynArray& _da) {

		if (this != &_da)
		{
			delete[]mArray;
			mCapacity = _da.mCapacity;
			mSize = _da.mSize;
			mArray = new Type[mCapacity];
			for (size_t i = 0; i < mSize; i++)
			{
				mArray[i] = _da.mArray[i]; 
			}
		}
		return *this;
	}

	// Overloaded [] operator
	//		Used to access an element in the internal array (read-only)
	// In:	_index			The index to access at
	//
	// Return: The item at the specified index (by reference)
	const Type& operator[](int _index) const {
		
		return mArray[_index];
		
	}

	// Overloaded [] operator
	//		Used to access an element in the internal array (writeable)
	// In:	_index			The index to access at
	//
	// Return: The item at the specified index (by reference)
	Type& operator[](int _index) {
		return mArray[_index];
	}

	// Get the current number of elements actively being used
	//
	// Return: The current number of elements used
	int Size() const {
		return mSize;
	}

	// Get the current capacity of the internal array
	//
	// Return: The capacity of the array
	int Capacity() const {
	
		return mCapacity;
	}

	// Clear the class for re-use
	//			Should clean up all dynamic memory and leave the object the same as if the default constructor had been called
	void Clear() {
		delete[]mArray;
		mCapacity = 0;
		mSize = 0;
		mArray = nullptr;
	}

	// Add an item to the end of the array
	//			Should resize the array if needed
	// In:	_data			The item to be added
	void Append(const Type& _data) {
		//mSize = _data;
		mArray[mSize] = _data;
		if (mSize >= mCapacity)
		{
		/*	mCapacity *= 2;
			if (mCapacity == 0)
			{
				mCapacity = 1;
			}*/
			Reserve();
			//mArray[mSize] = _data;
		}
		//mArray[mCapacity] = _data;
		//mArray = new Type[_data];
		//mArray[mSize] = _data;
		mSize++;
	}

	// Resizes the internal array, and copies all data over
	// In: _newCapacity		The new capacity of the array
	//	NOTE:	If 0 is passed, the array should double in size
	//			If _newCapacity < mCapacity, do nothing
	//
	//	SPECIAL CASE: If mCapacity is 0, then it should be set to 1
	void Reserve(unsigned int _newCapacity = 0) {
		
		Type* temp;
		if (_newCapacity == 0)
		{
			mCapacity *= 2;
			if (mCapacity==0)
			{
				mCapacity = 1;
			}
			_newCapacity = mCapacity;
		}
		if (_newCapacity >= mCapacity)
		{
			/*mCapacity = _newCapacity;*/
			temp = new Type[mCapacity];
			for (size_t i = 0; i < mSize; i++)
			{
				temp[i] = mArray[i];
			}
			mCapacity = _newCapacity;
			/*for (size_t i = 0; i < mCapacity; i++)
			{
				delete[] mArray[i];
			}*/
			delete[]mArray;
			mArray = temp;
			/*for (size_t i = 0; i < mSize; i++)
			{
				mArray[i] = temp[i];
			}*/
			//delete temp;
		}
		
		//delete[]temp;
	}

};
#endif
