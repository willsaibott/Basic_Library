#ifndef MYPRINTOPTIONS_H
#define MYPRINTOPTIONS_H

#include <cstdio>
#include <sys/ioctl.h>
#include "Basic.h"

#define COLOR_DEFAULT 0
#define COLOR_BLACK 30
#define COLOR_RED 31
#define COLOR_GREEN 32
#define COLOR_BROWN 33
#define COLOR_BLUE 34
#define COLOR_MARGENTA 35
#define COLOR_CYAN 36
#define COLOR_LIGHTGRAY 37


void setInputTextColor(int color, bool bold){
    switch (color) {
    case COLOR_RED:
        if(bold)
            printf("\033[1;%dm", COLOR_RED);
        else
            printf("\033[0;%dm", COLOR_RED);
        break;
    case COLOR_BLACK:
        if(bold)
            printf("\033[1;%dm", COLOR_BLACK);
        else
            printf("\033[0;%dm", COLOR_BLACK);
        break;
    case COLOR_GREEN:
        if(bold)
            printf("\033[1;%dm", COLOR_GREEN);
        else
            printf("\033[0;%dm", COLOR_GREEN);
        break;
    case COLOR_BROWN:
        if(bold)
            printf("\033[1;%dm", COLOR_BROWN);
        else
            printf("\033[0;%dm", COLOR_BROWN);
        break;
    case COLOR_BLUE:
        if(bold)
            printf("\033[1;%dm", COLOR_BLUE);
        else
            printf("\033[0;%dm", COLOR_BLUE);
        break;
    case COLOR_MARGENTA:
        if(bold)
            printf("\033[1;%dm", COLOR_MARGENTA);
        else
            printf("\033[0;%dm", COLOR_MARGENTA);
        break;
    case COLOR_CYAN:
        if(bold)
            printf("\033[1;%dm", COLOR_CYAN);
        else
            printf("\033[0;%dm", COLOR_CYAN);
        break;
    case COLOR_LIGHTGRAY:
        if(bold)
            printf("\033[1;%dm", COLOR_LIGHTGRAY);
        else
            printf("\033[0;%dm", COLOR_LIGHTGRAY);
        break;
    default:
            printf("\033[0m");
        break;
    }
}


void printToCoordinates(int x, int y, string text)
{
    printf("\033[%d;%dH%s\n", x, y, text.c_str());
}


void printToCoordinates(int x, int y, double text)
{
    printf("\033[%d;%dH%f\n", x, y, text);
}


void printToCoordinates(int x, int y, float text)
{
    printf("\033[%d;%dH%f\n", x, y, text);
}


void printToCoordinates(int x, int y, char* text)
{
    printf("\033[%d;%dH%s\n", x, y, text);
}

void printToCoordinates(int x, int y, const char* text)
{
    printf("\033[%d;%dH%s\n", x, y, text);
}


void printToCoordinates(int x, int y, char text)
{
    printf("\033[%d;%dH%c\n", x, y, text);
}

template <class A>
void printToCoordinates(int x, int y, A text)
{
    printf("\033[%d;%dH%d\n", x, y, text);
}

int getTerminalColumns(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}

int getTerminalRows(){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}


void getCursorPosition(int *x, int *y){
    x = y;
    y = x;
}

void moveCursorToXY(int x, int y){
    if (x > 0 && y > 0)
        printf("\033[%d;%dH", x, y);
}

#endif // MYPRINTOPTIONS_H
