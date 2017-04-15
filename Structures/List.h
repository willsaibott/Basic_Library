#ifndef LIST_H
#define LIST_H
#include "ListNode.h"
#include "mySort.h"
#include <vector>

#define BUBBLE_SORT 0
#define QUICK_SORT 1
#define MERGE_SORT 2
#define INSERTION_SORT 4
#define HEAP_SORT 3
#define SELECTION_SORT 6
#define SHELL_SORT 8
#define RADIX_SORT 7
#define BUCKET_SORT 10
#define COUNTING_SORT 9
#define INTRO_SORT 5
#define END -1
#define END_CHAR '*'
#define END_STRING "*"
#define ALL -21
#define BEGIN 0
#define TYPE_INT 0
#define TYPE_CHAR 1
#define TYPE_STRING 2
#define TYPE_DOUBLE 3



template <class A>
class List
{
    ListNode<A> *firstNode;
    ListNode<A> *pointer;

    int size=0;

public:
    List(){firstNode = pointer = NULL;}
    ~List();
    A pattern;


    int getPos(A data, int start); // only the first element
    vector<int> getAllPos(A data); // all elements
    ListNode<A> * getFirst();
    int contain(A data);
    int getSize();
    node_position<A> getMin();
    node_position<A> getMax();
    bool isEmpty();
    bool isEqual(List<A> *l);
    ListNode<A> get(int pos);

    void sortList(bool isIncreasing, int sortAlgorithm);
    void insert(A newData);
    void insertPos(A, int pos);
    void setElement(A newData, int pos);
    bool remove(int pos);
    void printList(char separator);
    void printElement(int pos);
    void erase();
    void setAllTo(A newData);
    static void copyList(List<A> origList, List<A> *destList);

    A *listToVector();
    vector<A> listToCVector();
    static List<A> *vectorToListPointer(A *a, bool isIncreasing, int n);
    void vectorToList(A* a, int n);

    void   operator << (A data){
        insert(data);
    }


    void  operator <= (List<A> l)
    {
        this->erase();
        for(int i = 0; i < l.size; i++)
            insert(l.get(i).data);
    }

    void  operator += (List<A> & l)
    {
        for(int i = 0; i < l.size; i++)
            insert(l.get(i).data);
    }

    void  operator >> (const int pos){
        if (pos==ALL)
            printList('\t');
        else
            printElement(pos);

    }
    bool  operator > (const List<A> &l){
        return (this->size > l.size);
    }
    bool  operator < (const List<A> &l){
        return (this->size < l.size);
    }
    bool  operator == ( List<A> &l){
        return isEqual(&l);
    }

    A operator [](int i){
        if (i < this->size)
            return get(i).getData();
        else{
            cout << "\nList Error: index out of bounds.\n";
            throw(-1);

        }
    }




};

template <class A>
void List<A>::copyList(List<A> origList, List<A> *destList){
    ListNode<A> *aux = origList.getFirst();
    destList->erase();
    for (int i = 0; i < origList.size; i++){
        destList->insert(aux->getData());
        aux = aux->getNext();
    }
}


template <class A>
int List<A>::contain(A data){
    int count = 0;
    pointer = firstNode;
    for(int i = 0; i < this->size;i++){
        if(compare(pointer->getData(), data)==0)
            count++;
        pointer = pointer->getNext();
    }
    return count;
}



template <class A>
ListNode<A> List<A>::get(int pos){
    pointer = firstNode;
    if (pos < this->size){
        for(int i = 0; i < pos;i++)
            pointer = pointer->getNext();
        return pointer;
    }
    else
        return firstNode;
}


template <class A>
int List<A>::getPos(A data, int start){
    pointer = firstNode;
    for(int i = start; i< this->size; i++){
        if (compare(pointer->getData(), data)==0)
            return i;
        pointer = pointer->getNext();
    }

    return END;
}

template <class A>
vector<int> List<A>::getAllPos(A data){
    vector<int> pos;
    int i = 0;
    for(i = BEGIN; i < size; i++){
        i = getPos(data,i);
        if (i==END)
            return pos;
        pos.push_back(i);
    }
    return pos;
}


template <class A>
node_position<A> List<A>::getMin(){
    pointer = firstNode;
    A minValue = (size>0)? pointer->getData():(A)0;
    A lastMin = minValue;
    int pos = (size>0)? 0:-1;
    node_position<A> minNode;

    minNode.value = minValue;
    minNode.pos = pos;
    for(int i = 0; i < size;i++){
        minValue = (compare(pointer->getData(), minValue)<0)? pointer->getData():minValue;
        if (compare(lastMin, minValue)!=0){
            minNode.pos = i;
            minNode.value = minValue;
            lastMin = minValue;
        }
        pointer = pointer->getNext();
    }
    return minNode;

}


template <class A>
node_position<A> List<A>::getMax(){
    pointer = firstNode;
    A maxValue = (size>0)? pointer->getData():(A)0;
    A lastMax = maxValue;
    int pos = (size>0)? 0:-1;
    node_position<A> maxNode;

    maxNode.value = maxValue;
    maxNode.pos = pos;
    for(int i = 0; i < size;i++){
        maxValue = (compare(pointer->getData(), maxValue)>0)? pointer->getData(): maxValue;
        if (compare(lastMax, maxValue)!=0){
            maxNode.pos = i;
            maxNode.value = maxValue;
            lastMax = maxValue;
        }
        pointer = pointer->getNext();
    }
    return maxNode;
}


template <class A>
int List<A>::getSize(){
    return size;
}

template <class A>
bool List<A>::isEmpty(){
    return (getSize() > 0) ? true : false;
}

template <class A>
List<A>::~List(){
    //erase();
}

template <class A>
ListNode<A> * List<A>::getFirst(){
    return this->firstNode;
}

template <class A>
void sort(int sortAlgorithm, A *a, int n){

    A max = a[0];

    switch(sortAlgorithm){

    case BUBBLE_SORT:
        bubbleSort(a, n);
        break;
    case QUICK_SORT:
        quickSort(a, 0, n-1);
        break;
    case MERGE_SORT:
        mergeSort(a, n);
        break;
    case INSERTION_SORT:
        insertionSort(a, n);
        break;
    case HEAP_SORT:
        heapSort(a, n);
        break;
    case SELECTION_SORT:
        selectionSort(a, n);
        break;
    case SHELL_SORT:
        shellSort(a, n);
        break;
    case RADIX_SORT:
        for(int i = 0; i < n; i++)
            if (max < a[i])
                max = a[i];
        radixSort(a, n, (llong)max);
        break;
    case BUCKET_SORT:
        for(int i = 0; i < n; i++)
            if (max < a[i])
                max = a[i];
        bucketSort(a, n, (llong)max);
        break;
    case COUNTING_SORT:
        countingSort(a, n);
        break;
    case INTRO_SORT:
        for(int i = 0; i < n; i++)
            if (max < a[i])
                max = a[i];
        introSort(a, 0, n-1, (llong)max, n);
        break;
    default:
        break;
    }

}
void sort(int sortAlgorithm, double *a, int n){

    double max = a[0];

    switch(sortAlgorithm){

    case BUBBLE_SORT:
        bubbleSort(a, n);
        break;
    case QUICK_SORT:
        quickSort(a, 0, n-1);
        break;
    case MERGE_SORT:
        mergeSort(a, n);
        break;
    case INSERTION_SORT:
        insertionSort(a, n);
        break;
    case HEAP_SORT:
        heapSort(a, n);
        break;
    case SELECTION_SORT:
        selectionSort(a, n);
        break;
    case SHELL_SORT:
        shellSort(a, n);
        break;
    case BUCKET_SORT:
        for(int i = 0; i < n; i++)
            if (max < a[i])
                max = a[i];
        bucketSort(a, n,(int) max + 1);
        break;
    case INTRO_SORT:
        for(int i = 0; i < n; i++)
            if (max < a[i])
                max = a[i];
        introSort(a, 0, n-1, (llong)max+1, n);
        break;
    default:
        break;
    }

}
void sort(int sortAlgorithm, float *a, int n){

    float max = a[0];

    switch(sortAlgorithm){

    case BUBBLE_SORT:
        bubbleSort(a, n);
        break;
    case QUICK_SORT:
        quickSort(a, 0, n-1);
        break;
    case MERGE_SORT:
        mergeSort(a, n);
        break;
    case INSERTION_SORT:
        insertionSort(a, n);
        break;
    case HEAP_SORT:
        heapSort(a, n);
        break;
    case SELECTION_SORT:
        selectionSort(a, n);
        break;
    case SHELL_SORT:
        shellSort(a, n);
        break;
    case BUCKET_SORT:
        for(int i = 0; i < n; i++)
            if (max < a[i])
                max = a[i];
        bucketSort(a, n, max + 1);
        break;
    case INTRO_SORT:
        for(int i = 0; i < n; i++)
            if (max < a[i])
                max = a[i];
        introSort(a, 0, n-1, (llong)max+1, n);
        break;
    default:
        break;
    }

}
void sort(int sortAlgorithm, char *a, int n){

    char max = MAX_CHAR;
    switch(sortAlgorithm){

    case BUBBLE_SORT:
        bubbleSort(a, n);
        break;
    case QUICK_SORT:
        quickSort(a, 0, n-1);
        break;
    case MERGE_SORT:
        mergeSort(a, n);
        break;
    case INSERTION_SORT:
        insertionSort(a, n);
        break;
    case HEAP_SORT:
        heapSort(a, n);
        break;
    case SELECTION_SORT:
        selectionSort(a, n);
        break;
    case SHELL_SORT:
        shellSort(a, n);
        break;
    case RADIX_SORT:
        radixSort(a, n, (int)max);
        break;
    case BUCKET_SORT:
        bucketSort(a, n, (int)max);
        break;
    case COUNTING_SORT:
        countingSort(a, n);
        break;
    case INTRO_SORT:
        introSort(a, 0, n-1, (llong)max, n);
        break;
    default:
        break;
    }

}
void sort(int sortAlgorithm, char **a, int n){

    switch(sortAlgorithm){

    case BUBBLE_SORT:
        bubbleSort(a, n);
        break;
    case QUICK_SORT:
        quickSort(a, 0, n-1);
        break;
    case MERGE_SORT:
        mergeSort(a, n);
        break;
    case INSERTION_SORT:
        insertionSort(a, n);
        break;
    case HEAP_SORT:
        heapSort(a, n);
        break;
    case SELECTION_SORT:
        selectionSort(a, n);
        break;
    case SHELL_SORT:
        shellSort(a, n);
        break;
    case INTRO_SORT:
        introSort(a, 0, n-1, (llong)MAX_CHAR, n);
        break;
    default:
        break;
    }

}
void sort(int sortAlgorithm, string *v, int n){

    char **a = new char *[n];
    for(int i = 0; i < n;i++){
        a[i] = new char[strlen(v[i].c_str())+1];
        strcpy(a[i], v[i].c_str());
    }

    switch(sortAlgorithm){

    case BUBBLE_SORT:
        bubbleSort(a, n);
        break;
    case QUICK_SORT:
        quickSort(a, 0, n-1);
        break;
    case MERGE_SORT:
        mergeSort(a, n);
        break;
    case INSERTION_SORT:
        insertionSort(a, n);
        break;
    case HEAP_SORT:
        heapSort(a, n);
        break;
    case SELECTION_SORT:
        selectionSort(a, n);
        break;
    case SHELL_SORT:
        shellSort(a, n);
        break;
    case INTRO_SORT:
        introSort(a, 0, n-1, (llong)MAX_CHAR, n);
        break;
    default:
        break;
    }
    for (int i = 0; i < n; i++){
        v[i] = string(a[i]);
    }

}

template <class A>
void List<A>::sortList(bool isIncreasing, int sortAlgorithm){
    A *v;
    List<A> *aux;
    int n = this->size;
    v = this->listToVector();
    erase();
    sort(sortAlgorithm, v, n);
    aux = vectorToListPointer(v, isIncreasing, n);
    size = aux->size;
    firstNode = aux->firstNode;
    delete []v;
}

template <class A>
void List<A>::insert(A newData){
    ListNode<A> *aux = new ListNode<A>(newData);
    if (this->size == 0){
        firstNode = aux;
        size = 1;
    }
    else{
        pointer = firstNode;
        for(int i = 0; i < this->size-1; i++)
            pointer = pointer->getNext();
        aux->setPrev(pointer);
        pointer->setNext(aux);
        size++;
    }
}


template <class A>
void List<A>::insertPos(A newData, int pos){
    ListNode<A> *aux = new ListNode<A>(newData);

    if (this->size == 0){
        firstNode = aux;
        size = 1;
    }
    else if (pos == BEGIN){
        pointer = firstNode;
        aux->setNext(firstNode);
        firstNode->setPrev(aux);
        firstNode = aux;
        size++;
    }
    else if (pos == END || pos == this->size -1){
        insert(newData);
    }
    else if (pos < this->size){
        pointer = firstNode;
        for(int i = 0; i < pos; i++)
            pointer = pointer->getNext();
        aux->setNext(pointer);
        aux->setPrev(pointer->getPrev());
        pointer->getPrev()->setNext(aux);
        pointer->setPrev(aux);

        size++;
    }
}

template <class A>
void List<A>::setElement(A newData, int pos){
    pointer = firstNode;
    if (pos < this->size){
        for(int i = 0; i < pos; i++)
            pointer = pointer->getNext();
        pointer->setData(newData);
    }
}

template <class A>
bool List<A>::remove(int pos){
    pointer = firstNode;

    if (pos==BEGIN){
        if(size>1){
            firstNode = firstNode->getNext();
            firstNode->setPrev(NULL);

            delete pointer;
            size--;
        }
        else{
            firstNode = NULL;
            delete pointer;
            size = 0;
        }

        return true;
    }
    else if (pos < this->size){
        for(int i = 0; i < pos; i++)
            pointer = pointer->getNext();

        if (pos!=this->size -1){
            pointer->getPrev()->setNext(pointer->getNext());
            pointer->getNext()->setPrev(pointer->getPrev());
        }
        else
            pointer->getPrev()->setNext(NULL);
        delete pointer;
        size--;
        return true;
    }

    return false;
}


template <class A>
void List<A>::printList(char separator){
    pointer = firstNode;
    cout << "\nList: \n" <<  endl;
    for(int i = 0; i < this->size; i++){
        cout << pointer->getData() << separator;
        pointer = pointer ->getNext();
    }
}

template <class A>
void List<A>::printElement(int pos){
    pointer = firstNode;
    if (pos < this->size){
        for(int i = 0; i < pos; i++)
            pointer = pointer->getNext();

        cout << pointer->getData();
    }
}

template <class A>
void List<A>::erase(){
    //cout << "\nList Destructor Called";
    pointer = firstNode;
    while(this->size>0){
        remove(BEGIN);
    }
}

template <class A>
void List<A>::setAllTo(A newData){
    pointer = firstNode;
    for(int i = 0; i < this->size; i++){
        pointer->setData(newData);
        pointer = pointer->getNext();
    }
}

template <class A>
A * List<A>::listToVector(){
    A *ans = new A [this->size]();
    pointer = firstNode;
    for(int i = 0; i < size; i++){
        ans[i] = (pointer->getData());
        pointer = pointer->getNext();
    }

    return ans;
}



template <class A>
vector<A> List<A>::listToCVector(){
    vector<A> ans;
    pointer = this->firstNode;

    for(int i = 0; i < size; i++){
        ans.push_back(pointer->getData());
        pointer = pointer->getNext();
    }

    return ans;
}

template <class A>
List<A> *List<A>::vectorToListPointer(A *a, bool isIncreasing, int n){

    List<A> *aux = new List<A>();
    if (isIncreasing){
        for(int i = 0; i < n; i++)
            aux->insert(a[i]);
    }
    else{
        for(int i = 0; i < n; i++)
            aux->insertPos(a[i], BEGIN);
    }
    return aux;
}

template <class A>
bool List<A>::isEqual(List<A> *l){
    if (size!=l->getSize())
        return false;
    for(int i = 0; i < size; i++){
        if(get(i).getData()!=l->get(i).getData())
            return false;
    }
    return true;
}

template <>
bool List<char*>::isEqual(List<char*> *l){
    if (size!=l->getSize())
        return false;
    for(int i = 0; i < size; i++){
        if(strcmp(get(i).getData(),l->get(i).getData())!=0)
            return false;
    }
    return true;
}

template <class A>
void List<A>::vectorToList(A *a, int n){
    for (int i = 0; i < n; i++)
        this->insert(a[i]);
}

#endif // LIST_H
