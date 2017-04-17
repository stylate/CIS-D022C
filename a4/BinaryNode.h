// Node for a binary tree
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Alan Nguyen
 
#ifndef _BINARY_NODE
#define _BINARY_NODE

template<class ItemType>
class BinaryNode
{   
private:
	ItemType              item;         // Data portion
	ItemType id; // student ID/unique key
	ItemType gpa; // student GPA
	ItemType name; // last, first name
	BinaryNode<ItemType>* leftPtr;		// Pointer to left child
	BinaryNode<ItemType>* rightPtr;		// Pointer to right child

public:
	// constructors
	 BinaryNode(const ItemType& anItem, const ItemType& aGPA, const ItemType& aName) { item = anItem; gpa = aGPA; name = aName; leftPtr = 0; rightPtr = 0; }
	 BinaryNode(const ItemType& anItem, const ItemType& aGPA, const ItemType& aName,
	 			BinaryNode <ItemType>* left, BinaryNode <ItemType>* right) { item = anItem; gpa = aGPA; name = aName; leftPtr = left; rightPtr = right; }
	// accessors
	void setItem(const ItemType & anItem) {item = anItem;}
	void setGPA(const ItemType& aGPA) { gpa = aGPA; }
	void setName(const ItemType& aName) { name = aName; }
	void setLeftPtr(BinaryNode<ItemType>* left) {leftPtr = left;}
    void setRightPtr(BinaryNode<ItemType>* right) {rightPtr = right;}
	// mutators
	ItemType getItem() const	 {return item;}
	ItemType getName() const { return name; }
	ItemType getGPA() const { return gpa; }
	BinaryNode<ItemType>* getLeftPtr() const  {return leftPtr;}
	BinaryNode<ItemType>* getRightPtr() const {return rightPtr;}

	bool isLeaf() const {return (leftPtr == 0 && rightPtr == 0);}
}; 

#endif 
