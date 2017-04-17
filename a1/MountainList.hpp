//
//  Mountains.hpp
//
//
//  Created by: A. Student
//
//

#ifndef MountainsList_hpp
#define MountainsList_hpp

using namespace std;

#include <string>

struct Mountain
{
    string name;
    double elevation;
    string range;
    string state;
};

class MountainList
{
private:
    // Declare a structure for the list
    struct ListNode
    {
        Mountain mount;     // The value in this node
        ListNode *next;     // To point to the next node
    };
    
    ListNode *head;        // List head pointer
    
    
public:
     MountainList();  // Constructor
    ~MountainList();   // Destructor
    
    // Linked list operations
    void insertNode(Mountain x);
    bool deleteNode(string);
    void displayList() const;
    void searchList(string) const;
    
};

#endif
