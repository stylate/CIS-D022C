//
//  MountainList.cpp
//
//
//  Created by Alan Nguyen
//
//

#include "VacationList.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

//**************************************************
// Constructor - sets initial values for variables
// in class Vacation.
//**************************************************
VacationList::VacationList()
{
    head = new ListNode; // head points to the sentinel
	head->next = head;
	count = 0;
}

//**************************************************
// The next element function
//**************************************************
ListNode* VacationList::nextNode(ListNode *pCur) const
{
    if (pCur == NULL)
        pCur = head;

    if (pCur->next == head)
        return NULL;

   return pCur->next;
}


//**************************************************
// The displayList function shows the value
// stored in each node of the linked list
// pointed to by head.
//**************************************************
void VacationList::displayList() const
{
    ListNode *pCur;

    if (head->next == head)
        return;
    // Display a header



    // Position pCur: skip the head of the list.
	pCur = head->next;
    // While pCur points to a node, traverse the list.
    while (pCur != head)
    {
		// Display the value in this node.
		pCur->vacation.print();

        pCur = pCur->next;
    }

}

//**************************************************
// The insertNode function inserts a new node in
// a sorted list (it keeps the list sorted)
//**************************************************
void VacationList::insertNode(Vacation& dataIn)
{
    ListNode *newNode;  // A new node
    ListNode *pCur;     // To traverse the list
    ListNode *pPre;     // The previous node

    // Allocate a new node and store num there.
    newNode = new ListNode;
    newNode->vacation = dataIn;

    // Initialize pointers
    pPre = head;
    pCur = head->next;
    while (pCur != head && pCur->vacation.getCode() < dataIn.getCode())
    {
        pPre = pCur;
        pCur = pCur->next;
    }

    // Insert the new node between pPre and pCur
    pPre->next = newNode;
    newNode->next = pCur;
    count++;
}


//**************************************************
// The deleteNode function searches for a node
// with num as its value. The node, if found, is
// deleted from the list and from memory.
//**************************************************
bool VacationList::deleteNode(string target)
{
    ListNode *pCur;       // To traverse the list
    ListNode *pPre;        // To point to the previous node
    bool deleted = false;
    // Initialize pointers
    pPre = head;
    pCur = head->next;

    while (pCur != NULL && pCur->vacation.getCode() != target)
    {
        pPre = pCur;
        pCur = pCur->next;
    }

    // If found, delete the node
    if (pCur != NULL && pCur->vacation.getCode() == target)
    {
        pPre->next = pCur->next;
        delete pCur;
        deleted = true;
        count--;
    }
    return deleted;

}

//**************************************************
// The searchList function searches for a node
// with target as its vacation code.
//**************************************************
void VacationList::searchList(string target) const
{
    ListNode *pCur;        // To transverse the list

    pCur = head->next;
    while (pCur != NULL && pCur->vacation.getCode() != target) {
        pCur = pCur->next;
    }

    if (pCur!= NULL && pCur->vacation.getCode() == target) {
        cout << "FOUND: \n";

         pCur->vacation.print();
    } else
        cout << target << " NOT FOUND\n\n";
}

//**************************************************
// getCount gathers the total number               *
// of cities in the list.                          *
// This function returns the total number          *
// of cities.                                      *
//**************************************************
int VacationList::getCount() const {
	return count;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
VacationList::~VacationList()
{
    ListNode *pCur;   // To traverse the list
    ListNode *pNext;  // To point to the next node

    pCur = head->next;
    while (pCur != head)
    {
        pNext = pCur->next;

        // Delete the current node.
        //cout << "DEBUG - Destructor: Now deleting " << pCur->vacation.getCode() << endl;
        delete pCur;

        pCur = pNext;
    }
	//system("PAUSE");
    delete head; // delete the sentinel node
}
