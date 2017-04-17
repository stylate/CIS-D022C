// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Elizabeth Chang <=============================== ADD YOUR NAME HERE

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
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, ItemType & target) const;
    // search for smallest node
    BinaryNode<ItemType>* findSmallestNode(BinaryNode<ItemType>* treePtr) const;
    // search for largest node
    BinaryNode<ItemType>* findLargestNode(BinaryNode<ItemType>* treePtr) const;
    
public:
    // insert a node at the correct location
    bool insert(const ItemType & newEntry) ;
    // remove a node if found
    bool remove(const ItemType & data);
    // find a target node
    bool getEntry(ItemType& anEntry, ItemType & returnedItem) const ;
    // find smallest node
    bool getSmallestEntry(ItemType & returnedItem) const;
    // find largest node
    bool getLargestEntry(ItemType & returnedItem) const;
    
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
bool BinarySearchTree<ItemType>::getEntry(ItemType& anEntry, ItemType & returnedItem) const
{
    BinaryNode<ItemType>* foundEntry;
        
        foundEntry=findNode(this->rootPtr, anEntry);
        if(foundEntry==NULL)
        {
            cout <<"NOT FOUND! " <<endl;
            return false;
        }
        if (foundEntry->getItem().getId()== (anEntry.getId()))
        {
            returnedItem=foundEntry->getItem();
            cout <<"found! result: "
                <<foundEntry->getItem().getId() <<" "
                <<foundEntry->getItem().getName() <<" "
                <<foundEntry->getItem().getGpa()<<endl ;
            return true;
        }
    return false;
}
//**************************************************
// searches for smallest node
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getSmallestEntry(ItemType & returnedItem) const
{

    if(this->rootPtr==NULL)
        return false;
    
    returnedItem=findSmallestNode(this->rootPtr)->getItem();
    return true;
    
}
//**************************************************
// searches for largest node
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getLargestEntry(ItemType & returnedItem) const
{
    if(this->rootPtr==NULL)
        return false;
    returnedItem = findLargestNode(this->rootPtr)->getItem();
    return true;

}



//////////////////////////// private functions ////////////////////////////////////////////

//**************************************************
// private function for insert
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNodePtr)
{

        if (newNodePtr->getItem().getId() < nodePtr->getItem().getId())
        {
            if (nodePtr->getLeftPtr()==NULL)
            {
                nodePtr->setLeftPtr(newNodePtr);
            }
            else
            {
                _insert(nodePtr->getLeftPtr(), newNodePtr);
            }
        }
        else if (newNodePtr->getItem().getId() > nodePtr->getItem().getId())
        {
            if (nodePtr->getRightPtr()==NULL)
            {
                nodePtr->setRightPtr(newNodePtr);
            }
            else
            {
                _insert(nodePtr->getRightPtr(), newNodePtr);
            
            }
        }
    
    return this->rootPtr;
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
    if (nodePtr->getItem().getId() > target.getId())
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    else if (nodePtr->getItem().getId() < target.getId())
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
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr, ItemType & target) const
{
        while (nodePtr != NULL)
        {
            if (nodePtr->getItem().getId()==target.getId())
            {
                return nodePtr;
            }
            if (target.getId() > nodePtr->getItem().getId())
                nodePtr = nodePtr->getRightPtr();
            else if (target.getId() < nodePtr->getItem().getId())
                    nodePtr = nodePtr->getLeftPtr();
        }
        
        if (nodePtr == NULL)
            return NULL;

 
    return NULL;
}  
//**************************************************
// private function for find smallest node
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType> :: findSmallestNode(BinaryNode<ItemType>* treePtr) const
{
    if (treePtr->getLeftPtr() == NULL)
    {
        return treePtr;
    }
    else
    {
        return findSmallestNode(treePtr->getLeftPtr());
    }

}
//**************************************************
// private function for find largest node
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType> :: findLargestNode(BinaryNode<ItemType>* treePtr) const
{
    if (treePtr->getRightPtr() == NULL)
    {
        return treePtr;
    }
    else
    {
        return findLargestNode(treePtr->getRightPtr());
    }
}

#endif
