 #include <iostream>
#include <fstream>
#include <time.h>
#include "avltree.h"

//https://visualgo.net/en/bst

using namespace std;
int insertCounter = 0;
int sCounter = 0;
AVLtree::AVLtree(){
	root=NULL;
}

AVLtree::~AVLtree(){

}

//************************************************************************
// Method Name: insert
//
// Private 
//
// Purpose: Inserts a node into a binary tree
//
// Arguments: reference to the root, and a reference to the new node
//
// Returns: Nothing.
//*************************************************************************
int AVLtree::insert(TreeNode *&nodePtr, TreeNode *&newNode){

    insertCounter++;
	if (nodePtr == NULL){
		nodePtr = newNode;
	}else if (newNode->value <= nodePtr->value){
		newNode->parent = nodePtr;		
		insert(nodePtr->left,newNode);
		
	}else{
		newNode->parent = nodePtr;
		insert(nodePtr->right,newNode);
	}

  return insertCounter;
}

//************************************************************************
// Method Name: insertNode
//
// Public 
//
// Purpose: Creates a new node and assigns the passed in value to it. Subsequently
//          calls insert to actually travers the binary tree and link the node in
//          proper location. 
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
int AVLtree::insertNode(int num){

    insertCounter  = 0;
	TreeNode *newNode;

	newNode = new TreeNode;
	newNode->value = num;
	newNode->AvlValue = 0;
	newNode->left = newNode->right = NULL;
	newNode->parent = NULL;
	insertCounter  =insert(root,newNode);
	ComputeAvlValues(root);
	
	return insertCounter;
}

//************************************************************************
// Method Name: inorder,postorder,preorder (all the same)
//
// Public 
//
// Purpose: Traverses a binary tree 
//
// Arguments: integer to be placed in binary tree.
//
// Returns: Nothing.
//*************************************************************************
void AVLtree::inorder(TreeNode *nodePtr){
	if(nodePtr){
		inorder(nodePtr->left);
		cout<<nodePtr->value<<" "<<"("<<nodePtr->AvlValue<<") ";
		inorder(nodePtr->right);
	}
}

void AVLtree::postorder(TreeNode *nodePtr){
	if(nodePtr){
		inorder(nodePtr->left);
		inorder(nodePtr->right);
		cout<<nodePtr->value<<" "<<"("<<nodePtr->AvlValue<<") ";
	}
}

void AVLtree::preorder(TreeNode *nodePtr){
	if(nodePtr){
		cout<<nodePtr->value<<" "<<"("<<nodePtr->AvlValue<<") ";
		inorder(nodePtr->left);
		inorder(nodePtr->right);
	}
}

//************************************************************************
// Method Name: searchNode
//
// Public 
//
// Purpose: Traverses a binary tree looking for a key value
//
// Arguments: integer to look for
//
// Returns: true if found, false otherwise 
//*************************************************************************
int AVLtree::SearchNode(int num){
	TreeNode *nodePtr = root;

	while (nodePtr){
    sCounter++;
		if(nodePtr->value==num)
			return true;
		else if (num < nodePtr->value)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}
	return sCounter;
}

int AVLtree::search(int num){
    sCounter = 0;
	  sCounter = SearchNode(num);
  
	  return sCounter;
}

//************************************************************************
// Method Name: deleteNode
//
// Private 
//
// Purpose: Traverses a binary tree looking for a key value to mark for 
//          deletion (could be merged with searchNode).
//
// Arguments: key to delete, nodePtr of the start of the tree (root , subroot, etc.)
//
// Returns: void 
//*************************************************************************
void AVLtree::deleteNode(int num,TreeNode *&nodePtr){
	if(nodePtr){
		if(num<nodePtr->value)
			deleteNode(num,nodePtr->left);
		else if (num > nodePtr->value)
			deleteNode(num,nodePtr->right);
		else if(nodePtr->value == num)
			makeDeletion(nodePtr);
	}else{
		cout<<"Value does not exist!"<<endl;
	}
}

//************************************************************************
// Method Name: makeDeletion
//
// Private 
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of node to be deleted
//
// Returns: void 
//*************************************************************************
void AVLtree::makeDeletion(TreeNode *&nodePtr){
	TreeNode *tempNodePtr;

	if(nodePtr ==NULL)
		cout<<"Cannot delete empty node.\n";
	else if (nodePtr->right==NULL){

		tempNodePtr = nodePtr;
		nodePtr = nodePtr->left;
		delete tempNodePtr;

	}else if (nodePtr->left==NULL){

		tempNodePtr = nodePtr;
		nodePtr = nodePtr->right;
		delete tempNodePtr;

	}else{
		tempNodePtr = nodePtr->right;
		while(tempNodePtr->left)
			tempNodePtr = tempNodePtr->left;
		tempNodePtr->left = nodePtr->left;
		tempNodePtr = nodePtr;
		nodePtr=nodePtr->right;
		delete tempNodePtr;
	}
	ComputeAvlValues(root);
}

//************************************************************************
// Method Name: Height
//
// Private 
//
// Purpose: Actually removes a node from a tree by pointer manipulation and
//          frees the memory
//
// Arguments: address of the root of the tree (or subtree)
//
// Returns: void 
//*************************************************************************
int AVLtree::Height(TreeNode *nodePtr){
	int left_height=0;
	int right_height=0;
	if(nodePtr==NULL)
		return 0;
	else{
		left_height = Height(nodePtr->left);
		right_height = Height(nodePtr->right);
	}
	if(left_height>right_height)
		return 1+left_height;
	else
		return 1+right_height;
}

//************************************************************************
// Method Name: TreeHeight
//
// Public 
//
// Purpose: Public method to call the private height method
//
// Arguments: none
//
// Returns: void 
//*************************************************************************
int AVLtree::TreeHeight(){
	return Height(root);
}

//************************************************************************
// Method Name: AvlValue
//
// Private 
//
// Purpose: Private method to calculate the avl value of a node.
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
int AVLtree::AvlValue(TreeNode *nodePtr)
{
	return Height(nodePtr->right)-Height(nodePtr->left);
}

//************************************************************************
// Method Name: ComputeAvlValues
//
// Private 
//
// Purpose: Private method to calculate the avl values of the entire tree.
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
void AVLtree::ComputeAvlValues(TreeNode *&nodePtr)
{
	if(nodePtr){
		ComputeAvlValues(nodePtr->left);
		ComputeAvlValues(nodePtr->right);
		nodePtr->AvlValue=AvlValue(nodePtr);
		if(nodePtr->AvlValue > 1){
			RotateLeft(nodePtr);
		}else if(nodePtr->AvlValue < -1){
			RotateRight(nodePtr);
		}
	}
}

//************************************************************************
// Method Name: RotateLeft 
//
// Private 
//
// Purpose: Private method to perform a left rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
void AVLtree::RotateLeft(TreeNode *&SubRoot)
{


	if(LeftHeavy(SubRoot->right)){
		RotateRight(SubRoot->right);
	}

	TreeNode *Temp;

	Temp = SubRoot->right;
	SubRoot->right = Temp->left;
	Temp->left = SubRoot;
	SubRoot = Temp;

	ComputeAvlValues(SubRoot);
}

//************************************************************************
// Method Name: RotateLeft 
//
// Private 
//
// Purpose: Private method to perform a right rotation from a given position in a tree
//
// Arguments: address of a node
//
// Returns: void 
//*************************************************************************
void AVLtree::RotateRight(TreeNode *&SubRoot)
{
	if(RightHeavy(SubRoot->left)){
		RotateLeft(SubRoot->left);
	}

	TreeNode *Temp;

	Temp = SubRoot->left;
	SubRoot->left = Temp->right;
	Temp->right = SubRoot;
	SubRoot = Temp;

	ComputeAvlValues(SubRoot);
}

//************************************************************************
// Method to help create GraphViz code so the expression tree can 
// be visualized. This method prints out all the unique node id's
// by traversing the tree.
// Recivies a node pointer to root and performs a simple recursive 
// tree traversal.
//************************************************************************
void AVLtree::GraphVizGetIds(TreeNode *nodePtr,ofstream &VizOut){
	static int NullCount=0;
	if(nodePtr){
		VizOut<<"node_"<<nodePtr->value
			  <<"[label=\""<<nodePtr->value<<"\\n"
			  <<"Avl:"<<nodePtr->AvlValue<<"\\n"
			  //<<"Add:"<<nodePtr<<"\\n"
			  //<<"Par:"<<nodePtr->parent<<"\\n"
			  //<<"Rt:"<<nodePtr->right<<"\\n"
			  //<<"Lt:"<<nodePtr->left<<"\\n"
			  <<"\"]"<<endl;
		// if(!nodePtr->left){
		// 	NullCount++;
		// 	VizOut<<"nnode"<<NullCount<<"[label=\"X\",shape=point,width=.15]"<<endl;
		// }
    GraphVizGetIds(nodePtr->left,VizOut);
		GraphVizGetIds(nodePtr->right,VizOut);
		// if(!nodePtr->right){
		// 	NullCount++;
		// 	VizOut<<"nnode"<<NullCount<<"[label=\"X\",shape=point,width=.15]"<<endl;
		// }
	}
}

//************************************************************************
// This method is partnered with the above method, but on this pass it 
// writes out the actual data from each node.
// Don't worry about what this method and the above method do, just
// use the output as your told:)
//************************************************************************
void AVLtree::GraphVizMakeConnections(TreeNode *nodePtr,ofstream &VizOut){
	static int NullCount=0;
	if(nodePtr){
		
		if(nodePtr->left)
			VizOut<<"node_"<<nodePtr->value<<"->"<<"node_"<<nodePtr->left->value<<endl;
		else{
			// NullCount++;
			// VizOut<<"node_"<<nodePtr->value<<"->"<<"nnode"<<NullCount<<endl;
		}
			
		if(nodePtr->right)
			VizOut<<"node_"<<nodePtr->value<<"->"<<"node_"<<nodePtr->right->value<<endl;
		else{
			// NullCount++;
			// VizOut<<"node_"<<nodePtr->value<<"->"<<"nnode"<<NullCount<<endl;
		}
    GraphVizMakeConnections(nodePtr->left,VizOut);
		GraphVizMakeConnections(nodePtr->right,VizOut);

	}
}

//************************************************************************
// Recieves a filename to place the GraphViz data into.
// It then calls the above two graphviz methods to create a data file
// that can be used to visualize your expression tree.
//************************************************************************
void AVLtree::GraphVizOut(string filename)
{
	ofstream VizOut;
	VizOut.open(filename);
	GraphVizGetIds(root,VizOut);
	GraphVizMakeConnections(root,VizOut);
	VizOut.close();

}

//************************************************************************
// Method Name: DoDumpTree 
//
// Private 
//
// Purpose: Private method to show the basic pointer structure of the tree. 
//          Initially written to help with debugging.
//
// Arguments: address of a node
//
// Returns: void 
// Outputs: tree information
//*************************************************************************
void AVLtree::DoDumpTree(TreeNode *nodePtr)
{
	if(nodePtr){
		cout<<"Add:    "<<nodePtr<<"\n"
			<<"Parent->"<<nodePtr->parent<<"\n"
			<<"Val:    "<<nodePtr->value<<"\n"
			<<"Avl:    "<<nodePtr->AvlValue<<"\n"
			<<"Left->  "<<nodePtr->left<<"\n"
			<<"Right-> "<<nodePtr->right<<"\n\n";

		DoDumpTree(nodePtr->left);
		DoDumpTree(nodePtr->right);
	}
}

//************************************************************************
// Method Name: LeftHeavy,RightHeavy 
//
// Private 
//
// Purpose: Compares the subtrees of a node to see which is taller
//
// Arguments: address of a node
//
// Returns: true if (left/right) heavy 
//
//*************************************************************************
bool AVLtree::LeftHeavy(TreeNode *nodePtr)
{
	return Height(nodePtr->left)>Height(nodePtr->right);
}

bool AVLtree::RightHeavy(TreeNode *nodePtr)
{
	return Height(nodePtr->right)>Height(nodePtr->left);

}
