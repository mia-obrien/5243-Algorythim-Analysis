// Implementation file for binary search tree class

#include "BSTree.h"
#include<iostream>
#include<fstream>

using namespace std;

int insertcounter=0;
int searchCounter=0;

BSTree::BSTree()
{
	root = nullptr;
}

BSTree::~BSTree()
{
	destroySubtree(root);
}

// destroySubtree recursively visits and deletes each node
// from the lowest level (leaves) up
void BSTree::destroySubtree(Node *& ptr)
{
	if (!ptr)
	{
		destroySubtree(ptr->left);
		destroySubtree(ptr->right);
		delete ptr;
		ptr = nullptr;
	}
}

int BSTree::insertNode(Node * &ptr, int x)
{
	// If ptr points to nullptr, the insertion position has been found
     insertcounter = insertcounter+1;

  
	if (ptr == nullptr)  
    ptr = new Node(x);

	// If ptr does not point to nullptr, decide whether to traverse
	// down the left subtree or right subtree by comparing value
	// to be inserted with current node.
	else if (x <= ptr->data)			// Node should be inserted in left subtree
		insertNode(ptr->left, x);
	else											// Node should be inserted in right subtree
		insertNode(ptr->right, x);
  return insertcounter;
}

// Public function that passes root to private helper function, insertNode
int BSTree::insert(int x)
{   
    insertcounter=0;
	  insertcounter=insertNode(root, x);
    return insertcounter;
}

void BSTree::inOrder(Node * ptr) const
{
	if (ptr)  // Equivalent to if(ptr != nullptr)
	{
		inOrder(ptr->left);
		cout << ptr->data << "   ";
		inOrder(ptr->right);
	}
}

void BSTree::inOrderPrint()
{
	inOrder(root);
	cout << endl;
}

void BSTree::preOrder(Node * ptr) const
{
	if (ptr)  // same as if (ptr != nullptr)
	{
		cout << ptr->data << "   ";
		preOrder(ptr->left);
		preOrder(ptr->right);
	}
}

void BSTree::preOrderPrint()
{
	preOrder(root);
	cout << endl;
}

void BSTree::postOrder(Node * ptr) const
{
	if (ptr)
	{
		postOrder(ptr->left);
		postOrder(ptr->right);
		cout << ptr->data << "   ";
	}
}

void BSTree::postOrderPrint()
{
	postOrder(root);
	cout << endl;
}

// Deletes a node using right child promotion
void BSTree::del(Node * &ptr)
{
	Node *delPtr = ptr;
	Node *attach;
	if (ptr->left == nullptr && ptr->right == nullptr) // no children
		ptr = nullptr;
	else if (ptr->right == nullptr)  // only left child
		ptr = ptr->left;
	else if (ptr->left == nullptr)  // only right child
		ptr = ptr->right;
	else  // two children
	{
		attach = ptr->right;
		while (attach->left != nullptr)
			attach = attach->left;
		attach->left = ptr->left;
		ptr = ptr->right;
	}
	delete delPtr;
}

// Recursive function that searches for node to be deleted and then
// passes the appropriate pointer to method del
void BSTree::deleteNode(Node * & ptr, int x)
{
	if (ptr)
	{
		if (ptr->data == x)
			del(ptr);
		else if (x < ptr->data)
			deleteNode(ptr->left, x);
		else
			deleteNode(ptr->right, x);
	}
}

// Public function that passes root to private helper function, deleteNode
void BSTree::deleteItem(int x)
{
	deleteNode(root, x);
}

void BSTree::deleteAll()
{
	destroySubtree(root);
}
int BSTree::searchItem(Node * ptr, int x)
{
    searchCounter = searchCounter+1;
	if (ptr)
	{
		if (x == ptr->data)
			return true;
		else if (x < ptr->data)
			return searchItem(ptr->left, x);
		else
			return searchItem(ptr->right, x);
	}
	return searchCounter;
}

int BSTree::search(int x)
{
    searchCounter = 0;
	searchItem(root, x);
	return searchCounter;
}
int BSTree::search_counter(int x)
{   
    
    return searchCounter;
}

void BSTree::GraphVizGetIds(Node *nodePtr, ofstream &VizOut){
	if (nodePtr){
		GraphVizGetIds(nodePtr->left, VizOut);
		VizOut << " node" << nodePtr->data << " [label=\"" << nodePtr->data << "\"];" << endl;
		GraphVizGetIds(nodePtr->right, VizOut);
	}
}


void BSTree::GraphVizMakeConnections(Node *nodePtr, ofstream &VizOut){
	if (nodePtr){
		if (nodePtr->left)
			VizOut << "  node" << nodePtr->data << "<-" << " node" << nodePtr->left->data << endl;
		if (nodePtr->right)
			VizOut << "  node" << nodePtr->data << "->" << " node" << nodePtr->right->data << endl;
		GraphVizMakeConnections(nodePtr->left, VizOut);
		GraphVizMakeConnections(nodePtr->right, VizOut);
	}
}

void BSTree::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename.c_str());
	VizOut << "digraph g { \n";
	GraphVizGetIds(root, VizOut);
	GraphVizMakeConnections(root, VizOut);
	VizOut << "} \n";
	VizOut.close();
}


int BSTree:: maxDepth(Node* node)
{
    if (node == NULL)
        return -1;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepth(node->left);
        int rDepth = maxDepth(node->right);
     
        /* use the larger one */
        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);
    }
}

int BSTree::CalcHeight(Node *&ptr) {
    if (ptr) {
      int left = 1 + CalcHeight(ptr->left);
      int right = 1 + CalcHeight(ptr->right);
      if (left > right) {
        // ptr->height=left;
        return left;
      } else {
        // ptr->height=right;
        return right;
      }
    } else {
      return 0;
    }
 }
  
int BSTree:: CalcH() {

    //int height = maxDepth(root);
    int height = CalcHeight(root);
    return height;
}
