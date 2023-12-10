#ifndef __MORPION_H_
#define __MORPION_H_

 /*!
 *  \file morpion.h
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1
 *  \brief fichier de déclaration des différentes fonctions permettant de jouer au Morpion
*/ 

/*Inclusion de la librairie stdio.h qui permet à l'utilisateur de faire un printf*/
#include <stdio.h>
/*Inclusion de la librairie stdlib.h qui permet à l'utilisateur de gérer la mémoire de façon dynamique ou encore de pouvoir intéragir avec le système d'exploitation*/
#include <stdlib.h>

void initGrid(int*** myGrid);
void setGrid(int** myGrid);
int checkInt(int maxInt, int minInt);
void play(int** myGrid);
int moveValid(int* move, int joueur);
void displayGrid(int** myGrid);
int checkWin(int** myGrid);
void playMinMax(int** myGrid);

#endif