#ifndef SPHERE_DISTANCE_CALCULATOR_H
#define SPHERE_DISTANCE_CALCULATOR_H

#include "../Structures/Basic.h"
#define STATE_HORIZONTAL_UP 0
#define STATE_HORIZONTAL_DOWN 1
#define STATE_VERTICAL_LEFT 2
#define STATE_VERTICAL_RIGHT 3

template <class A>
class Sphere_Distance_Calculator {
protected:

    A **m1, **m2;
    A **dist;
    imageSize size;
    A shift1, shift2;

public:
    Sphere_Distance_Calculator(A **matrix, A **matrix2, imageSize matrixSize);

    //getter
    A ** getDistanceMatrix(){return dist;}

    //others
    void execute(int overlap);
    void defineShift(int overlap);
    A execute_at(A, A row, A col);



};



template <class A>
Sphere_Distance_Calculator<A>::Sphere_Distance_Calculator(A **matrix, A **matrix2, imageSize matrixSize){
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
void Sphere_Distance_Calculator<A>::execute(int overlap){

    defineShift(overlap);
    for (uint i = 0; i < size.height; i++)
        for (uint j = 0; j < size.width; j++){
            if(m2[i][j]!=MAX_VALUE)
                dist[i][j] = execute_at(m2[i][j], i , j);
            else
                dist[i][j] = 0;
        }
}

template <class A>
void Sphere_Distance_Calculator<A>::defineShift(int overlap){
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
A Sphere_Distance_Calculator<A>::execute_at(A depth, A row, A col){
    A min, minPossible;
    point_3D<A> p1, p2;
    A r, r2;
    A j_base, j_top, i_base, i_top, state;
    bool running, up, down, left, right;

    up = down = left = right = false;
    //initializing variables...
    state = STATE_HORIZONTAL_UP;
    r2 = r = 0;
    j_base = j_top = col;
    i_base = i_top = row;

    makePoint(&p1, row, col, depth - shift2);
    makePoint(&p2, row, col, m1[row][col]);

    min = distance2(p1, p2);
    while ((uint)min > r2 && ((i_base != 0) || (i_top != size.height - 1)||( j_base != 0) || (j_top != size.width -1))){
        r++;
        r2 = 2*r*r;
        j_base = ((int)(col - r)>=0)? col - r: j_base;
        j_top = ((int)(col + r)<size.width)? col + r: j_top;
        i_base = ((int)(row - r)>=0)? row - r: i_base;
        i_top = ((int)(row + r)<size.height)? row + r: i_top;

        // continue from here
        //    A test = 5199;
        running = true;
        while (running){/*
                        if (depth==test)
                        cout << "\nS: " << state << " min: " << min << " r:" << r << " col: " << col << " row: " << row << " pmin: (" << i_base << ", " << j_base <<") pmax: " << i_top << ", " << j_top << ").";*/
            switch (state) {
            case STATE_HORIZONTAL_UP:
                if (i_base > 0 || !up){
                    up = (i_base == 0);
                    for (A j = j_base; j <= j_top; j++){
                        for (A k = 0;((((int)(i_base - k - row))*((int)(i_base - k - row)) + ((int)(j - col))*((int)(j - col))) <= r2) && ((int)(i_base - k) >= 0);k++){
                            if (m1[i_base-k][j]!=MAX_VALUE){
                                //                                                            if (depth==test)
                                //                                                            cout << "\t" << m1[i_base-k][j];
                                makePoint(&p2, i_base-k, j, m1[i_base-k][j]-shift1);
                                minPossible = distance2(p1, p2);
                                min = (minPossible < min)? minPossible: min;
                            }
                        }
                    }
                }
                state = STATE_VERTICAL_RIGHT;
                break;
            case STATE_HORIZONTAL_DOWN:
                if (i_top<size.height-1 || !down){
                    down = (i_top==size.height-1);
                    for (A j = j_base; j <= j_top; j++){
                        for (A k = 0;((((int)(i_top + k - row))*((int)(i_top + k - row)) + ((int)(j - col))*((int)(j - col))) <= r2) && ((int)i_top + k < size.height); k++){
                            if (m1[i_top+k][j]!=MAX_VALUE){
                                //                                                            if (depth==test)
                                //                                                            cout << "\t" << m1[i_top+k][j];
                                makePoint(&p2, i_top+k, j, m1[i_top+k][j]-shift1);
                                minPossible = distance2(p1, p2);
                                min = (minPossible < min)? minPossible: min;
                            }
                        }

                    }
                }
                state =  STATE_VERTICAL_LEFT;
                break;
            case STATE_VERTICAL_LEFT:
                if (j_base > 0 || !left){
                    left = (j_base == 0);
                    for (A i = i_base; i <= i_top; i++){
                        for (A k = 0;((((int)(i - row))*((int)(i - row)) + ((int)(j_base - k - col))*((int)(j_base - k - col))) <= r2) && ((int)(j_base - k) >= 0) ; k++){
                            if (m1[i][j_base-k]!=MAX_VALUE){
                                //                                                            if (depth==test)
                                //                                                            cout << "\t" << m1[i][j_base-k];
                                makePoint(&p2, i, j_base-k, m1[i][j_base-k]-shift1);
                                minPossible = distance2(p1, p2);
                                min = (minPossible < min)? minPossible: min;
                            }
                        }
                    }
                }
                state = STATE_HORIZONTAL_UP;
                running = false;
                break;
            case STATE_VERTICAL_RIGHT:
                if (j_top < size.width -1 || !right){
                    right = (j_top == size.width -1);
                    for (A i = i_base; i <= i_top; i++){
                        for (A k = 0;((((int)(i - row))*((int)(i - row)) + ((int)(j_top + k - col))*((int)(j_top + - col))) <= r2) && ((int)(j_top + k) < size.width) ; k++){
                            if (m1[i][j_top+k]!=MAX_VALUE){
                                //                                                            if (depth==test)
                                //                                                            cout << "\t" << m1[i][j_top+k];
                                makePoint(&p2, i, j_top+k, m1[i][j_top+k]-shift1);
                                minPossible = distance2(p1, p2);
                                min = (minPossible < min)? minPossible: min;
                            }
                        }
                    }
                }
                state = STATE_HORIZONTAL_DOWN;
                break;
            default:
                break;
            }
        }

    }
    return min;
}

#endif // SPHERE_DISTANCE_CALCULATOR_H
