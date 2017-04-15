#ifndef SEARCH_H
#define SEARCH_H
#include "List.h"

#define DEFAULT_MOD 93


template <class A>
class Search
{
private:
    static List<A> *hashTable;
    static int modValue;
    static A lastValue;
    static int lastPosition;
    static bool sorted;
    static void setLast(A newLastValue, int newLastPosition);
    static int generateKey(A data);
    static int estimatePos(A elem, int low, int high, A min, A max);



public:
    Search(bool sorted);

    static void setMod(int newModValue);
    static void setSorted(bool newSorted);
    static A getLastValue(){return lastValue;}
    static bool isSorted(){return sorted;}
    static int getLastPos(){return lastPosition;}
    static int getMod(){return modValue;}

    static List<A> *getHashTable(){return hashTable;}

    static List<A> *makeHash(A *v, int size);
    static List<A> *makeHash(List<A> *list);

    static int hash(A *v, A elem, int size, int modValue, int *steps);
    static int hash(A *v, A elem, int size, int modValue);
    static int hash(A *v,  A elem, int size);
    static int hash(List<A> *list,  A elem, int modValue, int *steps);
    static int hash(List<A> *list,  A elem, int modValue);
    static int hash(List<A> *list,  A elem);
    static int hash2(List<A> *HTable, A elem, int *steps);
    static int hash2(List<A> *HTable, A elem);

    static int binarySearch(List<A> *list,  A elem, int *steps);
    static int binarySearch(A *v,  A elem, int size, int *steps);
    static int binarySearch(List<A> list,  A elem);
    static int binarySearch(A *v,  A elem, int size);

    static int linearSearch(List<A> *list,  A elem, int *steps);
    static int linearSearch(A *v,  A elem, int size, int *steps);
    static int linearSearch(A *v,  A elem, int size);
    static int linearSearch(List<A> *list,  A elem);

    static int interpolationSearch(List<A> *list,  A elem, int *steps);
    static int interpolationSearch(A *v,  A elem, int size, int *steps);
    static int interpolationSearch(A *v,  A elem, int size);
    static int interpolationSearch(List<A> *list,  A elem);

    static void sort(A* v, int size);
    static void sort(List<A> *list);

    static bool isEqual(A data1, A data2);
    static double compare(A data1, A data2);

};

template <class A>
int Search<A>::modValue;

template <class A>
List<A> *Search<A>::hashTable;

template <class A>
A Search<A>:: lastValue;

template <class A>
int Search<A>::lastPosition;

template <class A>
bool Search<A>::sorted;

template <class A>
Search<A>::Search(bool sorted)
{
    setSorted(sorted);
    setMod(DEFAULT_MOD);
}

template <class A>
bool Search<A>::isEqual(A data1, A data2){
    return ((data1==data2)? true : false );
}

template <>
bool Search<char*>::isEqual(char *data1, char *data2){
    return ((strcmp(data1,data2)==0)? true : false);
}

template <class A>
double Search<A>::compare(A data1, A data2){
    return (data1-data2);
}

template <>
double Search<char*>::compare(char *data1, char *data2){
    return strcmp(data1, data2);
}

template <>
double Search<string>::compare(string data1, string data2){
    return strcmp(data1.c_str(),data2.c_str());
}



template <class A>
List<A>* Search<A>::makeHash(A *v, int size){
    int pos;
    hashTable = new List<A>[modValue];

    if (!isSorted()){
        sort (v, size);
    }

    for (int i = 0; i < size; i++){
        pos = generateKey(v[i]);
        hashTable[abs(pos)].insert(v[i]);
    }

    return hashTable;
}



template <class A>
List<A>* Search<A>::makeHash(List<A> *list){
    int pos;
    hashTable = new List<A>[modValue];

    if (!isSorted()){
        sort(list);
    }

    for (int i = 0; i < list->getSize(); i++){
        pos = generateKey(list->get(i).getData());
        hashTable[abs(pos)].insert(list->get(i).getData());
    }

    return hashTable;
}

template <class A>
void Search<A>::sort(A *v, int size){
    int max = v[0];
    for (int i = 0; i < size; i++)
        if ((int)(v[i])>max)
            max = (int)v[i];
    bucketSort(v,size, (int)max);
}

template <>
void Search<char>::sort(char *v, int size){
    radixSort(v,size, (int)MAX_CHAR);
}

template <>
void Search<char*>::sort(char **v, int size){
    mergeSort(v,size);
}

template <>
void Search<string>::sort(string *v, int size){
    char **str = new char*[size];
    for(int i = 0; i < size; i++)
        str[i] = new char[strlen(v[i].c_str())];

    mergeSort(str,size);

}

template <class A>
void Search<A>::sort(List<A> *list){
    list->sortList(true, BUCKET_SORT);
}

template <>
void Search<char*>::sort(List<char*> *list){
    list->sortList(true, MERGE_SORT);
}

template <>
void Search<string>::sort(List<string> *list){
    list->sortList(true, MERGE_SORT);
}


template <class A>
int Search<A>::generateKey(A data){
    return ((int)data)%modValue;
}

template <>
int Search<char*>::generateKey(char* data){
    int key = (int)data[0];
    return (key)%(modValue);
}

template <>
int Search<string>::generateKey(string data){
    return ((int)data[0])%modValue;
}

template < class A>
int Search<A>::estimatePos(A elem, int low, int high, A min, A max){
    return (low + ((int)(high-low)*((int)elem - (int)min)+1)/((int)max - (int)min+1));
}

template <>
int Search<char*>::estimatePos(char *elem, int low, int high, char *min, char *max){
    return (low + ((int)(high-low)*((int)elem[0]- (int)min[0])+1)/((int)max[0] - (int)min[0]+1));
}

template <>
int Search<string>::estimatePos(string elem, int low, int high, string min, string max){
    return (low + ((int)(high-low)*((int)elem[0]- (int)min[0])+1)/((int)max[0] - (int)min[0]+1));
}

template <class A>
void Search<A>::setMod(int newModValue){
    modValue = newModValue;
}

template <class A>
void Search<A>::setSorted(bool newSorted){
    sorted = newSorted;
}

template <class A>
void Search<A>::setLast(A newLastValue, int newLastPosition){
    lastPosition =  newLastPosition;
    lastValue = newLastValue;
}





// Searching
template <class A>
int Search<A>::hash(A *v, A elem, int size, int modValue, int *steps){
    setMod(modValue);
    makeHash(v, size);

    int pos = generateKey(elem);
    *steps += 1;
    int pos2 = binarySearch(&hashTable[abs(pos)], elem, steps);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}


template <class A>
int Search<A>::hash(A *v,  A elem, int size, int modValue){
    setMod(modValue);
    makeHash(v, size);

    int pos = generateKey(elem);
    int pos2 = binarySearch(hashTable[abs(pos)], elem);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}


template <class A>
int Search<A>::hash(A *v,  A elem, int size){
    makeHash(v,size);
    int pos = generateKey(elem);
    int pos2 = binarySearch(hashTable[abs(pos)], elem);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}

template <class A>
int Search<A>::hash(List<A> *list, A elem, int modValue, int *steps){
    setMod(modValue);
    makeHash(list);

    int pos = generateKey(elem);
    *steps += 1;
    int pos2 = binarySearch(&hashTable[abs(pos)], elem, steps);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}

template <class A>
int Search<A>::hash(List<A> *list,  A elem, int modValue){
    setMod(modValue);
    makeHash(list);

    int pos = generateKey(elem);
    int pos2 = binarySearch(&hashTable[abs(pos)], elem);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}

template <class A>
int Search<A>::hash(List<A> *list,  A elem){
    makeHash(list);
    int pos = generateKey(elem);
    int pos2 = binarySearch(&hashTable[abs(pos)], elem);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}

template <class A>
int Search<A>::hash2(List<A> *HTable, A elem, int *steps){
    int pos = generateKey(elem);
    *steps += 1;
    int pos2 = binarySearch(&HTable[abs(pos)], elem, steps);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}

template <class A>
int Search<A>::hash2(List<A> *HTable, A elem){
    int pos = generateKey(elem);
    int pos2 = binarySearch(&HTable[abs(pos)], elem);
    pos = (pos2!=ELEMENT_NOT_FOUND)?pos:ELEMENT_NOT_FOUND;
    setLast(elem, pos);
    return pos;
}


template <class A>
int Search<A>::binarySearch(List<A> *list,  A elem, int *steps){
    int begin = 0, end = list->getSize()-1, mid = (end)/2;
    if (!isSorted())
        sort(list);

    while (begin<=end){
        *steps += 1;
        int diff = compare(elem, list->get(mid).getData());
        if ( diff < 0)
            end = mid -1;
        else if (diff > 0)
            begin = mid + 1;
        else{
            setLast(elem, mid);
            return mid;
        }
        mid = (begin+end)/2;

    }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}

template <class A>
int Search<A>::binarySearch(A *v,  A elem, int size, int *steps){
    int begin = 0, end = size-1, mid = end/2;
    if (!isSorted())
        sort(v, size);

    while (begin<=end){
        *steps += 1;
        int diff = compare(elem, v[mid]);
        if ( diff < 0)
            end = mid -1;
        else if (diff > 0)
            begin = mid + 1;
        else{
            setLast(elem, mid);
            return mid;
        }
        mid = (begin+end)/2;

    }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}

template <class A>
int Search<A>::binarySearch(List<A> list,  A elem){
    int begin = 0, end = list.getSize() - 1, mid = end/2;

    if (!isSorted())
        sort(list);

    while (begin<=end){
        int diff = compare(elem, list.get(mid).getData());
        if ( diff < 0)
            end = mid -1;
        else if (diff > 0)
            begin = mid + 1;
        else{
            setLast(elem, mid);
            return mid;
        }
        mid = (begin+end)/2;
    }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}

template <class A>
int Search<A>::binarySearch(A *v,  A elem, int size){
    int begin = 0, end = size - 1, mid = end/2;

    if (!isSorted())
        sort(v, size);

    while (begin<=end){
        int diff = compare(elem, v[mid]);
        if ( diff < 0)
            end = mid -1;
        else if (diff > 0)
            begin = mid + 1;
        else{
            setLast(elem, mid);
            return mid;
        }
        mid = (begin+end)/2;
    }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}

template <class A>
int Search<A>::linearSearch(List<A> *list,  A elem, int *steps){
    int pos = list->getPos(elem, BEGIN);
    *steps = (pos!=ELEMENT_NOT_FOUND)? *steps + pos + 1 : *steps + list->getSize();
    setLast(elem, pos);
    return pos;

}

template <class A>
int Search<A>::linearSearch(A *v,  A elem, int size, int *steps){
    for(int i =0; i < size; i++){
        *steps += 1;
        if (isEqual(v[i], elem)){
            setLast(elem, i);
            return i;
        }
    }
    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}


template <class A>
int Search<A>::linearSearch(A *v,  A elem, int size){
    for(int i =0; i < size; i++)
        if (isEqual(v[i], elem)){
            setLast(elem, i);
            return i;
        }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}


template <class A>
int Search<A>::linearSearch(List<A> *list,  A elem){
    int pos = list->getPos(elem,BEGIN);
    setLast(elem, pos);
    return pos;
}

template <class A>
int Search<A>::interpolationSearch(List<A> *list,  A elem, int *steps){
    int low = 0, mid, high = list->getSize()-1;
    A aux;
    if (!isSorted())
        sort(list);
    if (compare(elem, list->get(low).getData()) < 0 || compare(elem, list->get(high).getData())>0){
        setLast(elem, ELEMENT_NOT_FOUND);
        return ELEMENT_NOT_FOUND;
    }

    while (low <= high){
        *steps += 1;
        mid = estimatePos(elem, low, high, list->get(low).getData(), list->get(high).getData());
        mid = (mid<0)? 0: (mid>high)? high: mid;
        aux = list->get(mid).getData();
        if (isEqual(aux, elem)){
            setLast(elem, mid);
            return mid;
        }
        else if (compare(aux, elem) < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}

template <class A>
int Search<A>::interpolationSearch(A *v,  A elem, int size, int *steps){
    int low = 0, mid, high = size-1;
    A aux;
    if (!isSorted())
        sort(v, size);
    if (compare(elem,v[low]) < 0 || compare(elem, v[high])>0){
        setLast(elem, ELEMENT_NOT_FOUND);
        return ELEMENT_NOT_FOUND;
    }

    while (low <= high){
        *steps += 1;
        mid = estimatePos(elem, low, high, v[low], v[high]);
        mid = (mid<0)? 0: (mid>high)? high: mid;
        aux = v[mid];
        if (isEqual(aux, elem)){
            setLast(elem, mid);
            return mid;
        }
        else if (compare(aux, elem) < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}


template <class A>
int Search<A>::interpolationSearch(A *v,  A elem, int size){
    int low = 0, mid, high = size-1;
    A aux;
    if (!isSorted())
        sort(v, size);

    if (compare(elem,v[low]) < 0 || compare(elem, v[high])>0){
        setLast(elem, ELEMENT_NOT_FOUND);
        return ELEMENT_NOT_FOUND;
    }

    while (low <= high){
        mid = estimatePos(elem, low, high, v[low], v[high]);
        mid = (mid<0)? 0: (mid>high)? high: mid;
        aux = v[mid];

        if (isEqual(aux, elem)){
            setLast(elem, mid);
            return mid;
        }
        else if (compare(aux, elem) < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}


template <class A>
int Search<A>::interpolationSearch(List<A> *list, A elem){
    int low = 0, mid, high = list->getSize()-1;
    A aux;
    if (!isSorted())
        sort(list);
    if (compare(elem, list->get(low).getData()) < 0 || compare(elem, list->get(high).getData())>0){
        setLast(elem, ELEMENT_NOT_FOUND);
        return ELEMENT_NOT_FOUND;
    }

    while (low <= high){
        mid = estimatePos(elem, low, high, list->get(low).getData(), list->get(high).getData());
        mid = (mid<0)? 0: (mid>high)? high: mid;
        aux = list->get(mid).getData();
        if (isEqual(aux, elem)){
            setLast(elem, mid);
            return mid;
        }
        else if (compare(aux, elem) < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }


    setLast(elem, ELEMENT_NOT_FOUND);
    return ELEMENT_NOT_FOUND;
}



#endif // SEARCH_H
