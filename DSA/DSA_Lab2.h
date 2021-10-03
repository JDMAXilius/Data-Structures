#pragma once

// Only compile if LAB_2 is on
#if LAB_2

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Checks to see if a number is a palindrome (reads the same forwards and backwards)
//		An example of a palindrome word would be "racecar"
//
// In: _num			The number to check
//
// Return: True, if the number is a palindrome number
inline bool IsPalindromeNumber(unsigned int _num) {
	
	int rev = 0;
	//int val = 0;
	bool check = false;
	//val = _num;
	/*while (_num > 0){
		rev = rev * 10 + _num % 10;
		_num = _num / 10;
	}*/
	for (int i = _num; i > 0; i /= 10)
	{
		rev = rev * 10 + i % 10;
	}
	/*while (_num != 0)
	{
		val = _num % 10;
		rev = rev * 10 + val;
		_num = _num / 10;
	}*/
	if (_num == rev)
	{
		check = true;
	}
		
	return check;
}


class DSA_Lab2
{
	friend class TestSuite;	// Giving access to test code


private:

	vector<unsigned int> mValues;		// contains all of the values
	vector<unsigned int> mPalindromes;	// contains just the numbers that are palindromes

public:

	// Fill out the vector with the contents of the binary file
	//		First four bytes of the file are the number of ints in the file
	//
	// In:	_input		Name of the file to open
	//
	// Note: Make sure the vector is empty and shrunk to 0 capacity before adding values
	void Fill(const char* _input) {
		Clear();
		ifstream ifl;
		int ffbytes;
		int ffbytes1;
		ifl.open(_input, ios_base::binary);
		ifl.read((char*)&ffbytes, sizeof(int));
		for (size_t i = 0; i < ffbytes; i++)
		{
			ifl.read((char*)&ffbytes1, sizeof(int));
			mValues.push_back(ffbytes1);
		} 
		mValues.shrink_to_fit();
		ifl.close();
		/*mValues = new vector <const char>(_input);*/
		//mValues.push_back(_input);

		//while (!ifl.eof()) {
		//	ifl >> temp;
		//	intVec.push_back(temp);
		//}

		//// Done with the file
		//
	}

	// Fill out the vector with the contents of an array
	//
	// In:	_arr			The array of values
	//		_size			The number of elements in the array
	//
	// Note: Make sure the vector is empty and shrunk to 0 capacity before adding values
	void Fill(const unsigned int* _arr, int _size) {
		Clear();
		for (size_t i = 0; i < _size; i++)
		{
			mValues.push_back(_arr[i]);
		}
	}

	// Remove all elements from vector and decrease capacity to 0
	void Clear() {
		//vector<unsigned int> erasemValues;
		//delete mValues[];
		mValues.clear();
		//mValues.empty();
		mValues.shrink_to_fit();
		//erasemValues = mValues.erase(erasemValues);
		//mValues[] = { 0 };
		//mValues.reserve(0);
		mPalindromes.clear();
		mPalindromes.shrink_to_fit();
		//mValues = nullptr;
		/*for (size_t i = 0; i < mValues.capacity(); i++)
		{
			delete mValues[i];
		}*/
	}

	// Sort the vector 
	//
	// In:	_ascending		To sort in ascending order or not
	void Sort(bool _ascending) {
		if (_ascending==true)
		{
			sort(mValues.begin(), mValues.end());
		}
		else
		{
			sort(mValues.begin(), mValues.end(), greater<>());
		}
	}

	// Get an individual element from the mValues vector
	int operator[](int _index) {
		return mValues[_index];
	}

	// Determine if a value is present in the vector
	// 
	// In:	_val		The value to check for
	//
	// Return: True, if the value is present
	bool Contains(unsigned int _val) const {
	
		bool check = false;
		for (size_t i = 0; i < mValues.size(); i++)
		{
			if (mValues[i] == _val)
			{
				check = true;
			}
		}
		return check;
	}

	// Move all palindrome numbers from mValues vector to mPalindromes vector
	//
	// Pseudocode:
	//		iterate through the main values vector
	//			if the value is a palindrome
	//				add it to the palindrome vector
	//				remove it from the values vector
	void MovePalindromes() {
		//vector<unsigned int> erasemValues= mValues.begin();
		bool check;

		/*for (size_t i = 0; i < mValues.size(); i++)
		{
			check = IsPalindromeNumber(mValues[i]);

			if (check==true)
			{
				mPalindromes.push_back(mValues[i]);
				
			}
		}*/

	/*	for (vector<unsigned int>::iterator iter = mValues.begin(); iter != mValues.end(); ++iter)
		{
			check = IsPalindromeNumber(*iter);
			if (check == true)
			{
				mPalindromes.push_back(*iter);
				iter=mValues.erase(iter);
			}
		}*/
		vector<unsigned int>::iterator iter = mValues.begin();

		while (iter != mValues.end())
		{
			check = IsPalindromeNumber(*iter);
			if (check == true)
			{
				mPalindromes.push_back(*iter);
				iter=mValues.erase(iter);
			}
			++iter;
		}
	}
};




#endif