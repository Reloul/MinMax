#ifndef __MINMAX_H_
#define __MINMAX_H_

#include "morpion.h"

typedef struct coord
{
    int coordX;
    int coordY;
}coord;


void moveComputer(int** myGrid, int numComputer);
int minMax(int** myGrid,int depth,int isMax, int numComputer, int* countPass);

#endif