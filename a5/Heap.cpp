
#include "Heap.h"
#include <iostream>
using namespace std;

//---------------------------------------
// Default constructor
//---------------------------------------
Heap::Heap(int size) {
    // Create heap of given size
	elements = new int[size];
}

//--------------------------------------------
// Destructor - deletes the array from memory.
//--------------------------------------------
Heap::~Heap() {
	delete [] elements;
}


//----------------------------------------------------------------------
// Swaps the heap's root with either the left or right child.
// Also has a comparison counter for every time this function is called.
//----------------------------------------------------------------------
int Heap::reheapDown(int index, int arr[], int size, int& compare) { // reheaps down
	int temp;
	int max = index;
	int left = 2 * index + 1; // index of root's left
	int right = 2 * index + 2; // index of root's right

	compare++;
	if (left < size && arr[left] > arr[max]) max = left; // if root has no right child, then left has max key
	if (right < size && arr[right] > arr[max]) max = right; // if root has no left child, then right has max key
	if (max != index) {
		// swapping...
		temp = arr[index];
		arr[index] = arr[max];
		arr[max] = temp;
		reheapDown(max, arr, size, compare); // recursive call until reheap is complete.
	}
	return compare;
}