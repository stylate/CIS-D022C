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
    head = new ListNode; // head points to the sentinel node
	head->mount.set_elevation();
	head->mount.set_name();
	head->mount.set_range();
	head->mount.set_state();
	
    head->next = nullptr;
}

//**************************************************
// The displayList function shows the value
// stored in each node of the linked list
// pointed to by head.
//**************************************************
void MountainList::displayList() const
{
    ListNode *pCur;  
    
    // Display a header
    cout << right << "====="  <<setw(22) << "=========" << setw(7) <<"=====" <<  setw(24)<< "===== " <<endl;
    cout << "Name "  <<setw(22) << "Elevation" << setw(7) <<"Range" <<  setw(24)<< "State " <<endl;
    cout << "====="  <<setw(22) << "=========" << setw(7) <<"=====" <<  setw(24)<< "===== " <<endl;

    // Position pCur: skip the head of the list.
    pCur = head->next;
    // While pCur points to a node, traverse the list.
    while (pCur)
    {
        // Display the value in this node.
		cout << setw(20) << left << pCur->mount.get_name()
              << setw(7) << right << pCur->mount.get_elevation() << "  "
              << setw(22) << left << pCur->mount.get_range() << " " << left
              << setw(23) << pCur->mount.get_state() << endl;
        // Move to the next node.
        pCur = pCur->next;
    }
    // End of the report
    cout << "=================================================================" <<endl;
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
    while (pCur != nullptr && pCur->mount.get_name() < dataIn.get_name())
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
bool MountainList::deleteNode(string target)
{
    ListNode *pCur;       // To traverse the list
    ListNode *pPre;        // To point to the previous node
    bool deleted = false;
    // Initialize pointers
    pPre = head;
    pCur = head->next;
    
    while (pCur != nullptr && pCur->mount.get_name() != target)
    {
        pPre = pCur;
        pCur = pCur->next;
    }
    
    // If found, delte the node
    if (pCur != nullptr && pCur->mount.get_name() == target)
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
// with target as its mountain name.
//**************************************************
void MountainList:: searchList(string target) const
{
    ListNode *pCur;        // To transverse the list
    
    pCur = head->next;
    while (pCur != nullptr && pCur->mount.get_name() != target) {
        pCur = pCur->next;
    }
    
    if (pCur!= nullptr) {
        cout << "FOUND: "
             << pCur->mount.get_name() << " "
             << pCur->mount.get_elevation() << " "
             << pCur->mount.get_range() << " "
             << pCur->mount.get_state() << " \n\n";
    } else
        cout << target << " NOT FOUND\n\n";
}

//**************************************************
// The searchState function searches for a node
// with target (a called string) as the state.
// If found, then all mountains in said 
// state are displayed.
//**************************************************
void MountainList::searchState(string target) const
{
	ListNode *pCur;        // To transverse the list
	int counter = 0; // counts # of mountains under specified state
	pCur = head->next;
	while (pCur != nullptr) {
		// there are special cases such that there is an extra whitespace
		// after the state, thus the find is used
		if (pCur->mount.get_state().find(target) != string::npos) {
			cout << "FOUND: "
				<< pCur->mount.get_name() << " "
				<< pCur->mount.get_elevation() << " "
				<< pCur->mount.get_range() << " "
				<< pCur->mount.get_state() << " \n\n";
			counter++;
		}
		pCur = pCur->next;
	}
	if (counter == 0) cout << target << " NOT FOUND\n\n";
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
    
    
    pCur = head->next;
    while (pCur != NULL)
    {
        
        pNext = pCur->next;
        
        // Delete the current node.
        cout << "DEBUG - Destructor: Now deleting " << pCur->mount.get_name() << endl;
        delete pCur;
        
        
        pCur = pNext;
    }
  
    delete head; // delete the sentinel node
}
