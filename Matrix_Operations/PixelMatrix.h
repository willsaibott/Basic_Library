#ifndef PIXELMATRIX_H
#define PIXELMATRIX_H

#include <iostream>
#include "../Structures/Basic.h"


#define OUT_OF_LIMITS 1

using namespace std;



template <class A>
class PixelMatrix{

protected:
    A **pixel;
    imageSize size;

    void createPixelMatrix(A **image);
    void createPixelMatrix();

public:
    PixelMatrix(A **image, imageSize newSize);
    PixelMatrix(imageSize newSize);
    PixelMatrix();
    ~PixelMatrix();

    //getters
    A **getPixelMatrix(){return pixel;}
    A valueAt(uint row, uint col);
    imageSize getSize(){return size;}


    //setters
    void destroy();
    void setPixelMatrix(A **image);
    virtual void setSize(imageSize newSize);
    virtual void setSize(uint width, uint height);

};

template <class A>
PixelMatrix<A>::PixelMatrix(){
    pixel = NULL;
    size.height = 0;
    size.width = 0;
}

template <class A>
PixelMatrix<A>::PixelMatrix(A **image, imageSize newSize){
    pixel = NULL;
    size.height = newSize.height;
    size.width = newSize.width;
    createPixelMatrix(image);
}

template <class A>
PixelMatrix<A>::PixelMatrix(imageSize newSize){
    pixel = NULL;
    size.height = newSize.height;
    size.width = newSize.width;
    createPixelMatrix();
}

template <class A>
PixelMatrix<A>::~PixelMatrix(){
    destroy();
    size.height = 0;
    size.width = 0;

}

template <class A>
void PixelMatrix<A>::destroy(){
    if (pixel != NULL){
        for (uint i = 0; i < size.height; i++)
            delete[] pixel[i];
        delete [] pixel;
        pixel = NULL;
    }
}

//getter
template <class A>
A PixelMatrix<A>::valueAt(uint row, uint col){
    if (row < size.height && col < size.width)
        return pixel[row][col];

    throw(OUT_OF_LIMITS);
}


template <class A>
void PixelMatrix<A>::setSize(imageSize newSize){
    destroy();
    size.height = newSize.height;
    size.width = newSize.width;
    createPixelMatrix();
}

template <class A>
void PixelMatrix<A>::setSize(uint width, uint height){
    destroy();
    size.height = height;
    size.width = width;
    createPixelMatrix();
}

template <class A>
void PixelMatrix<A>::setPixelMatrix(A **image){
    for (uint i = 0; i < size.height; i++){
        for (uint j = 0; j < size.width; j++){
            pixel[i][j] = image[i][j];
        }
    }
}

template <class A>
void PixelMatrix<A>::createPixelMatrix(A **image){
    pixel = new A*[size.height];
    for (uint i = 0; i < size.height; i++){
        pixel[i] = new A[size.width];
        for (uint j = 0; j < size.width; j++){
            pixel[i][j] = image[i][j];
        }
    }
}

template <class A>
void PixelMatrix<A>::createPixelMatrix(){
    pixel = new A*[size.height];
    for(uint i = 0; i < size.height; i++)
        pixel[i] = new A[size.width];
}

#endif
