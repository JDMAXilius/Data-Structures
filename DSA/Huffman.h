// Class to wrap up Huffman compression algorithm

#pragma once

/************/
/* Includes */
/************/
#include <queue>
#include "BitStream.h"



class Huffman {

	friend class TestSuite; // Giving access to test code

	// A node for a a Huffman tree
	struct HuffNode {
		short value;		// The value to store (-1 if not a leaf node, 0-255 for the ascii value)
		unsigned int freq;	// The frequency of the node
		HuffNode* left;		// Left child
		HuffNode* right;	// Right child
		HuffNode* parent;	// Parent node

		// Constructor
		// 
		// In:	_value		The value of the node
		//		_freq		The frequency of the node
		//		_left		The node's left child (OPTIONAL)
		//		_right		The node's right child (OPTIONAL)
		//		_parent		The parent node (OPTIONAL)
		HuffNode(short _value, unsigned int _freq, HuffNode* _left = nullptr, HuffNode* _right = nullptr, HuffNode* _parent = nullptr)
			: value(_value), freq(_freq), left(_left), right(_right), parent(_parent) {
			/*value = _value;
			freq = _freq;
			left = _left;
			right = _right;
			parent = _parent;*/
		}

		// Copy constructor
		//
		// In:	_hnode		The node to copy from
		HuffNode(const HuffNode& _hnode)
			: value(_hnode.value), freq(_hnode.freq), left(_hnode.left), right(_hnode.right), parent(_hnode.parent) {
			/**this = _hnode;*/
		}
	};

	// A binary predicate used to compare HuffNodes
	//		This is used in the GenerateTree method
	struct HuffCompare {
		// Compare the frequency of two nodes
		// 
		// In:	_a		The first node
		//		_b		The second node
		//
		// Return: True, if _a's freq is greater than _b's freq
		bool operator() (const HuffNode* _a, const HuffNode* _b) {
			return(_a->freq > _b->freq);
		}
	};


	// Data members
	string mFileName;						// The name of the file to open for read/write
	unsigned int mFrequencyTable[257];		// The frequency of each character in the file (the index in the array is the char's ASCII value)
											//		[256] of the array is the total count of characters in the file
	vector<HuffNode*> mLeafList;			// Contains all of the dynamically allocated leaf nodes
	HuffNode* mRoot;						// The root of the huffman tree (set in GenerateTree)
	vector<bool> mEncodingTable[256];		// Contains all of the bit-codes used to compress/decompress a file

	// Default constructor
	//
	// In:	_fileName		The name of the file to open
	//		_access			The way to open the file
	Huffman(string _fileName) {
		// 1. Assign the data members the values from the parameters
		mFileName = _fileName;
		// 2. Zero out the frequency table
		for (size_t i = 0; i < 257; i++)
		{
			mFrequencyTable[i] = 0;
		}
	}


	// Generate the frequency table for the Huffman algorithm (WRITING ONLY)
	//
	// NOTE:	mFrequencyTable is an array of 257 unsigned ints representing the 
	//			count of each character in the file (the index in the array is the char's ASCII value)
	//				Example:  'A' is ASCII 65, so if A is the character being checked, [65] of your array would get incremented
	//			[256] of your array is the total count of characters in the file
	void GenerateFrequencyTable() {
			// 1. Open the file in binary mode
		ifstream bFile(mFileName, ios::out | ios::binary);

			// 2. Get the total count of the file	(This can also be done in the next step instead)
		size_t totalCount;

		bFile.seekg(0, bFile.end);
		totalCount = bFile.tellg();
		bFile.seekg(0, bFile.beg);
			// 3. Read the file one byte at a time, and increment the corresponding index
		char* fByte = new char[totalCount];
		bFile.read(fByte, totalCount);

		for (size_t i = 0; i < totalCount; i++)
		{
			mFrequencyTable[fByte[i]]++;
			mFrequencyTable[256]++;
			//mFrequencyTable[(unsigned char)bFile.get()++];
		}

			// 4. Close the file when complete
		bFile.close();
		delete[] fByte;
	}

	// Generate the leaf list for the Huffman algorithm (used in READ AND WRITE)
	//
	// Note:	Will cause leaks until ClearTree is implemented
	void GenerateLeafList() {
		// 1. Iterate through the frequency table (for all ASCII values) and dynamically create a leaf node for each non-0
		//		frequency.  Add it to the mLeafList vector.
		for (short i = 0; i < 256; i++)
		{
			if (mFrequencyTable[i] != 0)
			{
				struct HuffNode* leafList = new struct HuffNode(i, mFrequencyTable[i]);
				mLeafList.push_back(leafList);
			}
		}
	}

	// Generate a Huffman tree
	void GenerateTree() {
		// 1. Create the priority queue
		//		This will be storing HuffNode*'s
		//		in a vector, and will be using the HuffCompare for comparison
		priority_queue<HuffNode*, vector<HuffNode*>, HuffCompare> pq;
		// 2. Add in all values from your leaf list
		for (size_t i = 0; i < mLeafList.size(); i++)
		{
			pq.push(mLeafList[i]);
		}
		// 3. Enter the tree generation algorithm
		//		While the queue has more than 1 node
		//			Store the top two nodes into some temporary pointers and pop them
		//			Create a new parent node /w 1st node as left, and 2nd as right
		//			Set the parent value to -1, and frequency to the sum of its children
		//			Set the 1st and 2nd node's parent to the new node you created
		//			Insert new node into queue

		while (pq.size() > 1)
		{
			//Store the top two nodes into some temporary pointers and pop them
			HuffNode* tempTopNode1 = pq.top();
			pq.pop();
			HuffNode* tempTopNode2 = pq.top();
			pq.pop();

			//Create a new parent node /w 1st node as left, and 2nd as right
			HuffNode* parentNode=nullptr;
			

			//Set the parent value to -1, and frequency to the sum of its children
			/*parentNode->value = -1;
			parentNode->freq = tempTopNode1->freq + tempTopNode2->freq;*/
			parentNode = new HuffNode(-1, tempTopNode1->freq + tempTopNode2->freq, tempTopNode1, tempTopNode2);

			//Set the 1st and 2nd node's parent to the new node you created
			tempTopNode1->parent = parentNode;
			tempTopNode2->parent = parentNode;

			//Insert new node into queue
			pq.push(parentNode);

		}

		// 4. Set the root of the tree (this will be the only node in the queue)
		mRoot = pq.top();
		pq.pop();
	}

	// Generating the encoding table for the Huffman algorithm
	//
	//				Each vector will contain the bit-code corresponding to that index in the frequency table
	void GenerateEncodingTable() {
		// 1. Go through all of the leaf nodes and generate the bit codes
		//		You will do this by traversing up the tree from the leaf node
		//			As you move up, push a 0 to the vector if you passed through a left child connection
		//			and a 1 if you passed through a right
		//			Once you hit the root node, reverse the values in the vector
		
		HuffNode* bitCodes=nullptr;

		for (size_t i = 0; i < mLeafList.size(); i++)
		{
		     bitCodes = mLeafList[i];
			while (bitCodes->parent !=nullptr)
			{
				//As you move up, push a 0 to the vector if you passed through a left child connection
				if (bitCodes->parent->left == bitCodes)
				{
					mEncodingTable[mLeafList[i]->value].push_back(0);
				}

				//and a 1 if you passed through a right
				if (bitCodes->parent->right == bitCodes)
				{
					mEncodingTable[mLeafList[i]->value].push_back(1);
				}

				bitCodes = bitCodes->parent;
			}
			
			//Once you hit the root node, reverse the values in the vector
			reverse(mEncodingTable[mLeafList[i]->value].begin(), mEncodingTable[mLeafList[i]->value].end());
		}
		
	}

	// Clear the tree of all dynamic memory (by using the helper function)
	void ClearTree() {
		// 1. Call the helper function with the root and then set it back to null
		ClearTree(mRoot);
		mRoot = nullptr;
	}

	// Clear the tree of all dynamic memory (recursive helper function)
	// 
	// In:	_curr		The current node to clean up
	//
	// Note:	This will be a recursive function that does a post-order deletion
	void ClearTree(HuffNode* _curr) {
		if (_curr == nullptr)
		{
			return;
		}
		ClearTree(_curr->left);
		ClearTree(_curr->right);
		//free(_curr);
		delete _curr;
	}

	// Write a Huffman compressed file to disk
	//
	// In:	_outputFile			Where to write the compressed data to
	//
	// Note: You will use most of your other functionality to complete this function
	void Compress(const char* _outputFile) {
		// 1. Create the frequency table, leaf list, tree, and encoding table
		GenerateFrequencyTable();
		GenerateLeafList();
		GenerateTree();
		GenerateEncodingTable();

		// 2. Create a BitOStream and supply it the huffman header
		BitOStream bStremFile(_outputFile, (char*)mFrequencyTable, sizeof(int) * 257);

		
		// 3. Open the input file in binary mode with a standard ifstream
		ifstream bFile(mFileName, ios::out | ios::binary);
		/*int totalCount;
		bFile.seekg(0, bFile.end);
		totalCount = bFile.tellg();
		bFile.seekg(0, bFile.beg);
		char* fByte = new char[totalCount];

		bFile.read(fByte, totalCount);
		char* fHead = new char[257*4];*/

		// 4. Start the compression process.   (You can read the whole file into a buffer first if you want)
		//		For each character in the original file, write out the bit-code from the encoding table
		/*for (size_t i = 0; i < 257 * 4; i+=4)
		{
			memccpy((char*)&fHead[i], (char*)&mFrequencyTable[i / 4], 4);
		}*/
		
		for (size_t i = 0; i < mFrequencyTable[256]; i ++)
		{
			bStremFile << mEncodingTable[(char)bFile.get()];
		}

		// 5. Close the file streams when done
		bFile.close();
		bStremFile.Close();
		// 6. Clear the tree (and optional buffer)
		ClearTree();
	}

	// Decompress a huffman-compressed file
	//
	// In:	_outputFile		Where to write the uncompressed data to
	//
	// Note: The mFileName will be the compressed file
	void Decompress(const char* _outputFile) {
		// 1. Create a BitIStream and read the frequency table
		BitIStream bStreamFile(mFileName.c_str(), (char*)mFrequencyTable, sizeof(int) * 257);
		// 2. Create the leaf list and tree
		GenerateLeafList();
		GenerateTree();

		// 3. Create the stream for output (binary mode)
		ofstream oStreamFile(_outputFile, ios_base::binary);
		// 4. Create a bool to use for traversing down the list, and a char to store the character for writing
		bool check;
		char store;
		// 5. Create a node pointer for use in traversing the list (start it at the top)
		HuffNode* nodetrav = mRoot;
		// 6. Go through the compressed file one bit at a time, traversing through the tree
		//		When you get to a leaf node, write out the value, and go back to the root
		//	Note: Remember, there may be trailing 0's at the end of the file, so only loop the appropriate number of times
		for (size_t i = 0; i < mFrequencyTable[256]; i++)
		{
			//while (!bStreamFile.eof())
			while (nodetrav->right != nullptr && nodetrav->left != nullptr)
			{
				bStreamFile >> check;
				/*if (nodetrav != nullptr && nodetrav->left != nullptr)*/
				
					if (check == true)
					{
						nodetrav = nodetrav->right;
					}
					else
					{
						nodetrav = nodetrav->left;
					}
				

			//	if (!check)
			//	{
			//		if (nodetrav != nullptr && nodetrav->left == nullptr)
			//		{
			//			if (nodetrav->value == 13)
			//			{
			//				check = true;
			//			}
			//			else {
			//				if (check)
			//				{
			//					oStreamFile.write("\r", 1);
			//					check = false;
			//				}
			//				oStreamFile.write((char*)&nodetrav->value, 1);
			//			}
			//			nodetrav = this->mRoot;
			//		}

			//		nodetrav = nodetrav->left;
			//	}
			//	else
			//	{
			//		if (nodetrav != nullptr && nodetrav->right == nullptr)
			//		{
			//			if (nodetrav->value == 13)
			//			{
			//				check = true;
			//			}
			//			else
			//			{
			//				if (check)
			//				{
			//					oStreamFile.write("\r", 1);
			//					check = false;
			//				}
			//				oStreamFile.write((char*)&nodetrav->value, 1);
			//			}
			//			nodetrav = this->mRoot;
			//		}
			//		nodetrav = nodetrav->right;
			//	}
			}
			store=(char)nodetrav->value;
			oStreamFile << store;
			nodetrav = mRoot;
		}
		// 7. Close the streams
		bStreamFile.Close();
		oStreamFile.close();
		// 8. Clean up the dynamic memory by clearing the tree
		ClearTree();
	}
};




