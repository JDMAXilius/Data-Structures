#pragma once

#if LAB_6
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

class DSA_Lab6 {

	friend class TestSuite;	// Giving access to test code

	// Data members
	int mLetterValues[26];
	unordered_map<string, int> mScrabbleMap;

public:

	// In Scrabble, each letter has a value associated with it.
	// This method will populate the array of letter values.
	//
	// In:	_letterValues		The array of 26 values
	void PopulateLetterValues(const int* _letterValues) {
		
		for (size_t i = 0; i < 26; i++)
		{
			mLetterValues[i] = _letterValues[i];
		}
	}

	// Retrieve the value of a particular letter
	// 
	// In:	_letter			The letter to get the score for
	//
	// Return:	The score value for the letter passed in
	// NOTE:	The letter passed in will always be upper-case
	int GetLetterValue(char _letter) {
		
		/*char letter = ' ';
		for (size_t i = 0; i < 26; i++)
		{
			letter = mLetterValues[i];
			_letter = letter;
		}*/
		return mLetterValues[_letter - 65];
	}
	
	// Get the value of a word
	//		This is done by adding up the values of each letter in the word
	//
	// In:	_word		The word to get the value of
	//
	// Return: The total value of the word
	int GetWordValue(string _word) {
		
		int value = 0;
		for (size_t i = 0; i < _word.size(); i++)
		{
			value += GetLetterValue(_word[i]);
		}
		return value;
		//return mLetterValues[_letter - 65];
	}

	// Create a pair to add into the scrabbleMap
	//		This will have a "first" of the word, and a "second" of the total score
	//
	// In:	_word		The word for the pair
	//
	// Return: A pair that contains the word and the total score
	pair<string, int> CreatePair(string _word) {
		pair <string, int> vpair;
		vpair.first = _word;
		vpair.second = GetWordValue(_word);
		return vpair;
	}

	// Load a file containing all of the possible scrabble words, along with their values
	//		This file will contain one word per line
	// In:	_filename	The name of the file to load
	//
	// Note: You may want to use one or more existing methods to help.
	void LoadWords(const char* _filename) {
		ifstream file(_filename);
		string doc;
		if (file.is_open())
		{
			while (getline(file,doc))
			{
				mScrabbleMap.insert(CreatePair(doc));
			}
			file.close();
		}
		//mScrabbleMap = unordered_map<string, int>;
	}
	
	/**********************************/
	/* ONLY FOR USE IN FindValueInMap */
	/**********************************/
	int values[26] = { 1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10 };

	// Searches for a word in the map, and retrieves the score for that word
	//		This will make use of some of your previous methods
	//		Use above "values" array to populate your letter scores
	//		Use "words.txt" for loading words
	//
	// In:	_word			The word to search for
	//
	// Return: The word score for _word (or -1 if not found)
	int FindValueInMap(string _word) {
		PopulateLetterValues(values);
		LoadWords("words.txt");
		if (mScrabbleMap.find(_word) != mScrabbleMap.end())
		{
			return mScrabbleMap[_word];
		}
		else
		{
			return -1;
		}
	}
};
#endif