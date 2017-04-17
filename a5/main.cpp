#include "Heap.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*
1. Create arrays of random numbers – 10
2. Selection Sort – 10
3. Heap Sort – 20
4. Heap class (ADT – for Extra Credit) – 25
5. Statistics (data comparisons and moves) – 10
6. Report – 10
7. main(), and other functions – 10
8. Self assessment – 5
// Did you write comments for the new functions? Yes, I wrote comments for the new functions.
// Did you completely test the program? I completely tested the program with multiple test cases with different array sizes.
// Did you save the updated output at the end of this source file as a comment? I saved an updated output inside "report.txt".
//
// Student Score: 97 - The assignment is being turned in 1 day late.
						Output format could have been potentially improved for more clarity (regarding the display of the actual array when ARRAY_SIZE <= 100).
//
// Instructor Score:
*/

int menu(int&);
void display(int[], int&);
void stat(int&, int&, string&, int&);
void randomNumbers(int[], int&);
void copyArray(int[], int[], int&);
string selectionSort(int[], int&, int&, int&);
string heapSort(Heap*, int[], int&, int&, int&);

int menu(int& size) {
	cout << "Enter your desired array size below. If -1 is entered, then the entire program will close.\n";
	cin >> size;
	return size;
}

int main () {
	int arraySize = 0; // default
	int* numbers;
	int* numbers2;
	string key;
	Heap* heapNum = new Heap(arraySize);

	while (arraySize != -1) {
		int selectComp = 0, heapComp = 0;
		int selectMove = 0, heapMove = 0;
		menu(arraySize);
		if (arraySize == -1) break;
		numbers = new int[arraySize];
		numbers2 = new int[arraySize];

		randomNumbers(numbers, arraySize);
		copyArray(numbers, numbers2, arraySize);
		display(numbers, arraySize); // before sort
		key = selectionSort(numbers, selectComp, selectMove, arraySize);
		display(numbers, arraySize); // after sort
		stat(selectComp, selectMove, key, arraySize);

		display(numbers2, arraySize);
		key = heapSort(heapNum, numbers2, heapComp, heapMove, arraySize);
		display(numbers2, arraySize); // after sort
		stat(heapComp, heapMove, key, arraySize);
		delete [] numbers;
		delete [] numbers2;
	}
}



//-------------------------------
// Displays the array's contents.
//-------------------------------
void display(int numbers[], int& size) {
	if (size <= 100) {
		cout << "=============" << endl;
		cout << "Array output: " << endl << endl;
		for (int i = 0; i < size; i++)
			cout << numbers[i] << endl;
		cout << "=============" << endl << endl;
	}
	// system("PAUSE");
}
//---------------------------------------------------
// Displays the amount of data comparisons and moves.
//---------------------------------------------------
void stat(int& compare, int& move, string& key, int& size) {
	if (key == "s") key = "Selection Sort";
	else if (key == "h") key = "Heap Sort";
	cout << "\n-----------" << key << " -----------\n";
	cout << "\nArray size: " << size << endl;
	cout << "Number of comparisons: " << compare << endl;
	cout << "Number of moves: " << move << endl << endl;
}


//-------------------------------------------------------
// Creates an array of random numbers from -99 to 99.
//-------------------------------------------------------
void randomNumbers(int array[], int& size) {
	for (int i = 0; i < size; i++) {
		array[i] = (rand() % 199) - 99;
	}
}



//------------------------------------------------------------
// Standard selection sort algorithm with modifications 
// resulting in a counter for the # of comparisons and moves.
//------------------------------------------------------------
string selectionSort(int arr[], int& compare, int& move, int& size)
{
	int index;
	int temp;
	for (int i = 0; i < size - 1; i++)
	{
		index = i;
		for (int j = i + 1; j < size; j++)
		{
			compare++;
			if (arr[j] < arr[index])
			{
				index = j;
			}
		}
		if (index != i)
		{
			// swapping....
			temp = arr[i];
			arr[i] = arr[index];
			arr[index] = temp;
			move++;
		}
	}
	return "s";
}

//----------------------------
// Copys array 1 into array 2.
//----------------------------
void copyArray(int original[], int copy[], int& size) {
	for (int i = 0; i < size; i++) copy[i] = original[i];
}


//-------------------------------------------------------
// Floyd's heap-building algorithm.
// This builds a heap and performs a max-heap operation, 
// then it gets sorted, with modifications resulting in
// a counter for the # of comparisons and moves.
//-------------------------------------------------------
string heapSort(Heap* heap, int arr[], int& compare, int& move, int& size) {
	int temp;
	for (int i = size / 2 - 1; i >= 0; i--) {
		heap->reheapDown(i, arr, size, compare);
	}
	for (int i = size - 1; i >= 0; i--) {
		// swapping
		temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		heap->reheapDown(0, arr, i, compare); // heapify the reduced heap
		move++;
	}
	return "h";
}