/* 
  * File:    mguneydas_CMPS5243_HW01.cpp
  * 
  * Author1:    Mihriban Guneydas (mguneydas0225@my.msutexas.edu) 
  * Date:       Spring 2022
  * Course:     CMPS 5243 Algorythim Analysis
  * References: https://www.geeksforgeeks.org/find-number-of-islands/
  * 
  * Summary of File: 
  * 
  *   This file contains code which finding number of islands of the file. 
  *   By doing that I used Depth First Search. I used DFS function as recursive.
  * 
  */ 

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#define ROW 20
#define COL 20

using namespace std;

int isSafe(string M[][COL], int row, int col,bool visited[][COL])
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL) && (M[row][col] != "0" && !visited[row][col]);
}

void DFS(string M[][COL], int row, int col,bool visited[][COL])
{
    static int rowNbr[] = { -1, 0, 0, 1};
    static int colNbr[] = { 0, -1, 1, 0};

    visited[row][col] = true;

    for (int k = 0; k < 4; ++k)
        if (isSafe(M, row + rowNbr[k], col + colNbr[k], visited))
            DFS(M, row + rowNbr[k], col + colNbr[k], visited);
}

int countIslands(string M[][COL])
{
    bool visited[ROW][COL];
    memset(visited, 0, sizeof(visited));

    int count = 0;
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            if (M[i][j] != "0" && !visited[i][j]) 
            {
                DFS(M, i, j, visited);
                ++count;
            }
    return count;
}

int main() 
{
  fstream myFile;
  myFile.open("blobtest.txt", ios::in);

  string arr[ROW][COL];

  if(myFile.is_open()){
    string line;
    int i = 0;
    while(getline(myFile, line))
    {
      int x = 0;
      for (int j = 0; j < line.length(); j++)
      {
        if (line[j] != ' ')
        {
          arr[i][x] = line[j];
          x++;
        }
      }
      i++;
    }
    cout << "Original world:"<<endl<<endl;

    for (int i = 0; i < ROW; i++)
    {
      for (int j = 0; j < COL; j++)
      {
        cout << arr[i][j] << " ";
      }
      cout << endl;
    }

  }
  
  cout <<endl<<endl<<"World with mutated blobs:"<<endl<<endl;
  
  for (int i = 0; i < 20; i++)
    {
      for (int j = 0; j < 20; j++)
      {
        if (arr[i][j] == "*")
        {
            arr[i][j] = '#';
        }  
        cout << arr[i][j] << " ";
      }
      cout << endl;
    }
    
  cout << endl << countIslands(arr) << " blobs were found." <<endl;

  return 0;
} 
