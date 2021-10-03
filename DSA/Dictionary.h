// Dictionary.h - A hash-mapped data structure using key/value pairs
//				  and separate chaining

#pragma once

/************/
/* Includes */
/************/
#include <list>
using namespace std;


template<typename Key, typename Value>
class Dictionary {

	friend class TestSuite;	// Giving access to test code

	// The objects stored in the hash-table
	struct Pair {
		Key key;			// The key for insertion/lookup
		Value value;		// The data

		// Constructor
		// In:	_key
		//		_value
		Pair(const Key& _key, const Value& _value) {
			key = _key;
			value = _value;
		}

		// For testing
		bool operator==(const Pair& _comp) {
			return (_comp.key == key &&
				_comp.value == value);
		}
	};

	list<Pair>* mTable;				// A dynamic array of lists (these are the buckets)
	unsigned int mNumBuckets;		// Number of elements in mTable
	unsigned int(*mHashFunc)(const Key&);	// Pointer to the hash function

public:

	// Constructor
	// In:	_numBuckets			The number of elements to allocate
	//		_hashFunc			The hashing function to be used
	Dictionary(unsigned int _numBuckets, unsigned int (*_hashFunc)(const Key&)) {
		mNumBuckets = _numBuckets;
		mHashFunc= _hashFunc;
		//list<Pair>* listc = new list < Pair>(_hashFunc);
		//list<Pair>* listc = new mHashFunc();
		mTable = new list<Pair>[mNumBuckets];
	}

	// Destructor
	//		Cleans up any dynamically allocated memory
	~Dictionary() {
		Clear();
		/*for (size_t i = 0; i < mNumBuckets; i++)
		{
			delete[] mTable[i];
		}*/
		delete[] mTable;
	}

	// Copy constructor
	//		Used to initialize one object to another
	// In:	_dict				The object to copy from
	Dictionary(const Dictionary& _dict) {
		*this = _dict;
		//this->copyDic(_dict);
	}

	// Assignment operator
	//		Used to assign one object to another
	// In:	_dict				The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	Dictionary& operator=(const Dictionary& _dict) {
		
		if (this != &_dict)
		{
			Clear();
			delete[] mTable;
			//mTable = _dict.mTable;
			mNumBuckets = _dict.mNumBuckets;
			mHashFunc = _dict.mHashFunc;

			/*this->deleteDict();
			this->copyDict(_dict);*/

			mTable = new list<Pair>[mNumBuckets];
			for (size_t i = 0; i < mNumBuckets; i++)
			{
				mTable[i] = _dict.mTable[i];
			}
		}
		return *this;
	}
	 
	// Clear
	//		Clears all internal data being stored
	//  NOTE:	Does not delete table or reset hash function
	void Clear() {
		
		if (mTable != nullptr) {

			
			for (size_t i = 0; i < mNumBuckets; i++)
			{
				mTable[i].clear();
			}
			/*mNumBuckets = 0;
			mHashFunc = nullptr;
			mTable = nullptr;*/
			
		}
	}

	// Insert an item into the table
	// In:	_key		The key to add at	
	//		_value		The value at the key
	//
	// NOTE:	If there is already an item at the provided key, overwrite it.
	void Insert(const Key& _key, const Value& _value) {
		
		
		int hashValue = mHashFunc(_key);
		//mTable[hashValue];
		bool check = false;

		for (typename list<Pair>::iterator i = mTable[hashValue].begin(); i != mTable[hashValue].end(); i++)
		{
			
			if (i->key == _key)
			{
				check = true;
				i->value = _value;
				//mTable[i].push_back(_value);
				//mTable[i].emplace_back(_value);
				//break;
			}

			
				
			//mTable[_key].push_back(_value);
			//if (i != mTable[hashValue].end())
				//mTable[hashValue].erase(i);
		}
		if (!check)
		{
			Pair mtableValue = Pair(_key, _value);
			mTable[hashValue].push_back(mtableValue);
			//mTable->emplace_back(_key, _value);
		}
		
		//mTable = new list<Pair> mTableValue[hashValue];
		

		//in = int(k mod max)
		//	p[in] = (n_type*)malloc(sizeof(n_type))
		//	p[in]->d = k
		//	if (r[in] == NULL) then
		//		r[in] = p[in]
		//		r[in]->n = NULL
		//		t[in] = p[in]
		//	else
		//		t[in] = r[in]
		//		while (t[in]->n != NULL)
		//			t[in] = t[in]->n
		//			t[in]->n = p[in]
	}

	// Find a value at a specified key
	// In:	_key		The key to search for	
	//
	// Return: A const pointer to the value at the searched key
	// NOTE:		Return a null pointer if key is not present
	const Value* Find(const Key& _key) {
		
		//const Value value;
		int hashValue = mHashFunc(_key);

		for (typename list<Pair>::iterator i = mTable[hashValue].begin(); i != mTable[hashValue].end(); i++)
		{

			//if (i->key != _key)
			{
				if (i->key == _key)
				{
					/*value = i->value;*/
					return &i->value;
					
				}
			}
			//else
			{
				//&i->key = _key;
			}


			//t[in] = r[in]
			//	while (t[in] != NULL) do
			//		if (t[in]->d == k) then
			//			Print “Search key is found”.
			//			flag = 1
			//			break
			//		else
			//			t[in] = t[in]->n
			//			if (flag == 0)
			//				Print “search key not found”.
		}
		return nullptr;
	}

	// Remove a value at a specified key
	// In:	_key		The key to remove
	//
	// Return: True, if an item was removed
	bool Remove(const Key& _key) {
		bool check = false;
		int hashValue = mHashFunc(_key);
		
		//list<Pair>::iterator i;
		for (typename list<Pair>::iterator i= mTable[hashValue].begin(); i != mTable[hashValue].end(); i++)
		{

			if (i->key == _key)
			{
				mTable[hashValue].erase(i);
				check = true;
				return true;
			}

			else
			{
				check = false;
			}
				
		}

		return false;
	}
};