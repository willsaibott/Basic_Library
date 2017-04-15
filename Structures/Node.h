#ifndef NODE_H
#define NODE_H

#include "Basic.h"

template <class A>
class Node {

protected:
    A data;
    bool visited = false;
public:

    Node(){}
    Node(A newData){setData(newData);}
    ~Node(){}
    //getters
    A getData(){return this->data;}
    bool isVisited(){return this->visited;}

    //setters
    void setData(A newData);
    void setVisited(bool isVisited){this->visited = isVisited;}

};

template <>
Node<char*>::Node(){
    data = nullptr;
}


template <>
Node<char*>::~Node(){
    if (this->data != nullptr || this->data != NULL){
        delete data;
        data = nullptr;
    }
}

template <class A>
void Node<A>::setData(A newData){
    this->data = newData;
}

template <>
void Node<char*>::setData(char* newData){
    if (newData!=NULL || newData != nullptr){
        if (this->data != nullptr || this->data != NULL)
            delete data;
        this->data = new char[strlen(newData)];
        strcpy(this->data, newData);
    }
}

template <>
void Node<std::string>::setData(std::string newData){
    this->data = std::string(newData);
}


#endif // NODE_H

