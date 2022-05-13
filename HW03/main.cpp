/*###########################################################################################################
#  Authors : AMULYA EJJINA, MIHRIBAN GUNEYDAS,DEANGELO BROWN                                                                       
#  Mustangs ID     : M20306671, M20293151 ,M20299911                                                                            
#  Program Aim     : Implement and Compare the efficiency of a regular, non-balanced 
#                    binary search tree to a balanced binary search tree  
#  Balanced Tree used : AVL Tree                                
#  Short explanation of program : This program creates two trees 
#   1) A regular binary search tree,      
#   2) An AVL Tree and uses different parameters to compare and tries compare the efficiency of 
#   balanced over an unbalanced binary tree.                                                        
#  Topics used in this program :   Recursion,Nested loops                
###########################################################################################################*/


#include<iostream>
#include<stdio.h>
#include<time.h>
#include "BSTree.h"
#include "avltree.h"
#include<string>
#include<iomanip>
#define INITIAL_ARRAY_SIZE 1000
#define SIZE 10000

using namespace std;
//-----------------------  METHODS TO CREATE DATASETS  ------------------------

// Inserts random values within a specified range(10000 here) with ... 
// no restrictions on the order of the data inserted

int *  create_dataset1(int size)
{
  int num;
  int * arr =new int[size];
  for (int i = 0; i < size; i++)
	{
		num = rand() % 10000;
		arr[i]=num;
 
	}
  return arr;
}

// Inserts a root value that is the median of a specified range
// here, setting 5000 as root as range is 1-10,000

int*  create_dataset2(int size)
{
  int num;
  int * arr =new int[size];
  arr[0] = 5000;
  for (int i = 1; i < size; i++)
	{
		num = rand() % 10000;
		arr[i]=num;
	}
  
  return arr;
}

// Inserts a root value that is closer to one of a specified range
// here, setting 2500 as root as range is 1-10,000

int*  create_dataset3(int size)
{
  int num;
  int * arr =new int[size];
  arr[0] = 2500;
  for (int i = 1; i < size; i++)
	{
		num = rand() % 10000;
		arr[i]=num;
	}
  return arr;
}

//-----------------------  METHODS TO HELP DISPLAY ------------------------

void display_timings_in_tabular( int bInsertCounter,int bSearchCounter, int bheight, int aheight, int aInsertCounter,int aSearchCounter, string name)
{
    // The input arrays hold the values of runtime & counter of each sort for 20 iterations
    int n=0;
    float msum=0,isum=0,csum=0;
    int colWidth=20;
    cout << endl;
    cout << endl;
    
    // table header 
    cout << name << endl;
    cout << setw(10) << setw(colWidth) << setprecision(6) << "BST TREE" << setw(colWidth) << setprecision(6) << "AVL TREE" << setw(colWidth) << endl; 

    
    // filling table data with passed array elements
    cout << setprecision(0) << setw(8) << "HEIGHT " << setw(9)<< bheight<< setw(21)<< aheight  << endl;
    cout << endl;
    cout << setprecision(0) << setw(14) << "INSERT COUNTER " << bInsertCounter<<setw(21)<<aInsertCounter<< setw(colWidth) << endl;
    cout << endl;
    cout << setprecision(0) << setw(14) << "SEARCH COUNTER " << bSearchCounter<<setw(21)<<aSearchCounter<<endl;
    


}
void heading()
{
cout << "############################################################################################################"<<endl
<<"#  Authors : AMULYA EJJINA, MIHRIBAN GUNEYDAS,DEANGELO BROWN "<<endl
<<"#  Mustangs ID     : M20306671, M20293151, M20299911 			         "<<endl
<<"#  Course 	   : CMPS 5243 Algorithm Analysis,Spring 2022, Dr.JOHNSON   "<<endl
<<"#  Purpose	   : Implement and Compare the efficiency of a regular, non-balanced binary search tree "<<endl
<<"#  to a balanced binary search tree "<<endl

<<"############################################################################################################" << endl;
}

int main()
{
  heading();
  int num, num2=0;
  
//Initiliazed the height values for all trees
  int btree1_Height ,btree2_Height ,btree3_Height = 0;
  int avltree1_Height, avltree2_Height ,avltree3_Height = 0;

//Initiliazed the search counter and insert counter values for all bs trees    
  int avg_searchC_btree1=0 ,avg_searchC_btree2=0, avg_searchC_btree3 = 0;
  int avg_insertC_btree1=0 ,avg_insertC_btree2=0, avg_insertC_btree3 = 0;
    
//Initiliazed the search counter and insert counter values for all avl trees    
  int avg_searchC_avl1=0 ,avg_searchC_avl2=0 ,avg_searchC_avl3 = 0;
  int avg_insertC_avl1=0 ,avg_insertC_avl2=0 ,avg_insertC_avl3 = 0;
    

//************************************************************************
// 
//  Creating Three trees/tree instances foreach type of Tree, i.e BST & AVL
//
//************************************************************************

  BSTree btree1;
  BSTree btree2;
  BSTree btree3;
  AVLtree avltree1;
  AVLtree avltree2;
  AVLtree avltree3;

  // Make a call to the methods which generate random numbers
  int * dataset1 = create_dataset1(INITIAL_ARRAY_SIZE);
  int * dataset2 = create_dataset2(INITIAL_ARRAY_SIZE);
  int * dataset3 = create_dataset3(INITIAL_ARRAY_SIZE);

//************************************************************************
// 
// Inserting the generated 3 Datasets into the BST & AVL Trees
//
//************************************************************************
  for (int i = 0; i < INITIAL_ARRAY_SIZE; i++)
	{
        // B TREE INSERTS...
        btree1.insert(dataset1[i]);
        btree2.insert(dataset2[i]);
        btree3.insert(dataset3[i]);

        // AVL TREE INSERTS...
        avltree1.insertNode(dataset1[i]);
        avltree2.insertNode(dataset2[i]);
        avltree3.insertNode(dataset3[i]);
	}
	
//************************************************************************
// 
// Finding heights for each BST & AVL Trees
//
//************************************************************************
	btree1_Height = btree1.CalcH();
	btree2_Height = btree2.CalcH();
	btree3_Height = btree3.CalcH();
	avltree1_Height = avltree1.TreeHeight();
	avltree2_Height = avltree2.TreeHeight();
	avltree3_Height = avltree3.TreeHeight();
    
//************************************************************************
// 
// Finding for comparing the number of steps for insertion and search of random numbers
//
//************************************************************************ 
cout << "Comparing the efficiency of BST vs AVL Trees ..."<<endl;
for (int size =1000; size< SIZE; size=size+3000)
{
  avg_searchC_btree1=0 ,avg_searchC_btree2=0, avg_searchC_btree3 = 0;
  avg_insertC_btree1=0 ,avg_insertC_btree2=0, avg_insertC_btree3 = 0;
  avg_searchC_avl1=0 ,avg_searchC_avl2=0 ,avg_searchC_avl3 = 0;
  avg_insertC_avl1=0 ,avg_insertC_avl2=0 ,avg_insertC_avl3 = 0;
  cout << "---------------------------------------------------------------------"<<endl;
  for (int i = 0; i < size; i++)
	{
	      num = rand() % 1000000;
	      num2 = rand() % 1000000;

        // B TREE NEW INSERTS & SEARCHES ...
        avg_insertC_btree1 += btree1.insert(num);
        avg_insertC_btree2 += btree2.insert(num);
        avg_insertC_btree3 += btree3.insert(num);
       
        avg_searchC_btree1 += btree1.search(num2);
        avg_searchC_btree2 += btree2.search(num2);
        avg_searchC_btree3 += btree3.search(num2);

        // AVL TREE NEW INSERTS & SEARCHES ...
        avg_insertC_avl1 += avltree1.insertNode(num);
        avg_insertC_avl2 += avltree2.insertNode(num);
        avg_insertC_avl3 += avltree3.insertNode(num);

        avg_searchC_avl1 += avltree1.search(num2);
        avg_searchC_avl2 += avltree2.search(num2);
        avg_searchC_avl3 += avltree3.search(num2);


	}

  
  //Divided the counters to the size of the loop    
    avg_insertC_btree1/=size;
    avg_searchC_btree1/=size;
    avg_insertC_btree2/=size;
    avg_searchC_btree2/=size;
    avg_insertC_btree3/=size;
    avg_searchC_btree3/=size;
  
    avg_insertC_avl1/=size;
    avg_searchC_avl1/=size;
    avg_insertC_avl2/=size;
    avg_searchC_avl2/=size;
    avg_insertC_avl3/=size;
    avg_searchC_avl3/=size;


    btree1.GraphVizOut("mygraphb.dot");
    btree2.GraphVizOut("mygraphb1.dot");
    btree3.GraphVizOut("mygraphb2.dot");
    avltree1.GraphVizOut("mygrapha.dot");
    avltree2.GraphVizOut("mygrapha1.dot");
    avltree3.GraphVizOut("mygrapha2.dot");
    
//************************************************************************
// 
// Displaying the values
//
//************************************************************************   
    cout << "FOR DATASET SIZE - "<< size<< endl;
           display_timings_in_tabular(avg_insertC_btree1,avg_searchC_btree1,btree1_Height,avltree1_Height,avg_insertC_avl1,avg_searchC_avl1,"DATASET1 TABLE");
    display_timings_in_tabular(avg_insertC_btree2,avg_searchC_btree2,btree2_Height,avltree2_Height,avg_insertC_avl2,avg_searchC_avl2,"DATASET2 TABLE");
    display_timings_in_tabular(avg_insertC_btree3,avg_searchC_btree3,btree3_Height,avltree3_Height,avg_insertC_avl3,avg_searchC_avl3,"DATASET3 TABLE");

//************************************************************************
// 
// Showing overall average values for BST & AVL Trees
//
//************************************************************************ 
cout << endl;
     cout << "average search for bst  "<<(avg_searchC_btree1+avg_searchC_btree2+avg_searchC_btree3)/3<<endl;
     cout << "average insert for bst  "<<(avg_insertC_btree1+avg_insertC_btree2+avg_insertC_btree3)/3<<endl;
     cout << "average search for avl  "<<(avg_searchC_avl1+avg_searchC_avl2+avg_searchC_avl3)/3<<endl;
     cout << "average insert for avl  "<<(avg_insertC_avl1+avg_insertC_avl2+avg_insertC_avl3)/3<<endl;

}

}
