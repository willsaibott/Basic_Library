#ifndef PIXELMATRIX_RGBD_H
#define PIXELMATRIX_RGBD_H


#include "PixelMatrix.h"
#include "Sphere_Distance_Calculator.h"
#include "Sphere_Similarities_Calculator.h"
#include "Intersection_Similarities_Calculator.h"

#define INTERSECTION_SIMILARITIES_ALGORITHM 2
#define SPHERE_SIMILARITIES_ALGORITHM 3
#define SPHERE_ALGORITHM 1
#define RUN_ALL_PIXEL_MATRIX 0


template <class A>
class PixelMatrix_RGBD : public PixelMatrix<A>{
private:

    A **dist;
    int method;
    void createDistanceMatrix();

public :
    PixelMatrix_RGBD(A **image, imageSize newSize);
    PixelMatrix_RGBD(imageSize newSize);
    PixelMatrix_RGBD();
    ~PixelMatrix_RGBD();

    //getters
    A **getDistanceMatrix(){return dist;}
    A getDistance_at(uint row, uint col);

    //setter
    void setMethod(int method){this->method = method;}

    //others
    virtual void setSize(imageSize newSize);
    virtual void setSize(uint width, uint height);
    virtual void eraseMatrix();
    void clean();
    A ** calculateDistanceMatrix(A **pixel2, int overlap);
    A calculateDistance_at(A pixel2, uint row, uint col);
};

template <class A>
PixelMatrix_RGBD<A>::PixelMatrix_RGBD() : PixelMatrix<A>()
{
    method = SPHERE_ALGORITHM;
    dist = NULL;
}


template <class A>
PixelMatrix_RGBD<A>::PixelMatrix_RGBD(A **image, imageSize newSize) : PixelMatrix<A>(image, newSize)
{
    method = SPHERE_ALGORITHM;
    dist = NULL;
}

template <class A>
PixelMatrix_RGBD<A>::PixelMatrix_RGBD(imageSize newSize) : PixelMatrix<A>(newSize)
{
    method = SPHERE_ALGORITHM;
    dist = NULL;
}

template <class A>
PixelMatrix_RGBD<A>::~PixelMatrix_RGBD()
{
    clean();
    this->size.height = 0;
    this->size.width = 0;
}

template<class A>
void PixelMatrix_RGBD<A>::clean(){
    if (dist!=NULL){
        for (uint i = 0; i < this->size.height; i++){
            delete [] dist[i];
        }
        delete [] dist;
        dist = NULL;
    }
}

template <class A>
void PixelMatrix_RGBD<A>::createDistanceMatrix(){
    clean();
    dist = new A*[this->size.height];
    for (uint i = 0; i < this->size.height; i++){
        dist[i] = new A[this->size.width]();
    }

}

template <class A>
void PixelMatrix_RGBD<A>::eraseMatrix(){
    for (uint i = 0; i < this->size.height; i++){
        for(uint j = 0; j < this->size.width; j++){
            dist[i][j] = 0;
        }
    }

}

template <class A>
void PixelMatrix_RGBD<A>::setSize(imageSize newSize){
    if (this->size.height!=newSize.height || this->size.width!=newSize.width){
        this->destroy();
        clean();
        this->size.height = newSize.height;
        this->size.width = newSize.width;
        this->createPixelMatrix();
        createDistanceMatrix();
    }

}

template <class A>
void PixelMatrix_RGBD<A>::setSize(uint width, uint height){
    this->destroy();
    clean();
    this->size.height = height;
    this->size.width = width;
    this->createPixelMatrix();
    createDistanceMatrix();
}



//getter

template <class A>
A PixelMatrix_RGBD<A>::getDistance_at(uint row, uint col){
    if (row < this->size.height && col < this->size.width)
        return dist[row][col];

    throw(OUT_OF_LIMITS);
}

//others

template <class A>
A **PixelMatrix_RGBD<A>::calculateDistanceMatrix(A** pixel2, int overlap){
    A min, aux;

    switch (method) {
    case SPHERE_ALGORITHM:
        if (true){
            Sphere_Distance_Calculator<A> sphere(this->pixel, pixel2, this->size);
            sphere.execute(overlap);
            clean();
            dist = sphere.getDistanceMatrix();
        }
        break;
    case RUN_ALL_PIXEL_MATRIX:
        //createDistanceMatrix();
        for (uint x = 0; x < this->size.height; x++){
            for (uint y = 0; y < this->size.width; y++){
                if ((uint) pixel2[x][y] != MAX_VALUE){
                    point_3D<A> p1, p2;
                    makePoint(&p1, (A)x, (A)y, pixel2[x][y]);
                    makePoint(&p2, (A)x, (A)y, this->pixel[x][y]);
                    min = distance2(p1, p2);


                    for(uint i = 0; i < this->size.height; i++){
                        p2.x = i;
                        for (uint j = 0; j < this->size.width; j++){
                            p2.y = j;
                            p2.z = this->pixel[i][j];
                            if (p2.z != MAX_VALUE){
                                aux = distance2(p1, p2);
                                if (aux < min)
                                    min = aux;
                            }
                        }
                    }
                }
                else
                    min = 0;
                dist[x][y] = min;
            }
        }

        break;
    case INTERSECTION_SIMILARITIES_ALGORITHM:
        if (true){
            Intersection_Similarities_Calculator<A> intersection(this->pixel, pixel2, this->size);
            intersection.execute(overlap);
            clean();
            dist = intersection.getDistanceMatrix();
        }
        break;
    case SPHERE_SIMILARITIES_ALGORITHM:
        if (true){
            Sphere_Similarities_Calculator<A> sphere(this->pixel, pixel2, this->size);
            sphere.execute(overlap);
            clean();
            dist = sphere.getDistanceMatrix();
        }
        break;
    default:
        break;
    }
    return dist;
}


template <class A>
A PixelMatrix_RGBD<A>::calculateDistance_at(A pixel2, uint row, uint col){
    if (row < this->size.height && col < this->size.width){
        A min, aux;

        switch (method) {
        case SPHERE_ALGORITHM:
            if (true){
                Sphere_Distance_Calculator<A> sphere(this->pixel, pixel2, this->size);
                min = sphere.execute_at(pixel2, row, col);
            }

            break;
        case RUN_ALL_PIXEL_MATRIX:
            createDistanceMatrix();
            point_3D<A> p1, p2;
            makePoint(&p1, row, col, pixel2);
            makePoint(&p2, row, col, this->pixel[row][col]);
            min = distance2(p1, p2);

            for(uint i = 0; i < this->size.height; i++){
                p2.x = i;
                for (uint j = 0; j < this->size.width; j++){
                    p2.y = j;
                    p2.z = this->pixel[i][j];
                    aux = distance2(p1, p2);
                    if (aux < min)
                        min = aux;
                }
            }


            break;
        case INTERSECTION_SIMILARITIES_ALGORITHM:
            if (true){
                Intersection_Similarities_Calculator<A> intersection(this->pixel, pixel2, this->size);
                min = intersection.execute_at(pixel2, row, col);
            }
            break;
        case SPHERE_SIMILARITIES_ALGORITHM:
            if (true){
                Sphere_Similarities_Calculator<A> sphere(this->pixel, pixel2, this->size);
                min = sphere.execute_at(pixel2, row, col);
            }
            break;
        default:
            break;
        }
        return min;
    }
    throw(OUT_OF_LIMITS);
}



#endif // PIXELMATRIX_RGBD_H
