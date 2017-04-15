#ifndef TREENODE_H
#define TREENODE_H

#include <vector>
#include "Node.h"


template <class A>
class TreeNode : public Node<A>
{

protected:
    int n = 0;

    TreeNode<A> *parent = NULL;
    vector<TreeNode<A>*> leaves;

public:

    TreeNode() : Node<A>(){}
    TreeNode(A newData) : Node<A>(newData){}
    TreeNode(TreeNode<A> *newNode);
    TreeNode(A newData, vector<TreeNode<A>*> newLeaves, TreeNode<A> *newParent);

    //getters
    int getN(){return n;}

    TreeNode<A> *getLeave(int leave){return (leave < n)? leaves.at(leave): NULL;}
    TreeNode<A> *getParent(){return this->parent;}
    vector<TreeNode<A>*> getLeaves(){return leaves;}

    //setters
    void setLeave(int leave, TreeNode *newLeave);
    void setLeaves(vector<TreeNode<A>*> newLeaves);
    void setParent(TreeNode<A> *newParent){this->parent = newParent;}

    //others
    void addLeave(TreeNode<A> *newNode);
    bool remove(int leave);
    void update(){n = leaves.size();}
};




template <class A>
TreeNode<A>::TreeNode(TreeNode<A> *newNode){
    if (newNode!=NULL){
        this->setData(newNode->getData());
        setLeaves(newNode->getLeaves());
        update();
    }
}


template <class A>
TreeNode<A>::TreeNode(A newData, vector<TreeNode<A>*> newLeaves, TreeNode<A> *newParent) : Node<A>(newData){
    setParent(newParent);
    setLeaves(newLeaves);
    update();
}


//setters

template <class A>
void TreeNode<A>::setLeave(int leave, TreeNode *newLeave){
    if (leave < n)
        this->leaves.at(leave) = newLeave;

    update();
}

template <class A>
void TreeNode<A>::setLeaves(vector<TreeNode<A> *> newLeaves){
    this->leaves = newLeaves;
    update();
}

template <class A>
void TreeNode<A>::addLeave(TreeNode<A> *newNode){
    leaves.push_back(newNode);
    update();
}

template <class A>
bool TreeNode<A>::remove(int leave){
    if (leave >= leaves.size())
        return false;

    TreeNode<A> *aux = leaves.at(leave);
    leaves.erase(leaves.begin()+leave);
    if (aux != NULL)
        delete aux;

    update();
    return true;
}

#endif // TREENODE_H
