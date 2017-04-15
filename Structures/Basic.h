#ifndef BASIC_STRUCTURES_H
#define BASIC_STRUCTURES_H

#include <cmath>
#include <iomanip>
#include "Value.h"

using std::setfill;
using std::cout;
using std::setw;
using std::string;

#define OVERLAP_BY_MINIMUN 1
#define OVERLAP_BY_FIRST 2
#define OVERLAP_BY_CENTER 3
#define OVERLAP_OFF 0
#define MAX_VALUE 255
#define SIMILARITY_FULL 0
#define SIMILARITY_CLOSE 1
#define SIMILARITY_FAR 5
#define SIMILARITY_FACTOR 10
#define ELEMENT_NOT_FOUND -1

typedef unsigned int uint;
typedef unsigned char byte;
typedef unsigned long ulong;
typedef unsigned long long ullong;
typedef long long llong;
typedef long double ldouble;
typedef ldouble Weight;

template <class A>
struct node_position{
    A value;
    int pos;
};

struct imageSize{
    uint width;
    uint height;
};

struct Size{
    uint rows;
    uint cols;
};

struct windowSize{
    uint width;
    uint height;
};

template <class A>
struct point_2D{
    A x;
    A y;
};


template <class A>
struct point_3D{
    A x;
    A y;
    A z;
};


template <class A>
A distance2(point_3D<A> p1, point_3D<A> p2){
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z);
}


template <class A>
A distance(point_3D<A> p1, point_3D<A> p2){
    return pow(distance2(p1, p2), 0.5);
}

template <class A>
A distance2(point_2D<A> p1, point_2D<A> p2){
    return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}


template <class A>
A distance(point_2D<A> p1, point_2D<A> p2){
    return pow(distance2(p1, p2), 0.5);
}

template <class A>
point_3D<A> * makePoint(A x, A y, A z){
    point_3D<A> *p = new point_3D<A>;

    p->x = x;
    p->y = y;
    p->z = z;
    return p;
}

template <class A>
point_2D<A> * makePoint(A x, A y){
    point_2D<A> *p = new point_2D<A>;

    p->x = x;
    p->y = y;
    return p;
}

template <class A>
void makePoint(point_3D<A> *p, A x, A y, A z){
    p->x = x;
    p->y = y;
    p->z = z;
}

template <class A>
void makePoint(point_2D<A> *p, A x, A y){
    p->x = x;
    p->y = y;
}
#endif // BASIC_H
