// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Alan Nguyen
 
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{   
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
   
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
   
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
   
	// search for target node
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* nodePtr, const ItemType & target) const;
	
	// searches for the smallest or largest node
	BinaryNode<ItemType>* _minMax(BinaryNode<ItemType>* nodePtr, const ItemType& key);
   
public:  
	// insert a node at the correct location
	bool insert(const ItemType & newEntry, const ItemType& name, const ItemType& GPA);
	// remove a node if found
	bool remove(const ItemType & anEntry);
	// find a target node
	ItemType getEntry(const ItemType & target, string& returnedString);	
	// finds either the min or max node
	ItemType minMax(const ItemType& key);
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry, const ItemType& name, const ItemType& GPA)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry, name, GPA);
	this->rootPtr = _insert(this->rootPtr, newNodePtr);
	return true;
}  

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
	return isSuccessful; 
}  

template<class ItemType>
// accesses the private function findNode and returns the appropriate information.
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, string& returnedString)
{
	BinaryNode<ItemType>* temp = nullptr;
	temp = findNode(this->rootPtr, anEntry);
	if (temp == nullptr)
		returnedString = "not found";
	else {
		returnedString = "name and GPA: " + temp->getName() + " " + temp->getGPA();
	}
	return returnedString;
}  // have this function return name and GPA.

template <class ItemType>
// calls the private function _minMax and returns the appropriate information.
ItemType BinarySearchTree<ItemType>::minMax(const ItemType& key) {
	BinaryNode<ItemType>* temp = nullptr;
	temp = _minMax(this->rootPtr, key);
	if (temp == nullptr)
		return "not found";
	else {
		return "key " + temp->getItem() + ": " + temp->getName() + " " + temp->getGPA();
	}
} // have this return the absolute values.


//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == nullptr) nodePtr = newNodePtr;
	else {
		if (newNodePtr->getItem() < nodePtr->getItem())
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
		else
			nodePtr->setRightPtr(_insert(nodePtr->getRightPtr(), newNodePtr));
	}
	return nodePtr;
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
	if (nodePtr == 0)                   
	{
		success = false;
		return 0;
	}
	if (nodePtr->getItem() > target)		 
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem() < target)	 
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else		
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}      
	return nodePtr;   
}  

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())				
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)  
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0) 
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;      
	}
	else                                  
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}  
}  

template<class ItemType> 
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else 
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}       
}


template<class ItemType>
// standard iterative searchBST function
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const 
{
	/*if (nodePtr == nullptr) return nullptr;
	if (target < nodePtr->getItem())
		return findNode(nodePtr->getLeftPtr(), target);
	else {
		if (target > nodePtr->getItem())
			return findNode(nodePtr->getRightPtr(), target);
		else
			return nodePtr;
	}*/
	BinaryNode<ItemType>* found = nullptr;
	while (nodePtr != nullptr && nodePtr != found) {
		if (target < nodePtr->getItem())
			nodePtr = nodePtr->getLeftPtr();
		else {
			if (target > nodePtr->getItem())
				nodePtr = nodePtr->getRightPtr();
			else 
				found = nodePtr;
		}
	}
	return found;
}  

template <class ItemType>
// recursive function that locates the min and max node
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_minMax(BinaryNode<ItemType>* nodePtr,
	const ItemType& key) {
	if (nodePtr == nullptr) {
		return nodePtr;
	}
	if (key == "smallest") {
		if (nodePtr->getLeftPtr() == nullptr) return nodePtr;
		else return _minMax(nodePtr->getLeftPtr(), key);
	} else {
		if (nodePtr->getRightPtr() == nullptr) return nodePtr;
		else return _minMax(nodePtr->getRightPtr(), key);
	}
}


#endif
