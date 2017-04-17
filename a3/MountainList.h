//
//  MountainList.h
//
//
//  Created by: Alan Nguyen
//
//

#ifndef MountainList_h
#define MountainList_h

#include "Mountain.h"
#include <iostream>
using namespace std;

class MountainList {
private:
    // Declare a structure for the list
    struct ListNode {
        Mountain mount;     // The value in this node
        ListNode *next;     // To point to the next node
		ListNode *back;
    };
    
    ListNode *head;        // List head pointer
	ListNode *tail;
	static int count;
    
public:
     MountainList();  // Constructor
    ~MountainList();  // Destructor

    // Linked list operations
    void insertNode(Mountain x);
    bool deleteNode(string);
    void displayList(string key = "a") const;
    void searchList(string) const;
	void searchState(string) const;
	
	int getCount() const; // returns count
};

#endif
