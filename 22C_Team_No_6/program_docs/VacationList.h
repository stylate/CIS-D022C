//
//  VacationList.h
//
//
//  Created by: Alan Nguyen
//
//

#ifndef VacationList_h
#define VacationList_h

#include "Vacation.h"
#include <iostream>
using namespace std;
 // Declare a structure for the list
    struct ListNode {
        Vacation vacation;     // The value in this node
        ListNode *next;     // To point to the next node
		ListNode *back;
    };

class VacationList {
private:

    ListNode *head;        // List head pointer
	ListNode *tail;
	int count;

public:
     VacationList();  // Constructor
    ~VacationList();  // Destructor

    // Linked list operations
    void insertNode(Vacation& x);
    bool deleteNode(string);
    void displayList() const;
    void searchList(string) const;
	void searchState(string) const;
	ListNode* nextNode(ListNode *pCur) const;

	int getCount() const; // returns count
};

#endif
