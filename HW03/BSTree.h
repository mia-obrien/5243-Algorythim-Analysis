// Header file for binary search tree class

#pragma once
#include<fstream>
#include<iostream>

using namespace std;

// A binary search tree is a binary tree with the additional property
// that at any node, all values in the left subtree are less than or equal 
// to the node and all nodes in the right subtree are greater than the node.

class BSTree
{
private:
	struct Node
	{
		int data;
		Node *left, *right;
    Node(int x){
      data = x;
      left = right = nullptr;
  } 
	};
	Node *root;
	
	// Recursive private function to insert a value into the tree
	int insertNode(Node *&ptr, int x);

	// Recursive private function to print an in order listing of nodes in tree
	void inOrder(Node * ptr) const;

	// Recursive private function to print a pre-order listing of nodes in tree
	void preOrder(Node * ptr) const;

	// Recursive private function to print a post-order listing of nodes in tree
	void postOrder(Node * ptr) const;

	// Pivate function to delete a node from tree that is pointed to by the 
	// reference pointer ptr
	void del(Node * &ptr);

	// Recursive private function to delete node containing specific value, x
	void deleteNode(Node * & ptr, int x);

	// Recursive private function to delete all nodes in the tree
	void destroySubtree(Node *& ptr);

	int searchItem(Node * ptr, int x);

	// Credit to:  Terry Griffin
	// Creates GraphViz code so the tree can be visualized.  Prints
	// unique node id's by traversing the tree.
	void GraphVizGetIds(Node *nodePtr, ofstream &VizOut);

	// Credit to:  Terry Griffin
	// Partnered with the above method, but on this pass it 
	// writes out the actual data from each node.
	void GraphVizMakeConnections(Node *nodePtr, ofstream &VizOut);

public:
	// Constructor
	BSTree();

	// Destructor - deallocates all memory by calling destroySubtree
	~BSTree();

	// Public function to insert item x into the tree; calls insertNode
	int insert(int x);

	// Public function to delete item x from the tree; calls deleteNode
	void deleteItem(int x);

	// Public function to delete all items from the tree
	void deleteAll();

	// Public function to print all nodes in order; calls inOrder
	void inOrderPrint();

	// Public function to print all nodes pre-order; calls preOrder
	void preOrderPrint();

	// Public function to print all nodes post order; calls postOrder
	void postOrderPrint();

	// Public function to search for an item in the tree
	int search(int x);

    int search_counter(int x);
	// Credit to:  Terry Griffin
	// Receives a filename and stores a GraphViz readable file;
	// calls 	GraphVizGetIds and GraphVizMakeConnections
	void GraphVizOut(string filename);

  int maxDepth(Node* node);
  int CalcHeight(Node *&ptr);
  int CalcH();
};
