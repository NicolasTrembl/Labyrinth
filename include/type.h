#ifndef TYPE_H
#define TYPE_H

#define CELL_SIZE 3

#include <windows.h>
#include <stdbool.h>


typedef struct {
    int x;
    int y;
} iVector2;

typedef struct {
    HANDLE hConsole;
    iVector2 size;
    bool supportsColor;
} display;

typedef struct {
    int vertices;
    int** edges;
} graph;



#endif