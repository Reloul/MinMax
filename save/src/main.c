/*!
 *  \mainpage Programme pour simuler l'algorithme MinMax sur le jeu du Morpion
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \section INFO
 *     Voici le code fais par Valentin Serres qui permet de faire tourner l'algorithme MinMax sur le jeu du Morpion
*/


 /*!
 *  \file main.c
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1
 *  \brief fichier main permettant d'exécuter les différentes fonctions du code
*/ 

#include "morpion.h"

int main(){
    int** tab;
    int choice;
    initGrid(&tab);
    setGrid(tab);

    printf("Que souhaitez vous faire: \n 1 - Jouer contre un autre Joueur \n 2 - Jouer contre MinMax \n 3 - Jouer contre AlphaBeta \n");
    choice = checkInt(3,1);
    switch (choice)
    {
    case 1:
        displayGrid(tab);
        play(tab);
        break;
    
    case 2:
        displayGrid(tab);
        playMinMax(tab);
        break;
    }
    for(int i =0; i<3; i++){
        free(tab[i]);
    }
    free(tab);
    return(0);
}
