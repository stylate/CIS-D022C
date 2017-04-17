/**~*~*
   Implementation file for the Stack_int class
            - a Stack of integers
*~**/

#include "Stack_int.h"
/**~*~*
   Destructor
*~**/
Stack_int::~Stack_int()
{
   StackNode *currNode, *nextNode;

   // Position nodePtr at the top of the stack.
   currNode = top;

   // Traverse the list deleting each node.
   while (currNode) //while (currNode != NULL)
   {
      nextNode = currNode->next;
      delete currNode;
      currNode = nextNode;
   }
}

/**~*~*
  Member function push pushes the argument onto
  the stack.
*~**/
bool Stack_int::push(int item)
{
   StackNode *newNode; // Pointer to a new node

   // Allocate a new node and store num there.
   newNode = new StackNode;
   if (!newNode)
       return false;
   newNode->value = item;

   // Update links and counter
   newNode->next = top;
   top = newNode;
   count++;

   return true;
}

/**~*~*
  Member function pop pops the value at the top
  of the stack off, and copies it into the variable
  passed as an argument.
*~**/
bool Stack_int::pop(int &item)
{
   StackNode *temp; // Temporary pointer

   // empty stack
   if (count == 0)
       return false;

   // pop value off top of stack
   item = top->value;
   temp = top->next;
   delete top;
   top = temp;
   count--;

   return true;
}

/**~*~*
  Member function isEmpty returns true if the stack
  is empty, or false otherwise.
*~**/
bool Stack_int::isEmpty()
{
   return count == 0;
}
