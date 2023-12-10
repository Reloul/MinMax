#ifndef __ALPHABETA_H_
#define __ALPHABETA_H_

 /*!
 *  \file nom_fichier
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1
 *  \brief 
*/ 

/*Inclusion de la librairie stdio.h qui permet à l'utilisateur de faire un printf*/
#include <stdio.h>
/*Inclusion de la librairie stdlib.h qui permet à l'utilisateur de gérer la mémoire de façon dynamique ou encore de pouvoir intéragir avec le système d'exploitation*/
#include <stdlib.h>
#include <limits.h>
#include "morpion.h"
#include "minMax.h"

void moveComputerAB(int** myGrid, int numComputer);
int alphaBeta(int** myGrid,int depth,int isMax, int numComputer, int alpha, int beta);
int max(int a, int b);
int min(int a, int b);

int evaluate(int** myGrid);
int evaluateLine(int cell1, int cell2, int cell3);

#endif