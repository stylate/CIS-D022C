//
//  MountainList.cpp
//
//
//  Created by Alan Nguyen
//  
//

#include "MountainList.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

int MountainList::count = 0;

//**************************************************
// Constructor - sets initial values for variables
// in class Mountain.
//**************************************************
MountainList::MountainList()
{
    head = new ListNode; // head points to the sentinel
	head->next = head;
	head->back = head;
}

//**************************************************
// The displayList function shows the value
// stored in each node of the linked list
// pointed to by head.
//**************************************************
void MountainList::displayList(string key) const
{
    ListNode *pCur;  
    
    // Display a header
    cout << right << "====="  <<setw(22) << "=========" << setw(7) <<"=====" <<  setw(24)<< "===== " <<endl;
    cout << "Name "  <<setw(22) << "Elevation" << setw(7) <<"Range" <<  setw(24)<< "State " <<endl;
    cout << "====="  <<setw(22) << "=========" << setw(7) <<"=====" <<  setw(24)<< "===== " <<endl;

    // Position pCur: skip the head of the list.
	if (key == "a") {
		pCur = head->next;
		pCur->back = head;
	} else pCur = head->back;
    // While pCur points to a node, traverse the list.
    while (pCur != head)
    {
		// Display the value in this node.
		cout << setw(20) << left << pCur->mount.get_name()
              << setw(7) << right << pCur->mount.get_elevation() << "  "
              << setw(22) << left << pCur->mount.get_range() << " " << left
              << setw(23) << pCur->mount.get_state() << endl;
        if (key == "a") pCur = pCur->next;
		else pCur = pCur->back;
    }
    // End of the report
    cout << "=================================================================" << endl;
	cout << "There are " << count << " items in the list\n\n";
}

//**************************************************
// The insertNode function inserts a new node in
// a sorted list (it keeps the list sorted)
//**************************************************
void MountainList::insertNode(Mountain dataIn)
{
    ListNode *newNode;  // A new node
    ListNode *pCur;     // To traverse the list
    ListNode *pPre;     // The previous node
    
    // Allocate a new node and store num there.
    newNode = new ListNode;
    newNode->mount = dataIn;
    // Initialize pointers
    pPre = head;
    pCur = head->next;
	// if blank, then sentinel node
	// while sort
    while (pCur != head && pCur->mount.get_name() < dataIn.get_name())
    {
		pPre = pCur;
        pCur = pCur->next;
    }
    
    // Insert the new node between pPre and pCur
	newNode->next = pCur;
	newNode->back = pPre;
	pCur->back = newNode;
	pPre->next = newNode;
	count++;
	/* DEBUG
	cout << "pPre->back: " << pPre->back->mount.get_name() << endl;
	cout << "pPre: " << pPre->mount.get_name() << endl;
	cout << "pPre->next: " << pPre->next->mount.get_name() << endl;
	cout << "newNode->back: " << newNode->back->mount.get_name() << endl;
	cout << "newNode: " << newNode->mount.get_name() << endl;
	cout << "newNode->next: " << newNode->next->mount.get_name() << endl;
	cout << "pCur->back: " << pCur->back->mount.get_name() << endl;
	cout << "pCur: " << pCur->mount.get_name() << endl;
	cout << "pCur->next: " << pCur->next->mount.get_name() << endl;
	cout << endl; */
}


//**************************************************
// The deleteNode function searches for a node
// with num as its value. The node, if found, is
// deleted from the list and from memory.
//**************************************************
bool MountainList::deleteNode(string target)
{
    ListNode *pCur;       // To traverse the list
    ListNode *pPre;        // To point to the previous node
	ListNode *tail;
	bool deleted = false;
    // Initialize pointers
    pPre = head;
    pCur = head->next;
    // note: do not go through the entire SORTED list
	while (pCur != head && pCur->mount.get_name() < target)
	{
		pPre = pCur;
		pCur = pCur->next;
	}
    
    // If found, delete the node
    if (pCur != head && pCur->mount.get_name() == target)
    {
		pCur->back->next = pCur->next;
		pCur->next->back = pPre;
        delete pCur;
        deleted = true;
		count--;
    }
    return deleted;    
}

//**************************************************
// The searchList function searches for a node
// with target as its mountain name.
//**************************************************
void MountainList:: searchList(string target) const
{
    ListNode *pCur;        // To transverse the list
	ListNode *pPre;

	pPre = head;
    pCur = head->next;
    while ((pCur != head || pPre != head) && pCur->mount.get_name() < target) {
        pCur = pCur->next;
		pPre = pPre->back;
    }
    
    if ((pCur!= head || pPre != head) && pCur->mount.get_name() == target) {
        cout << "FOUND: "
             << pCur->mount.get_name() << " "
             << pCur->mount.get_elevation() << " "
             << pCur->mount.get_range() << " "
             << pCur->mount.get_state() << " \n\n";
    } else 
		cout << target << " NOT FOUND\n\n";
}

//**************************************************
// getCount gathers the total number               *
// of cities in the list.                          *
// This function returns the total number          *
// of cities.                                      *
//**************************************************
int MountainList::getCount() const {
	return count;
}

//**************************************************
// Destructor                                      *
// This function deletes every node in the list.   *
//**************************************************
MountainList::~MountainList()
{
    ListNode *pCur;   // To traverse the list
    ListNode *pNext;  // To point to the next node
	ListNode *pBack; // To point to the node before

    pCur = head->next;
    while (pCur != head)
    {
        pNext = pCur->next;
        
        // Delete the current node.
        cout << "DEBUG - Destructor: Now deleting " << pCur->mount.get_name() << endl;
        delete pCur;
        
        pCur = pNext;
    }
	system("PAUSE");
    delete head; // delete the sentinel node
}
