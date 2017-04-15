#ifndef BINARYAVLTREE_H
#define BINARYAVLTREE_H

#include "BinaryTree.h"


template <class A>
class BinaryAVLTree : public BinaryTree<A>{

public:

    virtual void update();
    void leftRotate(BinaryNode<A> *node);
    void rightRotate(BinaryNode<A> *node);
};

template <class A>
void BinaryAVLTree<A>::update(){
    if (this->pointer == NULL) return;
    BinaryNode<A> *father = (this->pointer->getParent()!=NULL)? this->pointer->getParent() : this->pointer;
    int diff;



    while (father != NULL){
        diff = this->getHeight(father->getLeft()) - this->getHeight(father->getRight());

        if (diff == 2){
            if (father == this->pointer)
                this->pointer = father->getLeft();
            diff = this->getHeight(this->pointer->getLeft()) - this->getHeight(this->pointer->getRight());
            if (diff == 1){
                if (father->getLeft()==this->pointer){
                    rightRotate(father);
                    this->pointer = father->getParent();
                }
            }else if (diff == -1){
                leftRotate(this->pointer);
                this->pointer = this->pointer->getParent();
                father = this->pointer->getParent();
                rightRotate(father);
                this->pointer = father->getParent();

            }

        }
        else if (diff == -2){
            if (father == this->pointer)
                this->pointer = father->getRight();
            diff = this->getHeight(this->pointer->getLeft()) - this->getHeight(this->pointer->getRight());
            if (diff == -1){
                if (father->getRight()==this->pointer){
                    leftRotate(father);
                    this->pointer = father->getParent();
                }
            }else if (diff == 1){
                rightRotate(this->pointer);
                this->pointer = this->pointer->getParent();
                father = this->pointer->getParent();
                leftRotate(father);
                this->pointer = father->getParent();
            }

        }
        else
            this->pointer = this->pointer->getParent();


        if (this->pointer!=NULL)
            father = this->pointer->getParent();
        else
            father = NULL;
    }

    this->height = this->getHeight(this->root);
}


template <class A>
void BinaryAVLTree<A>::leftRotate(BinaryNode<A> *node){
    if(node==NULL || node->getRight()==NULL) return;

    BinaryNode<A> *father = node->getParent(), *oldR = node->getRight();
    if (father!=NULL){
        if (father->getLeft()==node)
            father->setLeft(node->getRight());
        else
            father->setRight(node->getRight());

    }else{
        this->root = oldR;
    }

    oldR->setParent(father);
    node->setRight(oldR->getLeft());
    oldR->setLeft(node);
    node->setParent(oldR);
}


template <class A>
void BinaryAVLTree<A>::rightRotate(BinaryNode<A> *node){
    if(node==NULL || node->getLeft()==NULL) return;

    BinaryNode<A> *father = node->getParent(), *oldL = node->getLeft();
    if (father!=NULL){
        if (father->getLeft()==node)
            father->setLeft(oldL);
        else
            father->setRight(oldL);

    }else{
        this->root = oldL;
    }

    oldL->setParent(father);
    node->setLeft(oldL->getRight());
    oldL->setRight(node);
    node->setParent(oldL);
}

#endif // BINARYAVLTREE_H
