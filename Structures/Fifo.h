#ifndef FIFO_H
#define FIFO_H


#include <cstdlib>
#include "Basic.h"

#define MAX_FIFO_SIZE 13

using namespace std;
template <class A>
class Fifo {
protected:
    int max;
    int top;
    int start;
    bool full;
    A *fifo;
    void increaseTop();
    void decreaseTop();
    void increaseStart();
    void decreaseStart();
public:
    Fifo();
    Fifo(int max);

    bool enqueue(A data);
    bool isFull(){return full;}
    bool isEmpty(){return (start == top && full == false);}
    void setMax(int max);
    void erase();
    void destroy();
    void print();
    A dequeue();

};

template <class A>
void Fifo<A>::increaseTop(){
    top = ((top < max - 1)? (top + 1): 0);
}

template <class A>
void Fifo<A>::decreaseTop(){
    top = ((top > 0)? (top - 1): max - 1);
}

template <class A>
void Fifo<A>::increaseStart(){
    start = ((start < max - 1)? (start + 1): 0);
}


template <class A>
void Fifo<A>::decreaseStart(){
    start = ((start > 0)? (start - 1): max - 1);
}

template <class A>
Fifo<A>::Fifo(){
    max = MAX_FIFO_SIZE;
    top = 0;
    start = 0;
    fifo = new A[max];
    full = false;
}

template <class A>
Fifo<A>::Fifo(int max){
    this->max = max;
    fifo = new A[max];
    top = 0;
    start = 0;
    full = false;
}

template <class A>
bool Fifo<A>::enqueue(A data){
    if (full)
        return false;
    fifo[top] = data;
    increaseTop();
    full = ((top==start)? true : false);
    return true;
}

template <class A>
void Fifo<A>::setMax(int max){
    A *aux = new A[max];
    int topCopy = (this->max > max)? max: this->max;

    for(int i = 0; i < topCopy; i++)
        aux[i] = fifo[i];

    fifo = aux;
    this->max = max;
}

template <class A>
A Fifo<A>::dequeue(){
    if (top!=start || full){
        A data = fifo[start];
        increaseStart();
        full =  false;
        return data;
    }
    throw ELEMENT_NOT_FOUND;
}

template <class A>
void Fifo<A>::destroy(){
    delete []fifo;
}

template <class A>
void Fifo<A>::erase(){
    start = top = 0;
    full = false;
}

template <class A>
void Fifo<A>::print(){
    int size = (top < start || full)? (top + max - start) : top - start;

    for (int i = 0; i < size; i++){
        if (i + start < max)
            cout << fifo[i + start] << "\t";
        else
            cout << fifo[i + start - max] << "\t";
    }
    cout << endl;
}

#endif // FIFO_H


