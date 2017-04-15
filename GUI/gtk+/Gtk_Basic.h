#ifndef BASIC_GTK_WINDOW_H
#define BASIC_GTK_WINDOW_H

#include <gtkmm/application.h>
#include <gtkmm/window.h>

#define DEFAULT_WINDOW_WIDTH 250
#define DEFAULT_WINDOW_HEIGHT 250

#define GTK_WINDOW_OPEN_TIME_IN_SECONDS 1
#define MARGIN_OFF -1

struct buttonSize{
    uint width;
    uint height;
};


template <class A>
struct margin{
    A left;
    A right;
    A top;
    A bottom;
};

template <class A>
void copyMargin(margin<A> *m1, margin<A> *m2){
    m1->bottom = m2->bottom;
    m1->left = m2->left;
    m1->right = m2->right;
    m1->top = m2->top;
}

template <class A>
void createMargin(margin<A> *m, A left, A right, A top, A bottom){
    m->bottom = bottom;
    m->left = left;
    m->right = right;
    m->top = top;
}

#endif // BASIC_GTK_WINDOW_H
