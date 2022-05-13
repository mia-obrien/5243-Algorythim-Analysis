/*  MIHRIBAN GUNEYDAS HW02 Of CMPS 5243
  * File:    mguneydas_CMPS5243_HW02.cpp
  * 
  * Author1:    Mihriban Guneydas (mguneydas0225@my.msutexas.edu) 
  * Date:       Spring 2022
  * Course:     CMPS 5243 Algorythim Analysis
  * References: https://www.programiz.com/dsa/counting-sort
  *             https://www.geeksforgeeks.org/merge-sort/
  *             https://www.geeksforgeeks.org/bubble-sort/
  * 
  * Summary of File: 
  * 
  *   In this assignment I used counting sort for O(n) complexity, merge sort for O(nlogn) complexity and lastly bubble sort for O(n^2) complexity. 
  *   The purpose of this assignment is to show and compare the time and number of iterations of each sorting algorithm.
  * 
  */ 

#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

//global value for merge sort
int mcounter=0;

// C++ program for Merge Sort
// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
int countSort(int array[], int size) {
    // The size of count must be at least the (max+1) but
    // we cannot assign declare it as int count(max+1) in C++ as
    // it does not support dynamic memory allocation.
    // So, its size is provided statically.
    int output[5000];
    int count[5000];
    int max = array[0];
    int counter = 0;
    // Find the largest element of the array
    for (int i = 1; i < size; i++) {
        if (array[i] > max)
            max = array[i];
        ++counter;
    }
    // Initialize count array with all zeros.
    for (int i = 0; i <= max; ++i) {
        count[i] = 0;
        ++counter;
    }
    // Store the count of each element
    for (int i = 0; i < size; i++) {
        count[array[i]]++;
        ++counter;
    }
    // Store the cummulative count of each array
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
        ++counter;
    }
    // Find the index of each element of the original array in count array, and
    // place the elements in output array
    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
        ++counter;
    }
    // Copy the sorted elements into original array
    for (int i = 0; i < size; i++) {
        array[i] = output[i];
        ++counter;
    }
    return counter;
}

void merge(int array[], int const left, int const mid, int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
    // Create temp arrays
    auto* leftArray = new int[subArrayOne],
        * rightArray = new int[subArrayTwo];
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
    {
        leftArray[i] = array[left + i];
        ++mcounter;
    }
    for (auto j = 0; j < subArrayTwo; j++)
    {
        rightArray[j] = array[mid + 1 + j];
        ++mcounter;
    }
    auto indexOfSubArrayOne = 0, // Initial index of first sub-array
        indexOfSubArrayTwo = 0; // Initial index of second sub-array
    int indexOfMergedArray = left; // Initial index of merged array
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
        ++mcounter;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
        ++mcounter;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
        ++mcounter;
    }
}
// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
    auto mid = begin + (end - begin) / 2;
    ++mcounter;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
    
}

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
int bubbleSort(int arr[], int n) 
{ 
    int i, j; 
    int counter = 0;
    for (i = 0; i < n-1; i++)     
      
    // Last i elements are already in place 
    for (j = 0; j < n-i-1; j++) 
        if (arr[j] > arr[j+1]){
            swap(&arr[j], &arr[j+1]); 
            ++counter;
        }
        
    return counter;
} 
  
  
// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size)
{
    for (auto i = 0; i < size; i++)
        cout << A[i] << " ";
}
// Driver code
int main()
{
    //I create the counter variable and time variable for each sort
    int countingCounter = 0;
    int mergeCounter = 0;
    int bubbleCounter = 0;
    double doneTime = 0;
    double doneTime2 = 0;
    double doneTime3 = 0;
    
    //I create the different arrays for each sort
    int arr[5000];  //original array
    int carr[5000]; //array for counting sort
    int marr[5000]; //array for merge sort
    int barr[5000]; //array for bubble sort
    
    for(int j=0;j<20;j++)//Running the code 20 times
    {
        for(int i=0;i<5000;i++)//Creating an array with size of 5000 
        {
            arr[i]=rand()%5000;  //Generate number between 0 to 5000
            carr[i]=arr[i];      //Copying the array for not loosing the unsorted array
            marr[i]=arr[i];
            barr[i]=arr[i];
        }
        
        //Calculating time for counting sort
        clock_t start = clock();
        countingCounter+=countSort(carr, 5000);
        clock_t finish = clock();
        doneTime += double(finish - start) / double(CLOCKS_PER_SEC / 1000);
        
        //Calculating time for merge sort
        clock_t start2 = clock();
        mergeSort(marr, 0, 5000 - 1);
        mergeCounter += mcounter;
        clock_t finish2 = clock();
        doneTime2 += double(finish2 - start2) / double(CLOCKS_PER_SEC / 1000);
        
        //Calculating time for bubble sort
        clock_t start3 = clock();
        bubbleCounter += bubbleSort(barr, 5000);
        clock_t finish3 = clock();
        doneTime3 += double(finish3 - start3) / double(CLOCKS_PER_SEC / 1000);

    }
    
    cout<<"MIHRIBAN GUNEYDAS HW02 Of CMPS 5243"<<endl<<endl;
    cout<<"File:       mguneydas_CMPS5243_HW02.cpp"<<endl;
    cout<<"Author1:    Mihriban Guneydas (mguneydas0225@my.msutexas.edu)"<<endl;
    cout<<"Date:       Spring 2022"<<endl;
    cout<<"Course:     CMPS 5243 Algorythim Analysis"<<endl;
    cout<<"References: https://www.programiz.com/dsa/counting-sort"<<endl;
    cout<<"            https://www.geeksforgeeks.org/merge-sort/"<<endl;
    cout<<"            https://www.geeksforgeeks.org/bubble-sort/"<<endl<<endl;
    cout<<"Summary of File: "<<endl;
    cout<<"In this assignment I used counting sort for O(n) complexity, merge sort for O(nlogn) complexity and lastly bubble sort for O(n^2) complexity."<<endl; 
    cout<<"The purpose of this assignment is to show and compare the time and number of iterations of each sorting algorithm."<<endl;
    
    //Dividing the time and counter by 20 for each sorting algorithms to getting average 
    cout <<endl<<"Counting Sort Time: "<<doneTime*1000.0/20 << " milliseconds" << endl;
    cout <<"Counting Sort Counter: "<< countingCounter/20<< endl;
    
    cout <<endl<<"Merge Sort Time: "<< doneTime2*1000.0/20 << " milliseconds" << endl;
    cout << "Merge Sort Counter: "<< mergeCounter/20<< endl;
   
    cout <<endl<< "Bubble Sort Time: "<<doneTime3*1000.0/20 << " milliseconds" << endl;
    cout <<"Bubble Sort Counter: "<<bubbleCounter/20<< endl;
    
    return 0;
}
