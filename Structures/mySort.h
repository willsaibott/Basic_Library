
#ifndef MYSORT_H
#define MYSORT_H

/*
 *  Author: Guilherme de Novais Bordignon
 *  date: 04/11/2015
 *
 *  Sort Algorithms in c++
 *
 *
 * */
#include "Basic.h"

using namespace std;

#define MAX_COUNTING 1024
#define MAX_CHAR '~'


template <class A>
void bubbleSort(A *a, int n){
    A aux;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1; j++){
            if(Value<A>::compare(a[j], a[j+1])>0){
                aux = a[j+1];
                a[j+1] = a[j];
                a[j] = aux;
            }
        }
    }
}


void bubbleSort( char *a[], int n){
    char *aux;
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < n-1; j++){
            if(strcmp(a[j],a[j+1])>0){
                aux = new char[strlen(a[j+1])+1];
                strcpy(aux,a[j+1]);
                delete[] a[j+1];
                a[j+1] = new char[strlen(a[j])+1];
                strcpy(a[j+1],a[j]);
                delete[] a[j];
                a[j] = new char[strlen(aux) + 1];
                strcpy(a[j],aux);
                delete[] aux;
            }
        }
    }

}

template <class A>
void quickSort(A *a, int begin, int end){
    int up = end, low = begin+1, key = begin;
    A aux;

    if (end<1 || key == up)
        return;

    while(Value<A>::compare(a[low], a[key]) <= 0 && low < up)
        low++;
    while(Value<A>::compare(a[up], a[key]) > 0)
        up--;

    if (up>key){

        aux = a[key];
        a[key] = a[up];
        a[up] = aux;

        quickSort(a, begin, up - 1);
    }

    quickSort(a, low, end);

}

void quickSort(char **a, int begin, int end){
    int up = end, low = begin+1, key = begin;
    char* aux;

    if (end<1 || key == up)
        return;

    while(strcmp(a[low], a[key]) <= 0 && low < up)
        low++;

    while(strcmp(a[up],a[key]) > 0)
        up--;


    if (up>key){
        aux = new char[strlen(a[key])+1];
        strcpy(aux, a[key]);
        delete[] a[key];
        a[key] = new char[strlen(a[up])+1];
        strcpy(a[key],a[up]);
        delete[] a[up];
        a[up] = new char[strlen(aux)+1];
        strcpy(a[up],aux);
        delete []aux;

        quickSort(a, begin, up - 1);
    }

    quickSort(a, low, end);

}

template <class A>
void mergeSort(A *a, int n){
    int size = 1, l1, l2, u1, u2, k, i , j;
    A *aux = new A[n];

    while(size<n){
        l1 = k = 0;

        while(l1+size < n){
            l2 = l1 + size;
            u1 = l2 -1;
            if (l2+size-1<n)
                u2 = l2+size-1;
            else
                u2 = n-1;

            i = l1;
            j = l2;
            while(i <= u1 && j <= u2){
                if (Value<A>::compare(a[i], a[j]) <= 0)
                    aux[k++] = a[i++];
                else
                    aux[k++] = a[j++];

            }
            while (i <= u1)
                aux[k++] = a[i++];
            while (j <= u2)
                aux[k++] = a[j++];


            l1 = u2+1;

        }

        for (i = l1; i < n; i++){
            aux[k++] = a[i];
        }
        for (i = 0; i < l1; i++){
            a[i] = aux[i];
        }
        size *= 2;
    }

    delete []aux;

}

void mergeSort(char **a, int n){
    int size = 1, l1, l2, u1, u2, k, i , j;
    char **aux = new char*[n];

    while(size<n){
        l1 = k = 0;

        while(l1+size < n){
            l2 = l1 + size;
            u1 = l2 -1;
            if (l2+size-1<n)
                u2 = l2+size-1;
            else
                u2 = n-1;

            i = l1;
            j = l2;
            while(i <= u1 && j <= u2){
                if (strcmp(a[i] ,a[j])<=0){
                    aux[k] = new char[strlen(a[i])+1];
                    strcpy(aux[k++], a[i++]);
                }
                else{
                    aux[k] = new char[strlen(a[j])+1];
                    strcpy(aux[k++], a[j++]);
                }

            }
            while (i <= u1){
                aux[k] = new char[strlen(a[i])+1];
                strcpy(aux[k++], a[i++]);
            }
            while (j <= u2){
                aux[k] = new char[strlen(a[j])+1];
                strcpy(aux[k++], a[j++]);
            }


            l1 = u2+1;

        }

        for (i = l1; i < n; i++){
            aux[k] = new char[strlen(a[i])+1];
            strcpy(aux[k++], a[i]);
        }
        for (i = 0; i < l1; i++){
            delete[]a[i];
            a[i] = new char[strlen(aux[i])+1];
            strcpy(a[i], aux[i]);
        }
        size *= 2;
    }


    for (i=0;i<n;i++)
        delete []aux[i];
    delete []aux;
}

template <class A>
void heapSort(  A *a, int n){
    int i = n/2, dad, sun;
    A aux;

    while (true){
        if( i > 0)
            aux = a[--i];
        else{
            n--;
            if(n==0)
                return;

            aux = a[n];
            a[n] = a[0];
        }

        dad = i;
        sun = 2*dad + 1;


        while (sun<n){
            if(sun+1<n && Value<A>::compare(a[sun+1], a[sun])> 0)
                sun++;
            if(Value<A>::compare(a[sun],aux)>0){
                a[dad] = a[sun];
                dad=sun;
                sun=dad*2+1;
            }
            else
                break;

        }
        a[dad] = aux;

    }


}

void heapSort( char **a, int n){
    int i = n/2, dad, sun;
    char *aux = new char;

    while (true){
        if( i > 0){
            aux = new char[strlen(a[i]) + 1];
            strcpy(aux, a[--i]);
        }
        else{
            n--;
            if(n==0)
                return;
            aux = new char[strlen(a[n]) + 1];
            strcpy(aux,a[n]);
            delete [] a[n];
            a[n] = new char[strlen(a[0]) + 1];
            strcpy(a[n],a[0]);
        }

        dad = i;
        sun = 2*dad + 1;

        while (sun<n){
            if(sun+1<n && strcmp(a[sun+1], a[sun])>0)
                sun++;
            if(strcmp(a[sun],aux)>0){
                delete [] a[dad];
                a[dad] = new char[strlen(a[sun]) + 1];
                strcpy(a[dad], a[sun]);
                dad=sun;
                sun=dad*2+1;
            }
            else
                break;

        }
        delete [] a[dad];
        a[dad] = new char[strlen(aux) + 1];
        strcpy(a[dad], aux);

        delete []aux;
    }

}
template <class A>
void insertionSort(  A *a, int n){
    int i, j;
    A aux;

    for(i=1;i<n;i++){
        aux = a[i];
        for(j = i-1; j >= 0 && Value<A>::compare(aux, a[j])<0; j--){
            a[j+1] = a[j];
        }
        a[j+1] = aux;
    }

}

void insertionSort( char **a, int n){
    int i, j;
    char *aux;

    for(i=1;i<n;i++){
        aux = new char[strlen(a[i]) + 1];
        strcpy(aux,a[i]);
        for(j = i-1; j >= 0 && strcmp(aux , a[j])<0; j--){
            delete [] a[j+1];
            a[j+1] = new char[strlen(a[j]) + 1];
            strcpy(a[j+1],a[j]);
        }
        delete [] a[j+1];
        a[j+1] = new char[strlen(aux) + 1];
        strcpy(a[j+1], aux);
        delete[] aux;
    }
}

template <class A>
void introSort(A *a, int begin, int end, llong max, int n){
    int up = end, low = begin+1, key = begin;
    A aux;

    if (end<1 || key == up)
        return;
    else if(max==0)
        heapSort(a,n);
    else{

        while(Value<A>::compare(a[low], a[key])<=0 && low < up)
            low++;
        while(Value<A>::compare(a[up], a[key])>0)
            up--;

        if (up>key){

            aux = a[key];
            a[key] = a[up];
            a[up] = aux;

            introSort(a, begin, up - 1 , (max-1), n);
        }

        introSort(a, low, end, (max-1), n);
    }
}

void introSort(char **a, int begin, int end, llong max, int n){
    int up = end, low = begin+1, key = begin;
    char* aux;

    if (end<1 || key == up)
        return;
    else if (max==0)
        heapSort(a,n);
    else{

        while(strcmp(a[low],a[key]) <= 0 && low < up)
            low++;
        while(strcmp(a[up],a[key]) > 0)
            up--;

        if (up>key){
            aux = new char[strlen(a[key]) + 1];
            strcpy(aux,a[key]);
            delete[] a[key];
            a[key] = new char[strlen(a[up]) + 1];
            strcpy(a[key],a[up]);
            delete[] a[up];
            a[up] = new char[strlen(aux)+1];
            strcpy(a[up], aux);
            delete[] aux;

            introSort(a, begin, up - 1, max-1, n);
        }

        introSort(a, low, end, max-1, n);
    }

}

template <class A>
void selectionSort(A *a, int n){
    int min = 0, j = 0;
    A aux;

    while(min < n){

        for(int i = j; i < n; i++)
            if(Value<A>::compare(a[min], a[i])>0)
                min = i;


        aux = a[j];
        a[j] = a[min];
        a[min] = aux;
        min = ++j;
    }
}

void selectionSort(char **a, int n){
    int min = 0, j = 0;
    char* aux;

    while(min < n){

        for(int i = j; i < n; i++)
            if(strcmp(a[min], a[i])>0)
                min = i;

        aux = new char [strlen(a[j])+1];
        strcpy(aux, a[j]);
        delete[] a[j];
        a[j] = new char [strlen(a[min])+1];
        strcpy(a[j], a[min]);
        delete[] a[min];
        a[min] = new char [strlen(aux)+1];
        strcpy(a[min], aux);
        delete[] aux;
        min = ++j;
    }

}

template <class A>
void shellSort(A *a, int n){
    int gap, j;
    A aux;

    for(gap = n/2; gap >= 1; gap=(gap)/2){
        for(int i = gap; i < n; i++){
            aux = a[i];
            j = i - gap;

            while(j >= 0 && Value<A>::compare(aux, a[j])<0){
                a[j+gap] = a[j];
                j -= gap;
            }
            a[j+gap] = aux;
        }

    }
}

void shellSort(char **a, int n){
    int gap, j;
    char *aux;

    for(gap = n/2; gap >= 1; gap=(gap)/2){
        for(int i = gap; i < n; i++){
            aux = new char [strlen(a[i])+1];
            strcpy(aux, a[i]);
            j = i - gap;

            while(j >= 0 && strcmp(aux, a[j]) < 0){
                delete [] a[j+gap];
                a[j+gap] = new char[strlen(a[j]) + 1];
                strcpy(a[j+gap], a[j]);
                j -= gap;
            }
            delete [] a[j+gap];
            a[j+gap] = new char[strlen(aux) + 1];
            strcpy(a[j+gap], aux);
            delete[] aux;
        }

    }

}

template <class A>
void countingSort(A *a, int n){
    A max=(A)a[0];
    int j = 0;
    for(int i=1; i<n; i++)
        if (Value<A>::compare(max, a[i])<0)
            max = a[i];


    A *aux = new A[(llong)max+1];
    for(int i = 0; i <= (llong)max; i++)
        aux[i] = 0;

    for(int i = 0; i < n; i++)
        aux[(llong)a[i]]++;

    for(int i = 0; i <= (llong)max; i++)
        while (aux[i]-- > (A)0 &&  j < n)
            a[j++] = (A)i;


    delete[]aux;
}

template <class A>
void bucketSort(A *a, int n, llong max){
    if (max <= log2(n)*n)
        max *= n+1;

    A **bucket = new A*[max/n+1];
    int *top = new int[max/n+1]();
    int j = 0;
    int aux;
    bool negative = false;

    for(int i =0; i < max/n+1; i++)
        bucket[i] = new A[n]();

    for(int i =0; i < n;i++){
        aux = (((llong)a[i]))*max/(n*n);
        if (aux<0){
            aux = 0;
            negative = true;
        } else if (aux > max/n)
            aux = max/n;

        bucket[aux][top[aux]++] = a[i];
    }
    for(int i = 0; i < max/n + 1; i++){
        int k = 0;
        if (top[i]>1){
            if ((2*top[i]*log2(top[i]))>(max) &&  !negative)
                countingSort(bucket[i],top[i]);
            else
                mergeSort(bucket[i], top[i]);
        }
        while(k < top[i])
            a[j++] = bucket[i][k++];
    }

    for(int i = 0; i < max/n + 1; i++)
        delete[]bucket[i];
    delete[]bucket;
    delete[]top;
}

void bucketSort(double *a, int n, llong max){
    if (max <= log2(n)*n)
        max *= n+1;

    double **bucket = new double*[max/n + 1];
    int *top = new int[max/n + 1]();
    int j = 0;
    int aux;

    for(int i =0; i < max/n + 1; i++)
        bucket[i] = new double[n]();

    for(int i =0; i < n;i++){
        aux = ((int)(a[i]))*max/(n*n);
        if (aux<0)
            aux = 0;
        else if (aux > max/n)
            aux = max/n;

        bucket[aux][top[aux]++] = a[i];
    }
    for(int i = 0; i < max/n + 1; i++){
        int k = 0;
        if (top[i]>1){
            mergeSort(bucket[i], top[i]);
        }
        while(k < top[i])
            a[j++] = bucket[i][k++];
    }

    for(int i = 0; i < max/n + 1; i++)
        delete[]bucket[i];
    delete[]bucket;
    delete[]top;
}

void bucketSort(char *a, int n, llong max){
    char **bucket = new char*[max/n+1];
    int *top = new int[max/n+1]();
    int j = 0;
    int aux;

    for(int i =0; i < max/n + 1; i++)
        bucket[i] = new char[n];

    for(int i =0; i < n;i++){
        aux = ((int)(a[i]))*max/(n);
        if (aux > max/n)
            aux = max/n;

        bucket[aux][top[aux]++] = a[i];
    }
    for(int i = 0; i < max/n + 1; i++){
        int k = 0;
        if (top[i]>1){
            countingSort(bucket[i],top[i]);
        }
        while(k < top[i])
            a[j++] = bucket[i][k++];
    }

    for(int i = 0; i < max/n + 1; i++)
        delete[]bucket[i];
    delete[]bucket;
    delete[]top;
}

template <class A>
void radixSort(A *a, int n, llong max){
    A **bucket = new A*[10];
    int *top = new int[10]();
    int j = 0;
    int aux;

    for(int i =0; i < 10; i++)
        bucket[i] = new A[n]();


    for(int k = 1; k <= (ulong)max; k*=10){
        j = 0;
        for(int i =0; i < n;i++){
            aux = ((uint)((llong)a[i]/k))%10;
            bucket[aux][top[aux]++] = a[i];
        }
        for(int i = 0; i < 10; i++){
            int k = 0;
            while(k < top[i])
                a[j++] = bucket[i][k++];
            top[i]=0;
        }

    }

    for(int i = 0; i < 10; i++)
        delete[]bucket[i];
    delete[]bucket;
    delete[]top;
}

void radixSort(char *a, int n, llong max){
    char **bucket = new char*[10];
    int *top = new int[10]();
    int j = 0;
    int aux;

    for(int i =0; i < 10; i++)
        bucket[i] = new char[n]();


    for(int k = 1; k <= (int)max; k*=10){
        j = 0;
        for(int i =0; i < n;i++){
            aux = ((int)a[i]/k)%10;
            bucket[aux][top[aux]++] = a[i];
        }
        for(int i = 0; i < 10; i++){
            int k = 0;
            while(k < top[i])
                a[j++] = bucket[i][k++];
            top[i]=0;
        }

    }

    for(int i = 0; i < 10; i++)
        delete[]bucket[i];
    delete[]bucket;
    delete[]top;
}



#endif // MYSORT_H

