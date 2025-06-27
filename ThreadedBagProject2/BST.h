// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
	BSTNode<Key, E>* root; // Root of the BST

	int nodecount; // Number of nodes in the BST
	// Private "helper" functions
	void clearhelp(BSTNode<Key, E>*);
	BSTNode<Key, E>* inserthelp(BSTNode<Key, E>*, const Key&, const E&);
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
	BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
	E* findhelp(BSTNode<Key, E>*, const Key&) const;
	void printhelp(BSTNode<Key, E>*, int) const;
	void vist(BSTNode<Key, E>*) const;

public:
	BST() { root = NULL; nodecount = 0; } // Constructor

	//Note from Prof Sipantzi -- I've commented out the destructor
	//since you would have to change clearhelp() to make it work with
	//doubly-threaded trees and that is not part of the assignment.
	//~BST() { clearhelp(root); } // Destructor

	void clear() // Reinitialize tree
	{
		clearhelp(root); root = NULL; nodecount = 0;
	}

	// Insert a record into the tree.
	// k Key value of the record.
	// e The record to insert.
	void insert(const Key& k, const E& e) {
		root = inserthelp(root, k, e);
		nodecount++;
	}

	// Remove a record from the tree.
	// k Key value of record to remove.
	// Return: The record removed, or NULL if there is none.
	E* remove(const Key& k) {
		E* temp = findhelp(root, k); // First find it
		if (temp != NULL) {
			root = removehelp(root, k);
			nodecount--;
		}
		return temp;
	}
	// Remove and return the root node from the dictionary.
	// Return: The record removed, null if tree is empty.
	E* removeAny() { // Delete min value
		if (root != NULL) {
			E* temp = new E;
			*temp = root->element();
			root = removehelp(root, root->key());
			nodecount--;
			return temp;
		}
		else return NULL;
	}

	// Return Record with key value k, NULL if none exist.
	// k: The key value to find. */
	// Return some record matching "k".
	// Return true if such exists, false otherwise. If
	// multiple records match "k", return an arbitrary one.
	E* find(const Key& k) const { return findhelp(root, k); }

	// Return the number of records in the dictionary.
	int size() { return nodecount; }

	void print() const { // Print the contents of the BST
		if (root == NULL) cout << "The BST is empty.\n";
		else printhelp(root, 0);
	}

	//prints an in-order traversal of the BST to the console
	//Postcondition: the BST keys are read and the value is displayed to the console
	//, following the concept of an inorder traversal.
	void printInorder() {

		BSTNode<Key, E>* currentNode = root;

		//iterate to find the leftmost child
		while (currentNode->getThread_l() == false)
			currentNode = currentNode->left();

		//as long as our current node isn't empty, follow the right thread via successorFind
		while (currentNode != NULL) {
			cout << currentNode->element() << endl;
			currentNode = successorFind(currentNode);
		}
	}

	//helper function to determine where to go next in the inorder traversal
	//Postcondition: the destination node of the traversal-in-progress is returned
	BSTNode<Key, E>* successorFind(BSTNode<Key, E>* currentNode) {

		if (currentNode->getThread_r() == true) {
			return currentNode->right();
		}
		//if getthread right is false, that child node is a pointer to successor
		currentNode = currentNode->right();
		while (currentNode->getThread_l() == false) {
			currentNode = currentNode->left();
		}
		return currentNode;
	}

	//print reverse function, similar to the print inorder function logic.
	//Postcondition: the left threads are read and the BST keys are read, printing the
	//values to the console in a REVERSE inorder traversal concept.
	void printReverse() {

		//start from the right child
		BSTNode<Key, E>* currentNode = root;

		//opposite of inorder, go to the rightmost node to begin reverse print
		while (currentNode->getThread_r() == false) {
			currentNode = currentNode->right();
		}
		//follow left threads via predecessorFind
		while (currentNode != NULL) {
			cout << currentNode->element() << endl;
			currentNode = predecessorFind(currentNode);
		}
	}

	//same concept as successorFind, but to follow left threads instead of right.
	//Postcondition: the destination node is returned for the reverse inorder traversal.
	BSTNode<Key, E>* predecessorFind(BSTNode<Key, E>* currentNode) {

		if (currentNode->getThread_l() == true) {
			return currentNode->left();
		}
		currentNode = currentNode->left();
		while (currentNode->getThread_r() == false) {
			currentNode = currentNode->right();
		}
		return currentNode;
	}

};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
	cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::inserthelp(BSTNode<Key, E>* root, const Key& k, const E& it) {
	if (root == NULL) // Empty tree: create node
		return new BSTNode<Key, E>(k, it, root, root);
	if (k < root->key()) {
		if (root->getThread_l() == true){  //if left child is a thread

			root->setLeft(new BSTNode<Key, E>(k, it, root->left(), root)); //value is pushed to this node
			root->setThread_l(false); //node is no longer a thread, so we set to false.
		}
		else root->setLeft(inserthelp(root->left(), k, it)); //continue through the tree to find the threadded pointer

	}
	else {
		if (root->getThread_r() == true){

			root->setRight(new BSTNode<Key, E>(k, it, root, root->right())); //same as above
			root->setThread_r(false); //set thread false
		}
		else root->setRight(inserthelp(root->right(), k, it)); //continue through the tree
	}
	return root; // Return tree with node inserted
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL)
		return rt;
	else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL) // Found min
		return rt->right();
	else { // Continue left
		rt->setLeft(deletemin(rt->left()));
		return rt;
	}
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
	if (rt == NULL) return NULL; // k is not in tree
	else if (k < rt->key())
		rt->setLeft(removehelp(rt->left(), k));
	else if (k > rt->key())
		rt->setRight(removehelp(rt->right(), k));
	else { // Found: remove it
		BSTNode<Key, E>* temp = rt;
		if (rt->left() == NULL) { // Only a right child
			rt = rt->right(); // so point to right
			delete temp;
		}
		else if (rt->right() == NULL) { // Only a left child
			rt = rt->left(); // so point to left
			delete temp;
		}
		else { // Both children are non-empty
			BSTNode<Key, E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root,
	const Key& k) const {
	if (root == NULL) return NULL; // Empty tree
	if (k < root->key())
		return findhelp(root->left(), k); // Check left
	else if (k > root->key())
		return findhelp(root->right(), k); // Check right
	else {
		E* temp = new E;
		*temp = root->element();
		return temp; // Found it
	}
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::
printhelp(BSTNode<Key, E>* root, int level) const {
	if (root == NULL) return; // Empty tree

	if (root->getThread_l() == false) {
		printhelp(root->left(), level + 1); // iterate through left subtree(s)
	}

	for (int i = 0; i < level; i++) { // Indent to level
		cout << " ";
	}

	cout << root->key() << "\n"; // Print statement

	if (root->getThread_r() == false) {
		printhelp(root->right(), level + 1); // iterate though right subtree(s)
	}
}

#endif