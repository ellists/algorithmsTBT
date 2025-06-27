#include "BST.h"
#include <iostream>



int main() {

cout << "<Tyler Ellis ----- CSIS 215>\n";


//create tree object
BST<int, std::string> myTree;

//call insert() to insert all values from assignment instructions in the same order
//to create the threaded binary search tree structure.

myTree.insert(77, "seventy-seven");
myTree.insert(70, "seventy");
myTree.insert(75, "seventy-five");
myTree.insert(66, "sixty-six");
myTree.insert(79, "seventy-nine");
myTree.insert(68, "sixty-eight");
myTree.insert(67, "sixty-seven");
myTree.insert(69, "sixty-nine");
myTree.insert(90, "ninety");
myTree.insert(85, "eighty-five");
myTree.insert(83, "eighty-three");
myTree.insert(87, "eighty-seven");
myTree.insert(65, "sixty-five");

//show the tree size to console
cout << "\nMy BST tree size is: " << myTree.size() << endl << endl;

//header for BST console output
cout << "My tree's structure after all insertions is:\n\n";
//call the printhelp() method
myTree.print();

//header for BST inorder traversal
cout << "\n\nBeginning inorder traversal...\n\n";

//call the printInoder() method
myTree.printInorder();

//header for BST reverse inorder traversal
cout << "\n\nBeginning reverse inorder traversal...\n\n";


//call the printReverse() method
myTree.printReverse();

return 0;
}