#ifndef INTERSECTION_SIMILARITIES_CALCULATOR_H
#define INTERSECTION_SIMILARITIES_CALCULATOR_H


#include "../Structures/Basic.h"


template <class A>
class Intersection_Similarities_Calculator {
protected:

    A **m1, **m2;
    A **dist;
    imageSize size;
    A shift1, shift2;

public:
    Intersection_Similarities_Calculator(A **matrix, A **matrix2, imageSize matrixSize);

    //getter
    A ** getDistanceMatrix(){return dist;}

    //others
    void execute(int overlap);
    void defineShift(int overlap);

    A execute_at(A depth, uint row, uint col);

};



template <class A>
Intersection_Similarities_Calculator<A>::Intersection_Similarities_Calculator(A **matrix, A **matrix2, imageSize matrixSize){
    m1 = matrix;
    m2 = matrix2;
    size.height = matrixSize.height;
    size.width = matrixSize.width;
    dist = new A*[size.height];
    for (uint i = 0; i < size.height; i++){
        dist[i] = new A[size.width]();
    }
}

//others

template <class A>
void Intersection_Similarities_Calculator<A>::execute(int overlap){

    defineShift(overlap);
    for (uint i = 0; i < size.height; i++)
        for (uint j = 0; j < size.width; j++){
            dist[i][j] = execute_at(m2[i][j], i , j);
        }
}

template <class A>
void Intersection_Similarities_Calculator<A>::defineShift(int overlap){
    A min1 = m1[0][0], min2 = m2[0][0];
    bool found = false;
    switch (overlap) {
    case OVERLAP_BY_MINIMUN:
        for (uint i = 0; i < size.height; i++){
            for (uint j = 0; j < size.width; j++){
                if(m1[i][j]!=MAX_VALUE && m1[i][j] < min1)
                    min1 = m1[i][j];
                if(m2[i][j]!=MAX_VALUE && m2[i][j] < min2)
                    min2 = m2[i][j];
            }
        }
        break;
    case OVERLAP_BY_FIRST:
        for (uint i = 0; i < size.height && !found; i++){
            for (uint j = 0; j < size.width; j++){
                if(m1[i][j]!=MAX_VALUE && m2[i][j]!=MAX_VALUE){
                    min1 = m1[i][j];
                    min2 = m2[i][j];
                    found = true;
                    break;
                }
            }
        }
        break;
    case OVERLAP_BY_CENTER:
        min1 = m1[size.height/2][size.width/2];
        min2 = m2[size.height/2][size.width/2];
        break;
    case OVERLAP_OFF:
        min1 = min2 = 0;
        break;
    default:
        break;
    }

    if (min2 > min1){
        shift2 = min2 - min1;
        shift1 = 0;
    }
    else{
        shift2 = 0;
        shift1 = min1 - min2;
    }
}

template <class A>
A Intersection_Similarities_Calculator<A>::execute_at(A depth, uint row, uint col){
    A diff = (depth - shift2) - (m1[row][col]-shift1);
    A similarity;
    if (diff == (A)0){
        similarity = (A)SIMILARITY_FULL;
    }
    else if (abs(diff) <=  SIMILARITY_FACTOR){
        similarity = (A)SIMILARITY_CLOSE;
    }
    else{
        similarity = (A)SIMILARITY_FAR;
    }
    return similarity;
}



#endif // INTERSECTION_SIMILARITIES_CALCULATOR_H
