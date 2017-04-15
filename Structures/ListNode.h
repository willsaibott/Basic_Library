#ifndef LISTNODE_H
#define LISTNODE_H

#include <cstdlib>
#include "Node.h"

template <class B>
class List;

template <class A>
class ListNode : public Node<A>
{
    friend class List<A>;
    int pos = 0;
    ListNode<A> *next = NULL;
    ListNode<A> *prev = NULL;
public:

    ListNode();
    ListNode(A newData, int pos, ListNode<A> *newNext, ListNode<A> *newPrev);
    ListNode(ListNode<A> *newNode);
    ListNode(A newData);
    ~ListNode(){}

    void setPos(int newPos){pos = newPos;}
    void setNext(ListNode<A> *newNext){next = newNext;}
    void setPrev(ListNode<A> *newPrev){prev = newPrev;}

    int getPos(){return pos;}
    ListNode<A> *getNext(){return next;}
    ListNode<A> *getPrev(){return prev;}
};

template <class A>
ListNode<A>::ListNode() : Node<A>(){
}

template <class A>
ListNode<A>::ListNode(ListNode<A> *newNode) : Node<A>(newNode->getData()){
    this->next = newNode->getNext();
    this->prev = newNode->getPrev();
    this->pos = newNode->getPos();
}

template <class A>
ListNode<A>::ListNode(A newData, int pos, ListNode<A> *newNext, ListNode<A> *newPrev) : Node<A>(newData){
    this->pos = pos;
    this->next = newNext;
    this->prev = newPrev;
}
template <class A>
ListNode<A>::ListNode(A newData) : Node<A>(newData){
}




#endif // LISTNODE_H
