// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

#ifndef BINNODE_H
#define BINNODE_H

// Binary tree node abstract class
template <typename E> class BinNode {
public:

	virtual ~BinNode() {} // Base destructor

	// Return the node's value
	virtual E& element() = 0;

	// Set the node's value
	virtual void setElement(const E&) = 0;

	// Return the node's left child
	virtual BinNode* left() const = 0;

	// Set the node's left child
	virtual void setLeft(BinNode*) = 0;

	// Return the node's right child
	virtual BinNode* right() const = 0;

	// Set the node's right child
	virtual void setRight(BinNode*) = 0;

	// Return the left child's thread status; COMMENTED OUT DUE TO ERRORS, RUNNING WELL WITHOUT THIS
	//virtual void getThreadStatusLeft() const = 0;

	// Return the right child's thread status; COMMENTED OUT DUE TO ERRORS, RUNNING WELL WITHOUT THIS
	//virtual void getThreadStatusRight() const = 0;

	// Return true if the node is a leaf, false otherwise
	virtual bool isLeaf() = 0;
};

#endif
