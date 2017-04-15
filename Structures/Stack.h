#ifndef STACK_H
#define STACK_H

#include <cstdlib>
#include "Basic.h"
#define MAX_STACK_SIZE 13

template <class A>
class Stack {
protected:
    int max;
    int size;
    A *stack;

public:
    Stack();
    Stack(int max);

    bool push(A data);
    bool isFull(){return (max == size);}
    bool isEmpty(){return (size == 0);}
    void setMax(int max);
    void print();
    void erase();
    void destroy();

    A pop();

};

template <class A>
Stack<A>::Stack(){
    max = MAX_STACK_SIZE;
    size = 0;
    stack = new A[max];
}

template <class A>
Stack<A>::Stack(int max){
    this->max = max;
    stack = new A[max];
    size = 0;
}

template <class A>
bool Stack<A>::push(A data){
    if(size < max){
        stack[size++] = data;
        return true;
    }
    return false;
}

template <class A>
void Stack<A>::setMax(int max){
    A *aux = new A[max];
    int top = (this->max > max)? max: this->max;

    for(int i = 0; i < top; i++)
        aux[i] = stack[i];
    stack = aux;
    this->max = max;
}

template <class A>
A Stack<A>::pop(){
    if (size!= 0)
        return stack[--size];
    throw ELEMENT_NOT_FOUND;
}

template <class A>
void Stack<A>::destroy(){
    delete []stack;
}

template <class A>
void Stack<A>::erase(){
    size = 0;
}

template <class A>
void Stack<A>::print(){

    for (int i = 0; i <= size; i++){
        cout << stack[i] << "\t";
    }
    cout << endl;
}

#endif // STACK_H

