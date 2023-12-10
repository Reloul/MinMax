/*!
 *  \file alphaBeta.c
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1
 *  \brief fichier permettant de déclarer les fonctions afin 
*/ 

#include "alphaBeta.h"

/*!
 *  \fn void moveComputer (int** myGrid)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 14:23:18
 *  \brief procédure permettant de simuler les coups que fait l'algorithme Min Max 
 *  \param myGrid tableau 2d de pointeur d'eniter représentant la grille de jeu du Morpion 
 *  \param numComputer entier permettant de savoir si l'ordinateur est joueur 1 ou 2
*/

void moveComputerAB(int** myGrid, int numComputer) {
    int bestScore = INT_MIN;
    int bestMoveX = -1;
    int bestMoveY = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (myGrid[i][j] == 0) {
                myGrid[i][j] = numComputer;
                int score = alphaBeta(myGrid, 3, 0,numComputer ,INT_MIN, INT_MAX); // Adjust depth as needed
                myGrid[i][j] = 0;

                if (score > bestScore) {
                    bestScore = score;
                    bestMoveX = i;
                    bestMoveY = j;
                }
            }
        }
    }

    myGrid[bestMoveX][bestMoveY] = numComputer;
}



/*!
 *  \fn int alphaBeta (int** myGrid, int deph, int isMax, int numComputer, int* countPass, int* alpha, int* beta)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 20:36:56
 *  \brief fonction permettant d'appliquer l'algorithme alpha beta
 *  \param myGris tableau 2d de pointeur d'entier représentant la grille de jeu du Morpion
 *  \param depth entier représentant la profondeur 
 *  \param isMax entier représentant un bollean pour savoir s'il faut prévoir le coup de l'ordinateur ou celui du joueur
 *  \param numComputer entier permettant de savoir si l'ordinateur joue en premier ou deuxième
 *  \param countPass pointeur d'entier permettant de compter le nombre de fois où l'algorithme boucle
 *  \param alpha pointeur d'entier pour représenter notre nombre alpha
 *  \param beta pointeur d'entier représentant le nombre beta
 *  \return  
*/

int alphaBeta(int** myGrid, int depth, int isMaximizing,int numComputer, int alpha, int beta) {
    int player;

    if(numComputer == 1){
        player = 2;
    }else{
        player = 1;
    }
    
    if (depth == 0 || checkWin(myGrid) != 0) {
        return evaluate(myGrid); // You need to implement the evaluation function
    }
    
    if (isMaximizing) {
        int maxEval = INT_MIN;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (myGrid[i][j] == 0) {
                    myGrid[i][j] = numComputer; 
                    int eval = alphaBeta(myGrid, depth - 1, !isMaximizing, numComputer,alpha, beta);
                    myGrid[i][j] = 0;
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) {
                        break; // Beta cut-off
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (myGrid[i][j] == 0) {
                    myGrid[i][j] = player; 
                    int eval = alphaBeta(myGrid, depth - 1, !isMaximizing,numComputer ,alpha, beta);
                    myGrid[i][j] = 0;
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) {
                        break; // Alpha cut-off
                    }
                }
            }
        }
        return minEval;
    }
}

/*!
 *  \fn int max (int a, int b)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 20:51:37
 *  \brief fonction permettant de trouver le maximum entre 2 entiers 
 *  \param a entier qu'on chercher à compare
 *  \param b entier qu'on cherche à comparer
 *  \return retourne l'entier maximum entre a et b 
*/

int max (int a, int b) { 
    int max;
    if(a < b){
        max = b;
    }else{
        max = a;
    }
    return max;
}


/*!
 *  \fn int min (int a, int b)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 20:51:37
 *  \brief fonction permettant de trouver le minimum entre 2 entiers 
 *  \param a entier qu'on chercher à compare
 *  \param b entier qu'on cherche à comparer
 *  \return retourne l'entier minimum entre a et b 
*/

int min (int a, int b) { 
    int min;
    if(a > b){
        min = b;
    }else{
        min = a;
    }
    return min;
}



int evaluate(int** myGrid) {
    // Check for wins
    int winner = checkWin(myGrid);
    if (winner == 2) {
        return 10; // Computer wins
    } else if (winner == 1) {
        return -10; // Player wins
    } else if (winner == 3) {
        return 0; // It's a draw
    }

    int score = 0;

    // Evaluate rows
    for (int i = 0; i < 3; ++i) {
        score += evaluateLine(myGrid[i][0], myGrid[i][1], myGrid[i][2]);
    }

    // Evaluate columns
    for (int j = 0; j < 3; ++j) {
        score += evaluateLine(myGrid[0][j], myGrid[1][j], myGrid[2][j]);
    }

    // Evaluate diagonals
    score += evaluateLine(myGrid[0][0], myGrid[1][1], myGrid[2][2]);
    score += evaluateLine(myGrid[0][2], myGrid[1][1], myGrid[2][0]);

    return score;
}

int evaluateLine(int cell1, int cell2, int cell3) {
    // Evaluate a line (row, column, or diagonal)
    int score = 0;

    // Check for computer win
    if (cell1 == 2 && cell2 == 2 && cell3 == 2) {
        score = 1;
    }
    // Check for player win
    else if (cell1 == 1 && cell2 == 1 && cell3 == 1) {
        score = -1;
    }

    return score;
}
