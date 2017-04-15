#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <vector>
#include "List.h"
#include "Stack.h"
#include "Fifo.h"

#define PRE 0
#define POS 2
#define MAX_HEIGHT 42
#define DEEP_SEARCH 0
#define WIDTH_SEARCH 1
#define SMALLEST 0
#define LARGEST 1

template < class A>
class Tree
{
protected:
    TreeNode<A> *root;
    TreeNode<A> *pointer;
    int degree;
    int height;
    int size;
    int maxHeight;
    bool balance;
    int searchMethod;
    void increaseHeight(){height++;}
    void decreaseHeight(){height--;}
    void increaseSize(){size++;}
    void decreaseSize(){size--;}
    int compare(A data1, A data2);
    int findLeaveIndex(TreeNode<A> *father, TreeNode<A> *child);
    bool removeNode(TreeNode<A> *node);

public:
    Tree();
    Tree(TreeNode<A> *newRoot);
    Tree(vector<TreeNode<A>> newTree, int degree);
    Tree(Tree<A> *newTree);
    Tree(int degree);

    //getters
    int getDegree(){return this->degree;}
    int getHeight(){return this->height;}
    int getMaxHeight(){return this->maxHeight;}
    int getSize(){return this->size;}
    int getSearchMethod(){return this->searchMethod;}
    bool isBalanced();
    TreeNode<A> *getRoot(){return this->root;}
    TreeNode<A> *getNode(A elem);


    //setters
    void setMaxHeight(int max){this->maxHeight = max;}
    void setDegree(int newDegree){this->degree = newDegree;}
    void setRoot(TreeNode<A> *newRoot);
    void setRoot(A newData);
    void setSearchMethod(int method){this->searchMethod = method;}


    //others
    void destroy();
    void erase();
    void removeAll(TreeNode<A> *node);
    void printPreOrder(string separator, TreeNode<A> *node);
    void printPosOrder(string separator, TreeNode<A> *node);
    void printWidth(string separator);
    int contain(A elem, TreeNode<A> *startNode);
    int contain(TreeNode<A> *node, TreeNode<A> *startNode);
    bool reOrganizeTree(int *error, TreeNode<A> *startNode); // 0 : no errors  1 : maxHeight error
    bool isEmpty();
    bool isEqual(Tree *t);
    bool addNode(A elem);
    bool addNode(TreeNode<A> *newNode);
    bool remove(A elem);


    A *treeToDataVector();
    vector<A> treeToVector();
    List<A> treeToList();
    TreeNode<A> *deepSearch(A elem, TreeNode<A> * startNode);
    TreeNode<A> *widthSearch(A elem);

    void   operator << (A data){
        addNode(data);
    }

    void  operator += (List<A> & l)
    {
        for(int i = 0; i < l.getSize(); i++)
            addNode(l.get(i).getData);
    }

    void  operator += (Tree<A> & t)
    {
        List<A> l = t.treeToList();

        for(int i = 0; i < l.getSize(); i++)
            addNode(l.get(i).getData());
    }

    void  operator >> (const int order){
        switch (order) {
        case PRE:
            printPreOrder('\t', root);
            break;
        case POS:
            printPosOrder('\t', root);
            break;

        default:
            break;
        }
    }

    bool  operator > (const Tree<A> &t){
        return (this->size > t.getSize());
    }
    bool  operator <(const Tree<A> &t){
        return (this->size < t.getSize());
    }
    bool  operator == ( Tree<A> &t){
        return isEqual(&t);
    }


};

//construtors
template <class A>
Tree<A>::Tree(){
    root = new TreeNode<A>;

    pointer = root;
    height = 1;
    size = 0;
    maxHeight = MAX_HEIGHT;
    balance = false;
    searchMethod = DEEP_SEARCH;

}

template <class A>
Tree<A>::Tree(int degree){
    root = new TreeNode<A>;
    pointer = root;

    height = 1;
    size = 0;
    maxHeight = MAX_HEIGHT;
    balance = false;
    searchMethod = DEEP_SEARCH;
    this->degree = degree;

}

template <class A>
Tree<A>::Tree(TreeNode<A> *newRoot){
    root = newRoot;
    pointer = root;

    height = 1;
    size = 1;
    maxHeight = MAX_HEIGHT;
    balance = false;
    searchMethod = DEEP_SEARCH;
}

template <class A>
Tree<A>::Tree(vector<TreeNode<A>> newTree, int degree){
    if (newTree.size()==0 || newTree.at(0) == NULL) return;

    root = new TreeNode<A>(newTree.at(0).getData());
    pointer = root;

    maxHeight = MAX_HEIGHT;
    this->degree = degree;
    this->balance = isBalanced();
    searchMethod = DEEP_SEARCH;

    for (int i = 1; i < newTree.size(); i++)
        addNode(newTree.at(i));


}

template <class A>
Tree<A>::Tree(Tree<A> *newTree){
    if (newTree == NULL || newTree->getRoot() == NULL) return;

    root = new TreeNode<A>(newTree->getRoot());
    vector<A> aux = newTree->treeToVector();
    pointer = root;
    maxHeight = newTree->getMaxHeight();
    this->degree = newTree->getDegree();
    this->balance = newTree->isBalanced();
    searchMethod = newTree->getSearchMethod();

    for (int i = 1; i < newTree->getSize(); i++)
        addNode(aux.at(i));
}

//getters
template <class A>
TreeNode<A> *Tree<A>::getNode(A elem){
    pointer = root;
    switch (searchMethod) {
    case DEEP_SEARCH:
        return deepSearch(elem, pointer);
        break;
    case WIDTH_SEARCH:
        return widthSearch(elem);
        break;
    default:
        return NULL;
        break;
    }
}


template <class A>
bool Tree<A>::isBalanced(){
    return false;
}


//setters
template <class A>
void Tree<A>::setRoot(TreeNode<A> *newRoot){
    root->setData(newRoot->getData());
    root->setLeft(newRoot->getLeft());
    root->setRight(newRoot->getRight());
    root->setN(newRoot->getN());
    root->setLeaves(newRoot->getLeaves());

}

template <class A>
void Tree<A>::setRoot(A newData){
    erase();
    root->setData(newData);
}


//others
template <class A>
void Tree<A>::destroy(){
    erase();
    delete root;
}

template <class A>
void Tree<A>::erase(){
    pointer = root;
    for(int i = 0; i < root->getN(); i++){
        removeAll(pointer->getLeaves().at(i));
    }
    delete root;
    root = new TreeNode<A>();
    pointer = root;

    height = 1;
    size = 0;
    maxHeight = MAX_HEIGHT;
    balance = false;
    searchMethod = DEEP_SEARCH;

}

template <class A>
void Tree<A>::removeAll(TreeNode<A> *node){
    for(int i = 0; i < node->getN(); i++){
        removeAll(node->getLeaves().at(i));
    }
    delete node;
    size--;
}


template <class A>
void Tree<A>::printPreOrder(string separator, TreeNode<A> *node){
    if (node!=NULL && size > 0){
        cout << node->getData() << separator;
        for (int i = 0; i < node->getN(); i++)
            printPreOrder(separator, node->getLeave(i));
    }
}

template <class A>
void Tree<A>::printPosOrder(string separator, TreeNode<A> *node){
    if (node!=NULL && size > 0){
        for (int i = 0; i < node->getN(); i++)
            printPosOrder(separator, node->getLeave(i));
        cout << node->getData() << separator;
    }
}

template <class A>
void Tree<A>::printWidth(string separator){
    Fifo<TreeNode<A>*> myFifo(size);
    myFifo.enqueue(root);
    int h = 1, hMax = 1;
    TreeNode<A> *aux;

    while (!myFifo.isEmpty() && size > 0){
        pointer = myFifo.dequeue();
        aux = pointer;
        h = 1;
        while (aux!=root){
            h++;
            aux = aux->getParent();
        }
        if (h > hMax){
            cout << endl;
            hMax = h;
        }
        for (int i = 0; i < (degree*height)/h; i++)
            cout << separator;

        cout << pointer->getData();

        for(int j = 0; j < pointer->getN();j++){
            if (pointer->getLeave(j) != NULL){
                myFifo.enqueue(pointer->getLeave(j));
            }
        }
    }
}


template <class A>
int Tree<A>::contain(A elem, TreeNode<A> *startNode){
    Fifo<TreeNode<A>*> myFifo(size);
    int aux = 0;
    if (startNode==NULL) return 0;

    switch (searchMethod) {
    case DEEP_SEARCH:
        for(int i = 0; i < startNode->getN(); i++)
            aux += contain(elem, startNode->getLeave(i));
        if(compare(elem, startNode->getData())==0)
            aux++;
        break;
    case WIDTH_SEARCH:
        myFifo.enqueue(root);

        while (!myFifo.isEmpty()){
            pointer = myFifo.dequeue();
            for(int j = 0; j < pointer->getN();j++){
                if (pointer->getLeave(j) != NULL && compare(pointer->getLeave(j)->getData(), elem)==0)
                    aux++;
                myFifo.enqueue(pointer->getLeave(j));
            }
        }
        break;
    default:
        break;
    }

    return aux;
}

template <class A>
int Tree<A>::contain(TreeNode<A> *node, TreeNode<A> *startNode){
    Fifo<TreeNode<A>*> myFifo(size);
    A elem;
    int aux = 0;
    if (startNode==NULL || node == NULL) return 0;

    elem = node->getData();

    switch (searchMethod) {
    case DEEP_SEARCH:
        for(int i = 0; i < startNode->getN(); i++)
            aux += contain(elem, startNode->getLeave(i));
        if(compare(elem, startNode->getData())==0)
            aux++;
        break;
    case WIDTH_SEARCH:
        myFifo.enqueue(root);

        while (!myFifo.isEmpty()){
            pointer = myFifo.dequeue();
            for(int j = 0; j < pointer->getN();j++){
                if (pointer->getLeave(j) != NULL && compare(pointer->getLeave(j)->getData(), elem)==0)
                    aux++;
                myFifo.enqueue(pointer->getLeave(j));
            }
        }
        break;
    default:
        break;
    }
    return aux;
}



template <class A>
int Tree<A>::compare(A data1, A data2){
    return (data1 - data2);
}

template <>
int Tree<char*>::compare(char* data1, char* data2){
    return strcmp(data1, data2);
}

template <>
int Tree<string>::compare(string data1, string data2){
    return strcmp(data1.c_str(), data2.c_str());
}

template <class A>
bool Tree<A>::reOrganizeTree(int *error, TreeNode<A> *startNode){
    return false;
} // 0 : no errors  1 : maxHeight error

template <class A>
bool Tree<A>::isEmpty(){
    return ((size>0)? false: true);
}

template <class A>
bool Tree<A>::isEqual(Tree *t){
    if (t->size != size)
        return false;
    A *v1, *v2;
    v1 = treeToDataVector();
    v2 = t->treeToDataVector();
    for(int i = 0; i < size; i++){
        if (compare(v1[i], v2[i])!=0)
            return false;
    }
    return true;
}

template <class A>
bool Tree<A>::remove(A elem){
    if (searchMethod==DEEP_SEARCH)
        pointer = deepSearch(elem, root);
    else
        pointer = widthSearch(elem);

    if (pointer==NULL)
        return false;

    return removeNode(pointer);
}

template <class A>
bool Tree<A>::removeNode(TreeNode<A> *node){
    TreeNode<A> * father = node->getParent();
    int index;

    if (node->getN()>0){
        node->setData(node->getLeave(0)->getData());
        return removeNode(node->getLeave(0));
    }
    else {
        index = findLeaveIndex(father, node);
        if (index >= 0)
            father->remove(index);
        else
            delete root;
    }

    return true;

}


template <class A>
int Tree<A>::findLeaveIndex(TreeNode<A> *father, TreeNode<A> *child){
    int i;
    if (father == NULL || child == NULL)
        return -1;

    for (i = 0; i <father->getN(); i++)
        if (father->getLeave(i)==child)
            break;
    return i;
}

template <class A>
bool Tree<A>::addNode(A elem){

    if (size==0){
        setRoot(elem);
        increaseSize();
        return true;
    }
    else{
        Fifo<TreeNode<A>*> myFifo(size);
        myFifo.enqueue(root);

        while (!myFifo.isEmpty()){
            pointer = myFifo.dequeue();
            if (pointer->getN() < degree){
                increaseSize();
                if (size > pow(degree, height) - 1)
                    increaseHeight();

                TreeNode<A> * newNode = new TreeNode<A>(elem);
                newNode->setParent(pointer);
                pointer->addLeave(newNode);

                return true;
            }

            for(int j = 0; j < pointer->getN();j++){
                myFifo.enqueue(pointer->getLeave(j));
            }
        }


    }

    return false;
}

template <class A>
bool Tree<A>::addNode(TreeNode<A> *newNode){

    if (size==0){
        setRoot(newNode);
        return true;
    }
    else{

        Fifo<TreeNode<A>*> myFifo(size);
        myFifo.enqueue(root);

        while (!myFifo.isEmpty()){
            pointer = myFifo.dequeue();
            if (pointer->getN() < degree){
                if (size > pow(degree, height) - 1)
                    increaseHeight();
                newNode->setParent(pointer);
                newNode->setHeight(height);
                pointer->addLeave(newNode);
                increaseSize();

                return true;
            }

            for(int j = 0; j < pointer->getN();j++){
                myFifo.enqueue(pointer->getLeave(j));
            }
        }

    }

    return false;
}

template <class A>
A *Tree<A>::treeToDataVector(){
    A *ans = new A[size];
    Fifo<TreeNode<A>*> myFifo(size);
    int i = 1;

    ans[0] = root->getData();

    pointer = root;
    while (i < size){
        for(int j = 0; j < pointer->getN();j++){
            ans[i++] = pointer->getLeave(j)->getData();
            myFifo.enqueue(pointer->getLeave(j));
        }
        pointer = myFifo.dequeue();
    }


    return ans;
}

template <class A>
vector<A> Tree<A>::treeToVector(){
    A *aux = new A[size];
    vector<A> ans;

    aux = treeToDataVector();

    for (int i = 0; i < size; i++)
        ans.push_back(aux[i]);
    return ans;
}

template <class A>
List<A> Tree<A>:: treeToList(){
    A *aux = new A[size];
    List<A> ans = new List<A>();

    aux = treeToDataVector();
    ans = ans.vectorToList(aux, true, size);
    return ans;
}

template <class A>
TreeNode<A> *Tree<A>::deepSearch(A elem, TreeNode<A> *startNode){
    TreeNode<A> *aux;
    if (startNode != NULL && size > 0){
        if (compare(startNode->getData(), elem)==0)
            return startNode;
        for (int i = 0; i < startNode->getN(); i++){
            aux = deepSearch(elem, startNode->getLeave(i));
            if (aux != NULL)
                return aux;
        }
    }
    return NULL;
}

template <class A>
TreeNode<A> * Tree<A>::widthSearch(A elem){
    Fifo<TreeNode<A>*> myFifo(size);
    myFifo.enqueue(root);

    while (!myFifo.isEmpty() && size > 0){
        pointer = myFifo.dequeue();
        if (pointer != NULL && compare(pointer->getData(), elem)==0)
            return pointer;

        for(int j = 0; j < pointer->getN();j++){
            if (pointer->getLeave(j)!=NULL)
                myFifo.enqueue(pointer->getLeave(j));
        }
    }
    return NULL;
}




#endif // TREE_H
