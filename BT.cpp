#include <iostream>
#include <fstream>
#include <assert.h>
#include "BT.h"

using namespace std;

template < class btElementType >
BST < btElementType > :: BST()
{
    nullTree = true;
    leftTree = NULL;
    rightTree = NULL;
}

template < class btElementType >
bool BST < btElementType > :: isEmpty() const
{
    return nullTree;
}

template < class btElementType >
btElementType BST < btElementType > :: getData() const
{
    assert(!isEmpty());
    return treeData;
}

template < class btElementType >
string BST < btElementType > :: getTitle() const
{
    assert(!isEmpty());
    return treeTitle;
}

template < class btElementType >
void BST < btElementType > :: insert(const btElementType & d,const string &t,ofstream &f)
{
    if (nullTree)
    {
        nullTree = false;
        leftTree = new BST;
        rightTree = new BST;
        treeData = d;
        treeTitle = t;
    }
    else if (d == treeData)
    {
        cout<<"Conflict "<<d/100<<" "<<d%100<<endl;
        f<<"Conflict "<<d/100<<" "<<d%100<<endl;
    }
    else if (d < treeData)
        leftTree->insert(d,t,f);
    else
        rightTree->insert(d,t,f);
}

template < class btElementType >
BST < btElementType > * BST < btElementType > :: retrieve(const btElementType & d)
{
    if (nullTree || d == treeData)
        return this;
    else if (d < treeData)
        return leftTree->retrieve(d);
    else
        return rightTree->retrieve(d);
}

template < class btElementType >
BST < btElementType > * BST < btElementType > :: left()
{
    assert(!isEmpty());
    return leftTree;
}

template < class btElementType >
BST < btElementType > * BST < btElementType > :: right()
{
    assert(!isEmpty());
    return rightTree;
}

template < class btElementType >
void BST < btElementType > :: makeLeft(BST * T1)
{
    assert(!isEmpty());
    assert(left()->isEmpty());
    delete left();
    leftTree = T1;
}

template < class btElementType >
void BST < btElementType > :: makeRight(BST * T1)
{
    assert(!isEmpty());
    assert(right()->isEmpty());
    delete right();
    rightTree = T1;
}

template < class btElementType >
BST < btElementType > * BST < btElementType > :: Modify(const btElementType & d,const string & t)
{
    if (nullTree || d == treeData)
    {
        treeTitle=t;
        return this;
    }
    else if (d < treeData)
    {
        return leftTree->Modify(d,t);
    }
    else
    {
        return rightTree->Modify(d,t);
    }
}

template < class btElementType >
void BST < btElementType > :: delet(const btElementType & d,const string & t)
{
    int tempData;
    string tempTitle;
    BST * tempTree;

    assert(!isEmpty());

    if (d < treeData)
        leftTree->delet(d,t);
    else if (d > treeData)
        rightTree->delet(d,t);
    else      // d==treeData
    {
        if(rightTree->isEmpty()&&leftTree->isEmpty()) //No children
        {
            nullTree = true;
        }
        else if(!rightTree->isEmpty()&&leftTree->isEmpty()) //1 child(right)
        {
            tempTree=rightTree;
            while(!tempTree->leftTree->isEmpty())
            {
                tempTree=tempTree->leftTree;
            }
            tempData=tempTree->getData();
            tempTitle=tempTree->getTitle();
            rightTree->delet(tempData,tempTitle);
            treeData=tempData;
            treeTitle=tempTitle;
        }
        else if(!leftTree->isEmpty()&&rightTree->isEmpty()) //1 child(left)
        {
            tempTree=leftTree;
            while(!tempTree->rightTree->isEmpty())
            {
                tempTree=tempTree->rightTree;
            }
            tempData=tempTree->getData();
            tempTitle=tempTree->getTitle();
            leftTree->delet(tempData,tempTitle);
            treeData=tempData;
            treeTitle=tempTitle;
        }
        else   //2 children
        {
            tempTree =leftTree;
            while(!tempTree->rightTree->isEmpty())
                tempTree=tempTree->rightTree;
            tempData=tempTree->treeData;
            tempTitle=tempTree->treeTitle;
            leftTree->delet(tempData,tempTitle);
            treeData=tempData;
            treeTitle=tempTitle;
        }
    }
}

template < class btElementType >
void BST < btElementType > :: inOrderTraverse(BST *t,ofstream &f)
{
    if (!t->isEmpty())
    {
        // traverse left child
        inOrderTraverse(t->left(),f); // visit tree
        cout <<t->getTitle()<<" "<<t->getData()/100<<" "<<t->getData()%100<<endl;
        f <<t->getTitle()<<" "<<t->getData()/100<<" "<<t->getData()%100<<endl;
        // traverse right child
        inOrderTraverse(t->right(),f);
    }
}

template class BST <int>;
