
 /*!
 *  \file minMax.c
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1
 *  \brief fichier permettant de définir les différentes fonctions pour utiliser l'algorithme minMax
*/ 

#include "minMax.h"

/*!
 *  \fn void moveComputer (int** myGrid)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 14:23:18
 *  \brief procédure permettant de simuler les coups que fait l'algorithme Min Max 
 *  \param myGrid tableau 2d de pointeur d'eniter représentant la grille de jeu du Morpion 
 *  \param numComputer entier permettant de savoir si l'ordinateur est joueur 1 ou 2
*/

void moveComputer (int** myGrid, int numComputer) {
    int bestScore = -1000;
    coord bestMove;
    bestMove.coordX = -1;
    bestMove.coordY = -1;
    int* countPass = malloc(sizeof(int));
    *countPass = 0;
    int i, j;
    int score;
    for (i = 0; i <3; i++ ){
        for (j = 0; j<3 ; j++){
            if(myGrid[i][j] == 0){
                myGrid[i][j] = numComputer;
                score = minMax(myGrid, 0,0, numComputer, countPass);
                myGrid[i][j] = 0;
                if(score > bestScore){
                    bestScore = score;
                    bestMove.coordX = i;
                    bestMove.coordY = j;
                }
            }
        }
    }
    myGrid[bestMove.coordX][bestMove.coordY] = numComputer;
    printf("Compteur Min Max : %d \n", *countPass);
    free(countPass);
}

/*!
 *  \fn int minMax (int** myGrid, int depth, int isMax)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 14:42:05
 *  \brief fonction permettant de retouner le score de chaque coup
 *  \param myGrid tableau 2d de pointeur d'entier représentant la grille de jeu du Morpion
 *  \param depth entier représentant la profondeur de la récusivité (éviter des boucles trop grandes )
 *  \param isMax entier représentant un booléen permettant de savoir si l'on souhaite prédir le coup de l'ordinateur ou celui du joueur
 *  \param numComputer entier permettant de savoir si l'ordinateur est joueur 1 ou 2
 *  \param countPass pointeur d'entier permettant de savoir combien de fois l'algorithme rentre dans minMax à chaque coup
 *  \return le score de chaque coup
*/

int minMax(int** myGrid, int depth, int isMax, int numComputer, int* countPassMax) {
    int i, j;
    int result = checkWin(myGrid);
    int score = 0;

    if (result == numComputer) {
        return 100 - depth;  // Score positif si l'ordinateur gagne
    } else if (result == 3) {
        return 0;  // Égalité
    } else if (result > 0) {
        return depth - 100;  // Score négatif si l'adversaire gagne
    }

    if (isMax) {
        int bestScore = -1000;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (myGrid[i][j] == 0) {
                    myGrid[i][j] = numComputer;
                    *countPassMax += 1;
                    score = minMax(myGrid, depth + 1, 0, numComputer, countPassMax);
                    myGrid[i][j] = 0;
                    bestScore = score > bestScore ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++) {
                if (myGrid[i][j] == 0) {
                    myGrid[i][j] = 3 - numComputer;  // Adversaire
                    score = minMax(myGrid, depth + 1, 1, numComputer, countPassMax);
                    myGrid[i][j] = 0;
                    bestScore = score < bestScore ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}
