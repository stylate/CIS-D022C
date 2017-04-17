// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Elizabeth Chang

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "Queue.h"
#include <iostream>
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
    int getLevels(BinaryNode<ItemType>* nodePtr) const   ;
    void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
    void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
    void breadthTraversal(void visit(ItemType &)) const {_breadth(visit, rootPtr);}
    void printTree(void visit(ItemType &)) const;

    
    	// abstract functions to be implemented by derived class
    virtual bool insert(const ItemType & newData) = 0;
    virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(ItemType & anEntry, ItemType & returnedItem) const = 0;
    
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
    void _printtree(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level, const int i) const;
                          
};

//////////////////////////////////////////////////////////////////////////
//**************************************************
// determines how many levels is in the tree
//**************************************************
template<class ItemType>
int BinaryTree<ItemType>::getLevels(BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr==NULL)
        return NULL;

    int levels;
    int lheight = getLevels(nodePtr->getLeftPtr());
    int rheight = getLevels(nodePtr->getRightPtr());
    
    if (lheight > rheight)
        return levels=lheight+1;
    else
        return levels =rheight+1;
}
//**************************************************
// prints the tree as indented list
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::printTree(void visit(ItemType &)) const
{

    BinaryNode<ItemType> *nodePtr;
    nodePtr=this->rootPtr;
    if (this->rootPtr==NULL)
        return;
    int treeLevels=getLevels(this->rootPtr);
    for (int i=0; i<treeLevels; i++)
    {
        
        for (int j=0; j<i; j++)
        {
            cout <<"\t";
        }
        cout << i+1 <<". " <<endl;
        _printtree(visit, nodePtr, i, i);
    }
}

//**************************************************
// copies the tree
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType>* newNodePtr = 0;
    
    return newNodePtr;
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
// private function for preOrder traversal
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != NULL)
    {
        ItemType item = nodePtr->getItem();
        visit(item);
        _preorder(visit, nodePtr->getLeftPtr());
        _preorder(visit, nodePtr->getRightPtr());
        
    }

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
// private function for postOrder traversal
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr!=NULL)
    {
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
    }
    
}

//**************************************************
// private function for breadth first traversal iteratively
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_breadth(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
    {

        {
             Queue<BinaryNode<ItemType> *> q;
            
            if (nodePtr)
            {
                q.enqueue(nodePtr);
            }
            BinaryNode<ItemType> *temp_node;
            while (!q.isEmpty())
            {
                q.dequeue(temp_node);
                cout<<temp_node->getItem().getId() <<" "
                    <<temp_node->getItem().getName() <<" "
                    <<temp_node->getItem().getGpa() <<endl;
                
                if (temp_node->getLeftPtr())
                {
                    q.enqueue(temp_node->getLeftPtr());
                }
                if (temp_node->getRightPtr())
                {
                    q.enqueue(temp_node->getRightPtr());
                }
            }
        }
    }

//**************************************************
// private function for breadth first traversal as indented list
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_printtree(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, int level, const int i) const
{
    if (nodePtr!=NULL)
    {

        if (level == 0)
        {
            
            for (int j=0; j<i; j++)
            {
                cout <<"\t" ;
            }
            cout <<nodePtr->getItem().getId() <<endl;
            return;
        }
            _printtree(visit, nodePtr->getRightPtr(), level-1, i);
            _printtree(visit, nodePtr->getLeftPtr(), level-1, i);

    }
    
}

#endif

