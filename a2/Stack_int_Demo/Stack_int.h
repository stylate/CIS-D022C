/**~*~*
   Specification file for the Stack_int class
            - a Stack of integers
*~**/
#ifndef INT_STACK_H
#define INT_STACK_H
#include <iostream>
using namespace std;

class Stack_int
{
private:
   // Structure for the stack nodes
   struct StackNode
   {
      int value;        // Value in the node
      StackNode *next;  // Pointer to next node
   };

   StackNode *top;     // Pointer to the stack top
   int count;

public:
   //Constructor
   Stack_int(){top = NULL; count = 0;}

   // Destructor
   ~Stack_int();

   // Stack operations
   bool push(int);
   bool pop(int &);
   bool isEmpty();
   // getCount()
   // getTop()
};
#endif
