// BST.h - A binary search tree
#pragma once

// For InOrder method
#include "string.h"
using namespace std;

#if LAB_8
template<typename Type>
class BST {

	friend class TestSuite; // Giving access to test code

	struct Node {
		Type data;
		Node* left, * right;

		// Constructor
		//		Creates a leaf node
		//
		// In:	_data		The value to store in this node
		Node(const Type& _data) {
			this->data = _data;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	// Data members
	Node* mRoot;

public:

	// Default constructor
	//			Creates an empty tree
	BST() 
	{

		mRoot = nullptr;
		/*mRoot->left = nullptr;
		mRoot->right = nullptr;*/
		
		//data->left = nullptr;
		/*left=nullptr;
		right=nullptr;*/
		/*this->left = nullptr;
		this->right = nullptr;*/
		//this->mRoot = NULL;
	}

	// Destructor
	//			Clear all dynamic memory
	~BST() {
		Clear();
	}

	// Copy constructor
	//			Used to initialize one object to another
	//
	// In:	_copy		The object to copy from
	BST(const BST<Type>& _copy) {
		*this = _copy;
	}


	// Assignment operator
	//			Used to assign one object to another
	//
	// In:	_assign		The object to assign from
	//
	// Return:	The invoking object (by reference)
	//		This allows us to daisy-chain
	BST<Type>& operator=(const BST<Type>& _assign) {

		Clear();
		Copy(_assign.mRoot);
		return *this;
	}

private:

	// Optional recursive helper method for use with Rule of 3
	// 
	// In:	_curr		The current Node to copy
	//
	// NOTE:	Use pre-order traversal
	void Copy(const Node* _curr) {
		if (_curr==nullptr)
		{
			return;
		}
		Push(_curr->data);
		Copy(_curr->left);
		Copy(_curr->right);
	}

public:

	// Clears out the tree and readies it for re-use
	void Clear() {
		
		Clear(mRoot);
		/*delete mRoot->left;
		delete mRoot->right;*/
		mRoot= nullptr;
	}

private:

	// Optional recursive helper method for use with Clear
	// 
	// In:	_curr		The current Node to clear
	//
	// NOTE:	Use post-order traversal
	void Clear(Node* _curr) {
		
		if (_curr == nullptr)
		{
			return;
		}
		Clear(_curr->left);
		Clear(_curr->right);
		delete _curr;
		/*delete left;
		delete right;*/

	}

public:

	// Add a value into the tree
	//
	// In:	_val			The value to add
	void Push(const Type& _val) {
		
		//Node* nPush = new Node(_val);
		//if (mRoot == nullptr)
		//{
		//	
		//	//nPush->data = _val;
		//	mRoot = nPush;
		//}

		//else
		//{
		//	Push(_val, mRoot);
		//}

		//
		//Node* temp = nPush;
		//delete nPush;
		Push(_val, mRoot);
	}

private:

	// Optional recursive helper method for use with Push
	//
	// In:	_val		The value to add
	//		_curr		The current Node being looked at
	void Push(const Type& _val, Node* _curr) {
		if (mRoot == nullptr)
		{
			mRoot= new Node(_val);
		}
		else if (_curr->data > _val)
		{
			if (_curr->left != nullptr)
			{
				Push(_val, _curr->left);
			}
			else
			{
				//Node* nPushL = new Node(_val);
				_curr->left = new Node(_val);
			}
		}
		else
		{
			if (_curr->right != nullptr)
			{
				Push(_val, _curr->right);
			}
			else
			{
				//Node* nPushR = new Node(_val);
				_curr->right = new Node(_val);
			}
		}
	}

public:

	// Checks to see if a value is in the tree
	//
	// In:	_val		The value to search for
	//
	// Return:	True, if found
	bool Contains(const Type& _val) {

		if (mRoot == nullptr)
		{
			return false;
		}
		else if (mRoot->data < _val) 
		{
			return true; 
		}
		else if (mRoot->data == _val)
		{
			return true;
		}
		else
		{
			if (_val < mRoot->data)
			{
				return false; 
			}
		}
		return false;
	}
	////	while (mRoot != nullptr)
	////	{
	////		if (mRoot->data > _val)
	////		{
	////			//return mRoot->left.Contains(_val);
	////			mRoot = mRoot->left;
	////			//if (mRoot->data == _val)
	////			//{
	////			//	return true;
	////			//	//break;
	////			//}
	////		}
	////		else if (mRoot->data < _val)
	////		{
	////			//return mRoot->right.Contains(_val);
	////			mRoot = mRoot->right;
	////			//if (mRoot->data == _val)
	////			//{
	////			//	return true;
	////			//	//break;
	////			//}
	////		}
	////		else if (mRoot->data == _val)
	////		{
	////			return true;
	////			break;
	////		}
	////	}
	////	if (mRoot == nullptr)
	////	{
	////		return false;
	////	}
	////}
	//	
	//	//return true;
	////	if (mRoot->data < _val)
	////	{
	////		return true;
	////		//this.data = data;
	////		if (mRoot->left == nullptr)
	////		{
	////			return false;
	////		}
	////		else
	////		{
	////			return mRoot->left.Contains(_val);
	////		}
	////	}
	////	else
	////	{
	////		return false;
	////		//this.data = data;
	////		if (mRoot->right == nullptr)
	////		{
	////			return false;
	////		}
	////		else
	////		{
	////			return mRoot->right.Contains(_val);
	////		}
	////	}
	////}

	// Removes a value from tree (first instance only)
	//
	// In:	_val			The value to search for
	//
	// Return:	True, if a Node was removed
	// NOTE:	Keep in mind the three cases
	//			A) 2 children ("fix" tree)
	//			B) 0 children
	//			C) 1 child
	bool Remove(const Type& _val) {
		Node* child = mRoot;
		Node* parent = nullptr;

		while (child !=nullptr)
		{
			if (child->data > _val)
			{
				parent = child;
				child = child->left;
			}
			else if (child->data < _val)
			{
				parent = child;
				child = child->right;
			}
			else if (child->data == _val)
			{
				/*return true;*/
				break;
			}
		}

		if (child == nullptr)
		{
			return false;
		}
		else
		{
			//case 02
			if (child->left != nullptr && child->right != nullptr)
			{
				Node* endtree = child->right;
				while (endtree->left != nullptr)
				{
					parent = endtree;
					endtree = endtree->left;
				}
				child->data = endtree->data;
				child = endtree;
			}

			//case 00
			if (child->left == nullptr && child->right == nullptr)
			{
				if (child==mRoot)
				{
					mRoot = nullptr;
				}
				else if (parent->left == child)
				{
					parent->left = nullptr;
				}
				else if (parent->right == child)
				{
					parent->right = nullptr;
				}
				delete child;
			}

			//case 01
			else if (child->left != nullptr || child->right != nullptr)
			{
				if (child == mRoot)
				{
					if (child->left !=nullptr)
					{
						mRoot = child->left;
					}
					else if (child->right != nullptr)
					{
						mRoot = child->right;
					}
				}
				else if (parent->left == child)
				{
					if (child->right == nullptr)
					{
						parent->left = child->left;
					}
					else
					{
						parent->left = child->right;
					}
				}
				else if (parent->right == child)
				{
					if (child->right == nullptr)
					{
						parent->right = child->left;
					}
					else
					{
						parent->right = child->right;
					}
				}
				delete child;
			}
			
		}
		
		return true;
	}

	// Returns a space-delimited string of the tree in order
	/*
	 Example:
			 24
			/ \
		   10  48
			\   \
			12   50

	 Should return: "10 12 24 48 50"
	*/
	// NOTE:	Use to_string to convert an int to its string equivelent

	string InOrder() {
		string sD;
		InOrder(mRoot, sD);
		sD.pop_back();
		return sD;
	}

private:

	// Optional recursive helper method to help with InOrder
	//
	// In:	_curr		The current Node being looked at
	//		_str		The string to add to
	//
	// NOTE:	Use in-order traversal
	void InOrder(Node* _curr, string& _str) {
		
		if (_curr == nullptr)
		{
			return;
		}
	
		if (_curr->left != nullptr)
		{
			InOrder(_curr->left, _str);
		}
		if (_curr->right != nullptr) // if left is not empty InOrder right
		{
			_str.append(to_string(_curr->data) + " ");
			InOrder(_curr->right, _str);
		}
		if (_curr->right == nullptr) // if right is null add data to _str
		{
			_str.append(to_string(_curr->data) + " ");
		}
	}

};
#endif