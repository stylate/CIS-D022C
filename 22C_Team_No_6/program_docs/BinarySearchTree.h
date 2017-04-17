/*Created by: Timothy Li
Program Function: BST is derived from Binary Tree, and is used to sort the data by airport code, and another tree sorts it by using the city name.
This class also searches for entries in the tree, as well as insert and delete.
*/


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
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, ItemType target, bool & success);

    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr,const ItemType & target) const;

public:
    // insert a node at the correct location
    bool insert(const ItemType & newEntry) ;
    // remove a node if found
    bool remove(const ItemType & data);
    // find a target node
    bool getEntry(const ItemType& anEntry, ItemType & returnedItem) const ;

};


///////////////////////// public function definitions ///////////////////////////
//**************************************************
// insert into bst
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::insert( const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);

    if (this->rootPtr==NULL)
    {
        this->rootPtr=newNodePtr; //first item
    }
    else
    {
        this->rootPtr = _insert(this->rootPtr, newNodePtr);
    }
    return true;
}

//**************************************************
// remove node from bst
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
}
//**************************************************
// searches for entry
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType> *foundEntry=findNode(this->rootPtr, anEntry);

    if(foundEntry==NULL)
    {
        return false;
    }

    if (foundEntry)
    {
        returnedItem = foundEntry->getItem();
        return true;
    }
    return false;
}


//////////////////////////// private functions ////////////////////////////////////////////

//**************************************************
// private function for insert
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr)
{

    if (nodePtr==nullptr)
    {
        return newNodePtr;
    } else if(nodePtr->getItem() > newNodePtr->getItem()){
        BinaryNode<ItemType>* tempPtr;
        tempPtr = _insert(nodePtr->getLeftPtr(), newNodePtr);
        nodePtr->setLeftPtr(tempPtr);
    }else{
        BinaryNode<ItemType>* tempPtr;
        tempPtr = _insert(nodePtr->getRightPtr(), newNodePtr);
        nodePtr->setRightPtr(tempPtr);

    }
    return nodePtr;
}

//**************************************************
// private function for remove
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
        ItemType target,
        bool & success)
{
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (nodePtr->getItem().getCode() > target.getCode())
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem().getCode() < target.getCode())
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
}
//**************************************************
// private function for delete
//**************************************************
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
//**************************************************
// to remove left most node
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor)
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

//**************************************************
// private function for find node
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,const ItemType & target) const
{
    if(!nodePtr)
    {
        return nodePtr;
    }

    BinaryNode<ItemType>* pWalk = nodePtr;
    while(pWalk)
    {
        if(target < pWalk->getItem())
            pWalk = pWalk->getLeftPtr();
        else if(target > pWalk->getItem())
            pWalk = pWalk->getRightPtr();
        else
            return pWalk;
    }

    return pWalk;
}

#endif