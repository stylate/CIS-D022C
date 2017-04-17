#ifndef _HEAP
#define _HEAP

class Heap {
     private:
        int* elements; // Pointer to dynamically allocated array
     public:
		Heap(int size); // Default constructor
        ~Heap(); // Destructor
		int reheapDown(int, int[], int, int&); // Heapify function
};

#endif