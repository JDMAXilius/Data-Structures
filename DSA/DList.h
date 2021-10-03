// DList.h - A doubly-linked list
// (similar to the stl list)

#pragma once


template<typename Type>
class DList {

	friend class TestSuite; // Giving access to test code

	// Node structor a doubly linked list
	struct Node {

		// Data members
		Type data;				// The value being stored
		Node* next, * prev;		// Pointers to the next and previous nodes

		// Constructor
		//
		// In:	_data			The value to store
		//		_next			Pointer to the next node in the list
		//		_prev			Pointer to the previous node in the list
		Node(const Type& _data, Node* _next = nullptr, Node* _prev = nullptr) {
			//Node* n = new Node(?);
			/*Node* n = new Node;
			n->data=_data;
			n->next = _next;
			n->prev = _prev;*/
			data = _data;
			next = _next;
			prev = _prev;
			
		}
	};

public:

	// An iterator class to made traversal more efficient
	class Iterator {
	public:

		// Data members
		Node* mCurr;

		// Pre-fix increment operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
							I
							R
		*/
		// Return:	The Iterator (the invoking object)
		Iterator& operator++() {
			mCurr = mCurr->next;
			return *this;
			
			/*int temp = val;
			val += 1;
			return temp;*/
		}

		// Post-fix increment operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
					  R		I

		*/
		// Return:	The Iterator (before increment)
		// NOTE:	Will need a temporary pointer
		Iterator operator++(int) {
			Iterator temp=*this;
			++(*this);
			return temp;
		}

		// Pre-fix decrement operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
				I
				R
		*/
		// Return:	The Iterator (the invoking object)
		Iterator& operator--() {
			mCurr = mCurr->prev;
			return *this;

		}

		// Post-fix decrement operator
		//
		// Example:
		//		I - Iterator's curr
		//		R - Return
		/*
			Before

			0<-[4]<->[5]<->[6]->0
					  I

			After

			0<-[4]<->[5]<->[6]->0
				I	  R

		*/
		// Return:	The Iterator (before decrement)
		// NOTE:	Will need a temporary pointer
		Iterator operator--(int) {
			Iterator temp1 = *this;
			--(*this);
			return temp1;
		}

		// Gets the value the iterator is currently pointing to
		//
		// Return:	The data of the current iterator
		Type& operator*() {
			Iterator temp2 = *this;
			return temp2;
		}
	};

	// Data members
	Node* mHead;			// The head (first node) of the list
	Node* mTail;			// The tail (last node) of the list
	unsigned int mSize;		// Current number of nodes being stored

public:

	// Default constructor
	//		Creates a new empty linked list
	DList() {
		mHead = nullptr;
		mTail = nullptr;
		mSize=0;
	}

	// Destructor
	//		Cleans up all dynamically allocated memory
	~DList() {
		
			Clear();
	}

	// Copy constructor
	//		Used to initialize one object to another
	//
	// In:	_copy			The object to copy from
	DList(const DList& _copy) {
		*this = _copy;
	}

	// Assignment operator
	//		Used to assign one object to another
	//
	// In:	_assign			The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	DList& operator=(const DList& _assign) {

		if (this != &_assign)
		{
			Clear();
			delete mHead;
			delete mTail;
			mSize = _assign.mSize;

			Node* assingIter = _assign.mHead;
			while (assingIter != nullptr)
			{
				Node* n = new Node(assingIter->data, nullptr, nullptr);
				n->next = nullptr;
				n->data = assingIter->data;
				if (mTail !=nullptr)
				{
					mTail->next = n;
					n->prev = mTail;
					mTail = n;
				}
				else
				{
					n->prev = nullptr;
					mHead=n;
					mTail=n;

				}
				assingIter = assingIter->next;
			}
			/*
			for (size_t i = 0; i < mSize; i++)
			{
				mHead[i] = _assign.mHead[i];
				mTail[i] = _assign.mmTailt[i];
			}*/
		}
		return *this;
	}

private:

	// Optional recursive helper method for use with Rule of 3
	//
	// In:	_curr		The current Node to copy
	void Copy(const Node* _curr) {

	}

public:
	// Add a piece of data to the front of the list
	//
	// In:	_data			The object to add to the list
	void AddHead(const Type& _data) {
		
		Node* n = new Node(_data);
		if (mHead == nullptr) {
			mHead = n;
			mTail = n;
		}
		else
		{
		
			mHead->prev = n;
			n->next = mHead;
			mHead = n;
		}
		mSize++;
	}

	// Add a piece of data to the end of the list
	//
	// In:	_data			The object to add to the list
	void AddTail(const Type& _data) {
		
		Node* n = new Node(_data);
		if (mHead == nullptr) {
			mTail = n;
            mHead = n;
		}
		else
		{

			mTail->next = n;
			n->prev = mTail;
			mTail = n;
		}
		mSize++;
	}

	// Clear the list of all dynamic memory
	//			Resets the list to its default state
	void Clear() {
		if (mHead != nullptr) {
			
			Node* tempH = mHead;
			for (size_t i = 0; i < mSize; i++)
			{
				Node* tempHN = tempH->next;
				delete tempH;
				tempH = tempHN;
			}
			mSize = 0;
			mHead = nullptr;
			mTail = nullptr;
		}
	}

private:

	// Optional recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	void Clear(const Node* _curr) {
		if (mHead != nullptr) {
			_curr = mHead;
			mHead = mHead->next;
			delete _curr;
		}
	}

public:

	// Insert a piece of data *before* the passed-in iterator
	//
	// In:	_iter		The iterator
	//		_data		The value to add
	//
	// Example:
	/*
		Before

			0<-[4]<->[5]<->[6]->0
					  I

		After

			0<-[4]<->[9]<->[5]<->[6]->0
					  I
	*/
	// Return:	The iterator
	// SPECIAL CASE:	Inserting at head or empty list
	// NOTE:	The iterator should now be pointing to the new node created
	Iterator Insert(Iterator& _iter, const Type& _data) {
		Node* n = new Node(_data);

		if (_iter.mCurr == nullptr || _iter.mCurr == mHead )
		{
			AddHead(_data);
			_iter.mCurr = mHead;

		}
		else
		{
			n->prev = _iter.mCurr->prev;
			n->next = _iter.mCurr;

			_iter.mCurr->prev->next = n;
			_iter.mCurr->prev = n;
			_iter.mCurr = n;
		}
		//mSize++;
		return _iter;
	}

	// Erase a Node from the list
	//
	// In:	_iter		The iterator
	//
	// Example
	/*

		Before

			0<-[4]<->[5]<->[6]->0
					  I

		After

			0<-[4]<->[6]->0
					  I
	*/
	// Return:	The iterator
	// SPECIAL CASE:	Erasing head or tail
	// NOTE:	The iterator should now be pointing at the node after the one erased
	Iterator Erase(Iterator& _iter) {
		Node* tempH;
		if (_iter.mCurr == nullptr)
		{
			
			/*for (size_t i = 0; i < mSize; i++)
			{
				_iter = tempH->next;
				delete tempH;
				tempH = _iter;
			}*/
		}
		else if(_iter.mCurr==mHead)
		{
			tempH = _iter.mCurr->next;
			delete mHead;
			mHead = tempH;
			_iter.mCurr = mHead;
			_iter.mCurr->prev = nullptr;
		}
		else if (_iter.mCurr == mTail)
		{
			tempH = _iter.mCurr->prev;
			delete mTail;
			mTail = tempH;
			mTail->next = nullptr;
			_iter.mCurr = mTail->next;
			
		}
		else
		{
			tempH = _iter.mCurr;
			_iter.mCurr->prev->next = _iter.mCurr->next;
			_iter.mCurr->next->prev = _iter.mCurr->prev;

			Node* tempH1 = _iter.mCurr->next;
			delete tempH;
	
			_iter.mCurr = tempH1;
			
			/*for (size_t i = 0; i < mSize; i++)
			{
				_iter = tempH->prev;
				delete tempH;
				tempH = _iter;
			}*/
		}
		mSize--;
		return _iter;
	}

	// Set an Iterator at the front of the list
	// 
	// Return: An iterator that is pointing to the list's head
	Iterator Begin() {
		Iterator n;
		n.mCurr = mHead;
		return n;
	}

	// Set an Iterator pointing to the end of the list
	// 
	// Return: An iterator that is pointing to a null pointer
	Iterator End() {
		Iterator n;
		n.mCurr = mTail;
		return n;
	}
};