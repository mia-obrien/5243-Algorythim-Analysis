#include <iostream>
#include <time.h>
#include <string>


using namespace std;

struct TreeNode{
	int value;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	int AvlValue;
};

class AVLtree{

private:
	TreeNode *root;
	bool RightHeavy(TreeNode *nodePtr);
	bool LeftHeavy(TreeNode *nodePtr);
	int insert(TreeNode *&, TreeNode *&);
	void inorder(TreeNode *nodePtr);
	void preorder(TreeNode *nodePtr);
	void postorder(TreeNode *nodePtr);
	void deleteNode(int ,TreeNode *&);
	void makeDeletion(TreeNode *&nodePtr);
	int  Height(TreeNode *nodePtr);
	void ComputeAvlValues(TreeNode *&nodePtr);
	void RotateLeft(TreeNode *&nodePtr);
	void RotateRight(TreeNode *&nodePtr);
	int  AvlValue(TreeNode *nodePtr);

public:
	AVLtree();
	~AVLtree();
	void DoDumpTree(TreeNode *nodePtr);
	void DumpTree(){cout<<"---------------------------------"<<endl;
	                cout<<"Root:   "<<root<<"\n";
					DoDumpTree(root);
	};
	int insertNode(int);
	void ShowInorder(){inorder(root);};
	void ShowPreorder(){preorder(root);};
	void ShowPostorder(){postorder(root);};
	int SearchNode(int);
	int search(int);
	void remove(int num){deleteNode(num,root);};
	int  TreeHeight();
    void GraphVizGetIds(TreeNode *nodePtr,ofstream &VizOut);
	void GraphVizMakeConnections(TreeNode *nodePtr,ofstream &VizOut);
	void GraphVizOut(string filename);
};
