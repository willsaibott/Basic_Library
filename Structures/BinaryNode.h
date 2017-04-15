#ifndef BINARYNODE_H
#define BINARYNODE_H

#include "Node.h"


template <class A>
class BinaryNode : public Node<A>
{

protected:
    int n = 0;

    BinaryNode<A> *parent = NULL;
    BinaryNode<A> *right = NULL;
    BinaryNode<A> *left = NULL;

public:

    BinaryNode() : Node<A>(){}
    BinaryNode(A newData) : Node<A>(newData){}
    BinaryNode(BinaryNode<A> *newNode);
    BinaryNode(A newData, BinaryNode<A> *newRight, BinaryNode<A> *newLeft, BinaryNode<A> *newParent);

    //getters
    int getN(){return n;}

    BinaryNode<A> *getRight(){return right;}
    BinaryNode<A> *getLeft(){return left;}
    BinaryNode<A> *getParent(){return this->parent;}


    //setters
    void setRight(BinaryNode<A> *newRight){
        this->right = newRight;
        update();
    }
    void setLeft(BinaryNode<A> *newLeft){
        this->left = newLeft;
        update();
    }
    void setParent(BinaryNode<A> *newParent){
        this->parent = newParent;
        update();
    }

    //others
    void update();

};


template <class A>
BinaryNode<A>::BinaryNode(BinaryNode<A> *newNode) : Node<A>(){
    if (newNode!=NULL){
        setRight(newNode->getRight());
        setParent(newNode->getParent());
        setLeft(newNode->getLeft());
        this->setData(newNode->getData());
    }
}


template <class A>
BinaryNode<A>::BinaryNode(A newData, BinaryNode<A> *newRight, BinaryNode<A> *newLeft, BinaryNode<A> *newParent) : Node<A>(newData){
    setParent(newParent);
    setRight(newRight);
    setLeft(newLeft);
}


template <class A>
void BinaryNode<A>::update(){
    n = 0;
    if (left!=NULL)
        n++;
    if (right!=NULL)
        n++;
}



#endif // BINARYNODE_H
