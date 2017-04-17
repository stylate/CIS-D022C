/**~*~*
  This program demonstrates two basic stack operations:
  push and pop
*~**/
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "Stack_int.h"

using namespace std;

// Constants for the menu choices
const int PUSH_CHOICE = 1,
          POP_CHOICE  = 2,
          QUIT_CHOICE = 3;

// Function prototypes
int menu();
int getValidNum(int low, int high);
void pushItem(Stack_int &);
void popItem(Stack_int &);

int main()
{
    int choice;    // To hold a menu choice

    // Create the stack object
    Stack_int stack;
    srand(time(NULL));
    while ((choice = menu())!= QUIT_CHOICE)
    {
        switch (choice)
        {
           case PUSH_CHOICE:
                pushItem(stack);
                break;
           case POP_CHOICE:
                popItem(stack);
        }
    }

    cout << "\n\t*** THE END ***\n";
    return 0;
}

/**~*~*
   The menu function displays the menu and gets
   the user's choice, which is assigned to the
   reference parameter.
*~**/
int menu()
{
    int choice;
     // Display the menu and get the user's choice.
     cout << "\nWhat do you want to do?\n\t"
          << PUSH_CHOICE
          << " - Push an item onto the stack\n\t"
          << POP_CHOICE
          << " - Pop an item off the stack\n\t"
          << QUIT_CHOICE
          << " - Quit the program\n"
          << "Enter your choice: ";

     choice = getValidNum(PUSH_CHOICE, QUIT_CHOICE);
     return choice;
}

/**~*~*
   The pushItem function gets a random integer
   and pushes it onto the stack.
*~**/
void pushItem(Stack_int &stack)
{
     int item;

     item = rand() % 89 + 10;
     cout << "\n\t" << item << " will be pushed onto the stack\n";
     stack.push(item);
}

/**~*~*
   The popItem function pops an item from the stack
*~**/
void popItem(Stack_int &stack)
{
     bool status;
     int item = 0;

     // Pop the item.
     status = stack.pop(item);

     // Display the item.
     if (status)
        cout << "\n\t" << item << " was popped.\n\n";
     else
        cout << "\n\t*** Empty stack! ***\n\n";
}

/**~*~*
   This function prompts the user to enter an integer number within a given range
   If the input is not valid (not a number or if it is outside of the range) it
   prompts the user to enter a new number, until the input is valid.
*~**/
int getValidNum(int low, int high)
{
    int num;
    bool success;

    do
    {
        cout << "Please enter a number (" << low << " to " << high << "): ";
        success = cin >> num;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success || num < low || num > high);

    return num;
}

/**~*~*


What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 1

        14 will be pushed onto the stack

What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 1

        32 will be pushed onto the stack

What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 1

        46 will be pushed onto the stack

What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 2

        46 was popped.

What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 2

        32 was popped.

What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 2

        14 was popped.

What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 2

        *** Empty stack! ***

What do you want to do?
        1 - Push an item onto the stack
        2 - Pop an item off the stack
        3 - Quit the program
Enter your choice: Please enter a number (1 to 3): 3

        *** THE END ***
*~**/
