#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "BinaryNode.h"
#include "MyPrintOptions.h"
#include "List.h"
#include "Stack.h"
#include "Fifo.h"



#define PRE 0
#define IN 1
#define POS 2
#define MAX_HEIGHT 42
#define DEEP_SEARCH 0
#define WIDTH_SEARCH 1
#define BINARY_SEARCH 2
#define SMALLEST 0
#define LARGEST 1
#define TERMINAL_COLUMNS 80
#define STANDART_CHARACTER '_'

template < class A>
class BinaryTree
{
protected:
    BinaryNode<A> *root;
    BinaryNode<A> *pointer;
    int height;
    int size;
    int maxHeight;
    int searchMethod;

    void increaseHeight(){height++;}
    void decreaseHeight(){height--;}
    void increaseSize(){size++;}
    void decreaseSize(){size--;}

    virtual void update(){height = getHeight(root);}
    int compare(A data1, A data2);
    int max(int a, int b){ return (a>b)? a : b;}
    bool removeNode(BinaryNode<A> *node);
    BinaryNode<A> *sortedVectorToBinaryTree(A *v, int start, int end, BinaryNode<A> *father);


public:
    BinaryTree();
    BinaryTree(BinaryNode<A> *newRoot);
    BinaryTree(BinaryTree<A> *newBinaryTree);

    //getters
    static int getDegree(){return 2;}
    int getHeight(){return height;}
    int getHeight(BinaryNode<A> *startNode);
    int getMaxHeight(){return this->maxHeight;}
    int getSize(){return this->size;}
    int getSearchMethod(){return this->searchMethod;}
    bool isBalanced(BinaryNode<A> *startNode);

    BinaryNode<A> *getRoot(){return this->root;}
    BinaryNode<A> *getNode(A elem);
    BinaryNode<A> *getNode(int target, BinaryNode<A> *startNode);


    //setters
    void setMaxHeight(int max){this->maxHeight = max;}
    void setRoot(BinaryNode<A> *newRoot);
    void setRoot(A newData);
    void setSearchMethod(int method){this->searchMethod = method;}


    //others
    void destroy();
    void erase();
    void removeAll(BinaryNode<A> *node);
    void reOrganizeBinaryTree();
    void printInOrder(string separator, BinaryNode<A> *node);
    void printPreOrder(string separator, BinaryNode<A> *node);
    void printPosOrder(string separator, BinaryNode<A> *node);
    void printWidth();
    bool contain(A elem);
    bool isEmpty();
    bool isEqual(BinaryTree *t);
    bool addNode(A elem);
    bool addNode(BinaryNode<A> *newNode);
    bool remove(A elem);



    A *BinaryTreeToDataVector();
    A *BinaryTreeToSortedDataVector();
    vector<A> BinaryTreeToVector();
    List<A> BinaryTreeToList();
    BinaryNode<A> *deepSearch(A elem, BinaryNode<A> * startNode);
    BinaryNode<A> *widthSearch(A elem);
    BinaryNode<A> *binarySearch(A elem);
    BinaryNode<A> *sortedVectorToBinaryTree(A *v, int size);


    void   operator << (A data){
        addNode(data);
    }

    void  operator += (List<A> & l)
    {
        for(int i = 0; i < l.getSize(); i++)
            addNode(l.get(i).getData);
    }

    void  operator += (BinaryTree<A> & t)
    {
        List<A> l = t.BinaryTreeToList();

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
        case IN:
            printInOrder('\t', root);
            break;
        default:
            break;
        }
    }

    bool  operator > (const BinaryTree<A> &t){
        return (this->size > t.getSize());
    }
    bool  operator <(const BinaryTree<A> &t){
        return (this->size < t.getSize());
    }
    bool  operator == ( BinaryTree<A> &t){
        return isEqual(&t);
    }


};

//construtors
template <class A>
BinaryTree<A>::BinaryTree(){
    root = new BinaryNode<A>;
    pointer = root;
    height = 0;
    size = 0;
    maxHeight = MAX_HEIGHT;
    searchMethod = BINARY_SEARCH;

}

template <class A>
BinaryTree<A>::BinaryTree(BinaryNode<A> *newRoot){
    root = newRoot;
    pointer = root;
    height = 0;
    size = 1;
    maxHeight = MAX_HEIGHT;
    searchMethod = BINARY_SEARCH;
}


template <class A>
BinaryTree<A>::BinaryTree(BinaryTree<A> *newBinaryTree){
    if (newBinaryTree == NULL || newBinaryTree->getRoot() == NULL) return;

    root = new BinaryNode<A>(newBinaryTree->getRoot());
    vector<A> aux = newBinaryTree->BinaryTreeToVector();
    pointer = root;
    maxHeight = newBinaryTree->getMaxHeight();
    this->
    searchMethod = BINARY_SEARCH;

    for (int i = 1; i < newBinaryTree->getSize(); i++)
        addNode(aux.at(i));
}



//getters
template <class A>
BinaryNode<A> *BinaryTree<A>::getNode(A elem){
    pointer = root;
    switch (searchMethod) {
    case DEEP_SEARCH:
        return deepSearch(elem, pointer);
        break;
    case BINARY_SEARCH:
        return binarySearch(elem);
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
BinaryNode<A> *BinaryTree<A>::getNode(int target, BinaryNode<A> *startNode){
    pointer = startNode;
    if (startNode==NULL)
        return NULL;

    switch (target) {
    case SMALLEST:
        while(pointer->getLeft()!=NULL)
            pointer = pointer->getLeft();
        break;
    case LARGEST:
        while(pointer->getRight()!=NULL)
            pointer = pointer->getRight();
        break;
    default:
        break;
    }
    return pointer;
}

template <class A>
bool BinaryTree<A>::isBalanced(BinaryNode<A> *startNode){
    int leftH, rightH;
    if (size>1 || startNode !=NULL){
        leftH = getHeight(startNode->getLeft());
        rightH = getHeight(startNode->getRight());
        return (abs(leftH - rightH) <= 1 && isBalanced(startNode->getLeft()) && isBalanced(startNode->getRight()));
    }

    return true;
}

template <class A>
int BinaryTree<A>::getHeight(BinaryNode<A> *startNode){
    return (startNode!=NULL && size > 0)? 1 + max(getHeight(startNode->getLeft()), getHeight(startNode->getRight())): 0;
}

//setters
template <class A>
void BinaryTree<A>::setRoot(BinaryNode<A> *newRoot){
    root->setData(newRoot->getData());
    root->setLeft(newRoot->getLeft());
    root->setRight(newRoot->getRight());
}

template <class A>
void BinaryTree<A>::setRoot(A newData){
    erase();
    root->setData(newData);

}


//others
template <class A>
void BinaryTree<A>::destroy(){
    erase();
    delete root;
}

template <class A>
void BinaryTree<A>::erase(){
    removeAll(root);
    root = new BinaryNode<A>();
    pointer = root;
    height = 0;
    size = 0;
    maxHeight = MAX_HEIGHT;
    searchMethod = BINARY_SEARCH;

}

template <class A>
void BinaryTree<A>::removeAll(BinaryNode<A> *node){
    if (node!=NULL){
        removeAll(node->getLeft());
        removeAll(node->getRight());
        delete node;
        size--;
    }
}

template <class A>
void BinaryTree<A>::printInOrder(string separator, BinaryNode<A>*node){
    if (node!=NULL && size > 0){
        printInOrder(separator, node->getLeft());
        cout << node->getData() << separator;
        printInOrder(separator, node->getRight());
    }
}

template <class A>
void BinaryTree<A>::printPreOrder(string separator, BinaryNode<A> *node){
    if (node!=NULL && size > 0){
        cout << node->getData() << separator;
        printPreOrder(separator, node->getLeft());
        printPreOrder(separator, node->getRight());
    }
}

template <class A>
void BinaryTree<A>::printPosOrder(string separator, BinaryNode<A> *node){
    if (node!=NULL && size > 0){
        printPosOrder(separator, node->getLeft());
        printPosOrder(separator, node->getRight());
        cout << node->getData() << separator;
    }
}


template <class A>
void BinaryTree<A>::printWidth(){
    struct myStruct{
        BinaryNode<A>* node;
        int height;
    };

    int h, hMax, x, coef;
    int windowWidth = getTerminalColumns();
    Fifo<myStruct> myFifo(pow(2, height));
    myStruct s;
    s.height = 1;
    s.node = root;
    hMax = 0;
    myFifo.enqueue(s);

    if (windowWidth < 1 || windowWidth > TERMINAL_COLUMNS)
        windowWidth = TERMINAL_COLUMNS;

    setInputTextColor(COLOR_GREEN, true);
    cout << "\n\n";

    while (!myFifo.isEmpty() && size > 0){
        s = myFifo.dequeue();
        pointer = s.node;
        h = s.height;

        if (h > hMax){
            cout << endl;
            hMax = h;
            coef = 1;
        }else
            coef = 2;

        if (pointer==NULL){
            x = (coef)*windowWidth/(pow(2, h));
            for(int i = 0; i < x; i++)
                cout << " ";
            cout << STANDART_CHARACTER;

            if (h < height){
                s.height = h + 1;
                s.node = NULL;
                myFifo.enqueue(s);
                myFifo.enqueue(s);
            }

        }else{
            x = (coef)*windowWidth/(pow(2, h));
            for(int i = 0; i < x; i++)
                cout << " ";
            cout << pointer->getData();

            if(h<height){
                s.height = h+1;
                s.node = pointer->getLeft();
                myFifo.enqueue(s);
                s.node = pointer->getRight();
                myFifo.enqueue(s);
            }
        }
    }
    setInputTextColor(COLOR_DEFAULT, false);
}


template <class A>
bool BinaryTree<A>::contain(A elem){
    return (getNode(elem)!=NULL);
}


template <class A>
int BinaryTree<A>::compare(A data1, A data2){
    return (data1 - data2);
}

template <>
int BinaryTree<char*>::compare(char* data1, char* data2){
    return strcmp(data1, data2);
}

template <>
int BinaryTree<string>::compare(string data1, string data2){
    return strcmp(data1.c_str(), data2.c_str());
}

template <class A>
void BinaryTree<A>::reOrganizeBinaryTree(){

    int n = size;
    if(!isBalanced(root)){
        A *v = BinaryTreeToSortedDataVector();
        this->erase();
        root = sortedVectorToBinaryTree(v, n);
    }
    update();
}

template <class A>
bool BinaryTree<A>::isEmpty(){
    return ((size>0)? false: true);
}

template <class A>
bool BinaryTree<A>::isEqual(BinaryTree *t){
    if (t->size != size)
        return false;
    A *v1, *v2;
    v1 = BinaryTreeToDataVector();
    v2 = t->BinaryTreeToDataVector();
    for(int i = 0; i < size; i++){
        if (compare(v1[i], v2[i])!=0)
            return false;
    }
    return true;
}

template <class A>
bool BinaryTree<A>::remove(A elem){

    bool success;
    switch (searchMethod) {
    case DEEP_SEARCH:
        pointer = deepSearch(elem, root);
        break;
    case BINARY_SEARCH:
        pointer = binarySearch(elem);
        break;
    case WIDTH_SEARCH:
        pointer = widthSearch(elem);
        break;
    default:
        break;
    }

    success = removeNode(pointer);
    update();
    return success;
}

template <class A>
bool BinaryTree<A>::removeNode(BinaryNode<A> *node){
    BinaryNode<A> *aux, *father;

    if (node!=NULL){
        father = node->getParent();

        switch (node->getN()) {
        case 0:
            if (node==root){
                erase();
                pointer = root;
                return true;
            }else if (father->getRight()==node)
                father->setRight(NULL);
            else
                father->setLeft(NULL);

            pointer = father;
            delete node;
            decreaseSize();

            return true;
            break;
        case 2:
            aux = getNode(LARGEST, node->getLeft());
            node->setData(aux->getData());
            break;
        default: // case 1
            aux = getNode(LARGEST, node->getLeft());
            if (aux==NULL)
                aux = getNode(SMALLEST, node->getRight());

            node->setData(aux->getData());
            break;
        }
        return removeNode(aux);;
    }else
        return false;
}


template <class A>
bool BinaryTree<A>::addNode(A elem){
    Stack<BinaryNode<A>*> myStack(size);
    int diff;
    BinaryNode<A> *newNode;


    if (size==0){
        setRoot(elem);
        increaseSize();
        return true;
    }
    else{

        myStack.push(root);

        while(!myStack.isEmpty()){
            pointer = myStack.pop();
            diff = compare(elem, pointer->getData());

            if (diff > 0){
                if (pointer->getRight()!=NULL)
                    myStack.push(pointer->getRight());
                else{
                    newNode = new BinaryNode<A>;
                    newNode->setData(elem);
                    newNode->setParent(pointer);
                    pointer->setRight(newNode);
                    increaseSize();
                    update();
                    return true;
                }
            }
            else if (diff < 0){
                if (pointer->getLeft()!=NULL)
                    myStack.push(pointer->getLeft());
                else{
                    newNode = new BinaryNode<A>;
                    newNode->setData(elem);
                    newNode->setParent(pointer);
                    pointer->setLeft(newNode);
                    increaseSize();
                    update();
                    return true;
                }
            }
            else
                break;

        }
    }

    return false;
}

template <class A>
bool BinaryTree<A>::addNode(BinaryNode<A> *newNode){
    Stack<BinaryNode<A>*> myStack(size);
    int diff;

    if (size==0){
        setRoot(newNode);
        increaseSize();
        return true;
    }
    else{

        myStack.push(root);

        while(!myStack.isEmpty()){
            pointer = myStack.pop();
            diff = compare(newNode->getData(), pointer->getData());

            if (diff > 0){
                if (pointer->getRight()!=NULL)
                    myStack.push(pointer->getRight());
                else{
                    newNode->setParent(pointer);
                    pointer->setRight(newNode);
                    increaseSize();
                    update();
                    return true;
                }
            }
            else if (diff < 0){
                if (pointer->getLeft()!=NULL)
                    myStack.push(pointer->getLeft());
                else{
                    newNode->setParent(pointer);
                    pointer->setLeft(newNode);
                    increaseSize();
                    update();
                    return true;
                }
            }
            else
                break;

        }
    }

    return false;
}

template <class A>
A *BinaryTree<A>::BinaryTreeToDataVector(){
    A *ans = new A[size];
    Fifo<BinaryNode<A>*> myFifo(size);
    int i = 1;

    ans[0] = root->getData();

    pointer = root;
    while (i < size){
        if (pointer->getLeft()!=NULL){
            ans[i++] = pointer->getLeft->getData();
            myFifo.enqueue(pointer->getLeft);
        }
        if (pointer->getRight()!=NULL){
            ans[i++] = pointer->getRight->getData();
            myFifo.enqueue(pointer->getRight);
        }

        pointer = myFifo.dequeue();
    }


    return ans;
}

template <class A>
A *BinaryTree<A>::BinaryTreeToSortedDataVector(){
    A *ans = new A[size];
    Stack<BinaryNode<A>*> myStack(size);
    int i = 0;
    pointer = root;
    while (true){
        if (pointer->getLeft()!=NULL){
            myStack.push(pointer);
            pointer = pointer->getLeft();

        } else if (pointer->getRight()!=NULL){
            ans[i++] = pointer->getData();
            pointer = pointer->getRight();
        }
        else {
            ans[i++] = pointer->getData();

            do {
                try{
                    pointer = myStack.pop();
                }
                catch(int e){
                    return ans;
                }
                ans[i++] = pointer->getData();
                pointer = pointer->getRight();
            } while (pointer==NULL);


        }
    }


    return ans;
}


template <class A>
vector<A> BinaryTree<A>::BinaryTreeToVector(){
    A *aux = new A[size];
    vector<A> ans;

    aux = BinaryTreeToDataVector();

    for (int i = 0; i < size; i++)
        ans.push_back(aux[i]);
    return ans;
}

template <class A>
List<A> BinaryTree<A>:: BinaryTreeToList(){
    A *aux = new A[size];
    List<A> ans = new List<A>();

    aux = BinaryTreeToDataVector();
    ans = ans.vectorToList(aux, true, size);
    return ans;
}


template <class A>
BinaryNode<A> *BinaryTree<A>::sortedVectorToBinaryTree(A *v, int size){
    return sortedVectorToBinaryTree(v, 0, size -1, NULL);
}

template <class A>
BinaryNode<A> *BinaryTree<A>::sortedVectorToBinaryTree(A *v, int start, int end, BinaryNode<A> *father){
    if (start > end)
        return NULL;

    int mid = start + (end - start)/2;
    BinaryNode<A> *newNode = new BinaryNode<A>;
    newNode->setData(v[mid]);
    newNode->setLeft(sortedVectorToBinaryTree(v, start, mid -1, newNode));
    newNode->setRight(sortedVectorToBinaryTree(v, mid + 1, end, newNode));
    newNode->setParent(father);
    increaseSize();
    return newNode;
}

template <class A>
BinaryNode<A> *BinaryTree<A>::deepSearch(A elem, BinaryNode<A> *startNode){
    if (startNode != NULL && size > 0){
        if (compare(elem, startNode->getData())==0)
            return startNode;

        deepSearch(elem, startNode->getLeft());
        deepSearch(elem, startNode->getRight());
    }
    return NULL;
}

template <class A>
BinaryNode<A> * BinaryTree<A>::widthSearch(A elem){
    Fifo<BinaryNode<A>*> myFifo(size);
    myFifo.enqueue(root);

    while (!myFifo.isEmpty() && size > 0){
        pointer = myFifo.dequeue();
        if (compare(pointer->getData(), elem)==0)
            return pointer;

        if(pointer->getLeft()!=NULL)
            myFifo.enqueue(pointer->getLeft());

        if(pointer->getRight()!=NULL)
            myFifo.enqueue(pointer->getRight());
    }
    return NULL;
}

template <class A>
BinaryNode<A> * BinaryTree<A>::binarySearch(A elem){
    Stack<BinaryNode<A>*> myStack(size);
    int diff;
    myStack.push(root);

    while(!myStack.isEmpty()){
        pointer = myStack.pop();
        diff = compare(elem, pointer->getData());
        if (diff < 0){
            if (pointer->getLeft()!=NULL){
                myStack.push(pointer->getLeft());
            }
            else break;
        }
        else if (diff > 0){
            if (pointer->getRight()!=NULL){
                myStack.push(pointer->getRight());
            }
            else break;
        }
        else
            return pointer;


    }
    return NULL;
}


#endif // BinaryTree_H
