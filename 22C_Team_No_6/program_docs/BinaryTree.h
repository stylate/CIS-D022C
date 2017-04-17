/*Created by: Timothy Li
Program Function:Binary Tree is used to organize the data. Also prints out data in different orders, such 
as preorder traversal and prints the tree.
*/

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include <iostream>
#include <fstream>
using namespace std;
template<class ItemType>
class BinaryTree
{
protected:
    BinaryNode<ItemType>* rootPtr;		// ptr to root node
    int count;							// number of nodes in tree
    int levels;

public:
    // "admin" functions
    BinaryTree() {rootPtr = NULL; count = 0;}
    BinaryTree(const BinaryTree<ItemType> & tree){ }
    virtual ~BinaryTree() {destroyTree(this->rootPtr); }

    // common functions for all binary trees
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
    void breadthTraversal(void visit(ItemType &)) const {_breadth(visit, rootPtr);}
    void printTree(void indent(ItemType &, int), int level) const {_printTree(indent, rootPtr, level);}
    void printToFile(void visit(ItemType &)) const ;


    	// abstract functions to be implemented by derived class
    virtual bool insert(const ItemType & newData) = 0;
    virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);

    // copy from the tree rooted at nodePtr and returns a pointer to the copy
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

    // internal traverse
    void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _breadth(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _printTree(void indent(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const;
    void _printToFile(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ofstream &outFile) const;

};

//////////////////////////////////////////////////////////////////////////

//**************************************************
// copies the tree
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
   BinaryNode<ItemType>* newTreePtr = NULL;

   if (nodePtr != NULL)
   {
	   newTreePtr = new BinaryNode<ItemType>(nodePtr->getItem(), NULL, NULL);
	   newTreePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
      	   newTreePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
   }

   return newTreePtr;
}

//**************************************************
// destroys the tree
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
        if( nodePtr != NULL )
        {
            destroyTree(nodePtr->getLeftPtr());
            destroyTree(nodePtr->getRightPtr());
            delete nodePtr;
        }

}

//**************************************************
// public function to print to File
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>:: printToFile(void visit(ItemType &)) const
{
    ofstream outFile;
    outFile.open("vacationTable.txt");
    _printToFile(visit, rootPtr, outFile);
    outFile.close();
}



//**************************************************
// private function for inOrder traversal
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr!=NULL)
    {
        _inorder(visit, nodePtr->getLeftPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());

    }
}


//**************************************************
// private function for breadth first traversal as indented list
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printTree(void indent(ItemType &, int), BinaryNode<ItemType>* nodePtr, int level) const
{
	if (nodePtr != 0) {
		ItemType item = nodePtr->getItem();
		if (nodePtr->getLeftPtr() == NULL && nodePtr->getRightPtr() == NULL) int level = 1;
		for (int i = 1; i < level; i++) {
			cout << "\t";
		}
		indent(item, level);
		level++;
		_printTree(indent, nodePtr->getLeftPtr(), level);
		_printTree(indent, nodePtr->getRightPtr(), level);
	}
}

//**************************************************
// private function to print to an outFile
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printToFile(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, ofstream &outFile) const
{
    if (nodePtr!=NULL)
    {
        _printToFile(visit, nodePtr->getLeftPtr(), outFile);
        
        ItemType item = nodePtr->getItem();
        outFile << setw(7) << left << item.getCode()
        << setw(22) << right << item.getCity() << "  "
        << setw(24) << left << item.getCurrency() << " " << left
        << setw(23) << item.getLocation()
        << setw(7) << right << item.getTicket() << endl;
        
        _printToFile(visit, nodePtr->getRightPtr(), outFile);
        
    }
}

#endif
