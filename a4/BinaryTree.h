// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Alan Nguyen
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h" // for breadth

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &, ItemType&, ItemType&)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType &, ItemType&, ItemType&)) const  { _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType &, ItemType&, ItemType&)) const{ _postorder(visit, rootPtr); }
	void breadth(void visit(ItemType&, ItemType&, ItemType&)) const { _breadth(visit, rootPtr); }

	// indents a list based on preOrder traversal.
	void preIndent(void indent(ItemType&, ItemType&, ItemType&, int), int level) { _preIndent(indent, rootPtr, level); }

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData, const ItemType& name, const ItemType& GPA) = 0;
	virtual bool remove(const ItemType & data) = 0; 
	virtual ItemType getEntry(const ItemType & anEntry, string& returnedString) = 0;
	virtual ItemType minMax(const ItemType& key) = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const;
	void _breadth(void visit(ItemType&, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const;
	
	// print indent
	void _preIndent(void indent(ItemType&, ItemType&, ItemType&, int), BinaryNode<ItemType>* nodePtr, int level);
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
    
   
    return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != nullptr) {
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
		nodePtr = nullptr;
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		ItemType name = nodePtr->getName();
		ItemType GPA = nodePtr->getGPA();
		visit(item, name, GPA);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		ItemType item = nodePtr->getItem();
		ItemType name = nodePtr->getName();
		ItemType GPA = nodePtr->getGPA();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item, name, GPA);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0) {
		ItemType item = nodePtr->getItem();
		ItemType name = nodePtr->getName();
		ItemType GPA = nodePtr->getGPA();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item, name, GPA);
	}
}

template <class ItemType>
void BinaryTree<ItemType>::_breadth(void visit(ItemType &, ItemType&, ItemType&), BinaryNode<ItemType>* nodePtr) const {
	Queue<BinaryNode<ItemType>*> treeQueue;
	if (nodePtr == nullptr) {
		cout << "The tree is empty!\n";
		return;
	}
	treeQueue.enqueue(nodePtr);
	while (!treeQueue.isEmpty()) {
		treeQueue.dequeue(nodePtr);
		visit(nodePtr->getItem(), nodePtr->getName(), nodePtr->getGPA());
		if (nodePtr != nullptr) {
			if (nodePtr->getLeftPtr() != nullptr) treeQueue.enqueue(nodePtr->getLeftPtr());
			if (nodePtr->getRightPtr() != nullptr) treeQueue.enqueue(nodePtr->getRightPtr());
		}
	}
}

template <class ItemType>
void BinaryTree<ItemType>::_preIndent(void indent(ItemType&, ItemType&, ItemType&, int), BinaryNode<ItemType>* nodePtr, int level) {
	if (nodePtr != 0) {
		ItemType item = nodePtr->getItem();
		ItemType name = nodePtr->getName();
		ItemType GPA = nodePtr->getGPA();
		if (nodePtr->getLeftPtr() == nullptr && nodePtr->getRightPtr() == nullptr) int level = 1;
		for (int i = 1; i < level; i++) {
			cout << "\t";
		}
		indent(item, name, GPA, level);
		level++;
		_preIndent(indent, nodePtr->getLeftPtr(), level);
		_preIndent(indent, nodePtr->getRightPtr(), level);
	}
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}  


#endif

