
 /*!
 *  \file morpion.h
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1
 *  \brief fichier de définition des différentes fonction permettant de jouer au Morpion
*/ 

#include "morpion.h"
#include "minMax.h"

/*!
 *  \fn void initGrid (int*** myGrid)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 10:17:20
 *  \brief procédure permettant d'initialiser la grille du jeu du Morpion 
 *  \param myGrid pointeur d'une tableau 2d d'entier que l'on souhaite initialiser pour servir de plateau de jeu
*/

void initGrid (int*** myGrid) {
    int i;
    //On alloue la mémoire nécessaire à notre grille de jeu
    *myGrid = malloc(3*sizeof(int*));
    for(i = 0; i<3; i++){
        (*myGrid)[i] = malloc(3*sizeof(int));
    }
}

/*!
 *  \fn void èsetGrid (int** myGrid)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 11:45:13
 *  \brief procédure permettant d'initialiser les valeur de la grille à 0 
 *  \param myGrid tableau 2d de pointeur d'entier 
*/

void setGrid (int** myGrid) {
    int i,j;
    //On attribue 0 à toutes les cases pour qu'elles apparaissent "vide"
    for(i = 0; i<3; i++){
        for(j = 0; j<3; j++){
            myGrid[i][j] = 0;
        }
    }
}
 


/*!
 *  \fn int checkInt(int maxInt, int minInt)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Sun 19 2023 - 11:21:11
 *  \brief fonction permettant de vérifier que l'élément choisit est bien un entier 
 *  \param maxInt entier correspondant à l'entier maximal que l'on souhaite que l'utilisateur rentre
 *  \param minInt entier correspondant à l'entier minimum que l'on souhaite que l'utilisateur rentre
 *  \return la valeur choisie et valide
*/

int checkInt(int maxInt, int minInt) { 
    int check;
    int value;
    check = scanf("%d", &value);
    while((check == 0) || ((value < minInt) || (value > maxInt))){
        printf("erreur de saisie veuillez recommencer \n");
        while(getchar() != '\n'){};
        check=scanf("%d", &value);
    }
    return(value); 
}

/*!
 *  \fn void displayGrid (int** myGrid)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 11:30:46
 *  \brief procédure permettant d'afficher la grille de jeu du Morpion
 *  \param myGrid tableau 2d de pointeur d'entier
*/

void displayGrid (int** myGrid) {
    //Entiers qui serviront d'itérateurs de boucles
    int i;
    int j;
    ////On affiche le numéro des colonnes de la grille, si le numéro dépasse 10 on affiche un espace de moins (sinon décalage dans l'affichage des cases)
    printf("     ");
    for(i=1;i<4;i++){
        printf("%d   ", i);
    }
    printf("\n");
    //Partie pour afficher la première ligne de la grille
    printf("   ┌");
    for(i=0;i<2;i++){
        printf("───┬");
    }
    printf("───┐\n");
    //Boucle permettant d'afficher le contenue de notre grille
    for(i=0;i<3;i++){
        //On affiche le numéro des lignes de la grille, si le numéro dépasse 10 on affiche un espace de moins (sinon décalage dans l'affichage des cases)
        printf("%d  ", i+1);   
        for(j=0;j<3;j++){
            //Si l'état de la case est de 0 alors elle reste cachée
            if(myGrid[i][j] == 0){
                printf("│   ");
            }
            //Si l'état de la case vaut 1 alors elle ne doit pas être cachée
            else{
                //Si son type vaut 1 alors c'est une case vide sans bombe à côté
                if(myGrid[i][j] == 1){
                    printf("│ X ");
                }
                //Sinon si son type vaut 2 alors c'est un rond
                else if (myGrid[i][j] == 2){
                    printf("│ ◯ ");
                }      
            }
        }
        printf("│\n");
        //On affiche ce qui sépare les lignes jusqu'à int_taille-1 pour éviter d'en avoir 1 en trop
        if(i<2){
            printf("   ├");
            for(j=0;j<2;j++){
                printf("───┼");
            }
            printf("───┤\n");
        }
    }
    //On affiche la dernière ligne
    printf("   └");
    for(i=0;i<2;i++){
        printf("───┴");
    }
    printf("───┘\n");
}
 
/*!
 *  \fn void play (int** myGrid)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 11:50:40
 *  \brief procédure permettant de jouer au morpion
 *  \param myGrid tableau 2d de pointeur d'entier représentant la grille du Morpion
*/

void play (int** myGrid) {
    int joueur = 1;
    int x, y, verifMove;
    int nbMove = 1;
    int verifWin = 0;
    
    while(verifWin == 0){
        verifMove = 0;
        if(nbMove %2 == 1){
            joueur = 1;
        }else{
            joueur = 2;
        }
        while(verifMove == 0){
            printf("Joueur %d, veuillez choisir une case à jouer (entrez le numéro de ligne de la case: ) \n", joueur);
            x = checkInt(3, 1)-1;
            printf("Choisissez le numéro de colonne : \n");
            y = checkInt(3, 1)-1;
            verifMove = moveValid(&myGrid[x][y], joueur);
            if(verifMove == 0){
                printf("Coup impossible veuillez réessayer! \n");
            }
        }
        displayGrid(myGrid);
        verifWin = checkWin(myGrid);   

        nbMove ++;
    }
    if(verifWin != 3 ){
        printf("Le joueur %d a gagné! \n", verifWin);
    }else{
        printf("Égalité! \n");
    }
}
 
/*!
 *  \fn int moveValid (int** myGrid, int* move)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 12:02:08
 *  \brief fonction permettant de savoir si un coup est valide ou non et de jouer le coup s'il est valide
 *  \param move pointeur d'entier représentant le coup à jouer 
 *  \param joueur entier représentant le joueur voulant jouer
 *  \return 1 si le coup est possible et qu'il est joué et 0 sinon 
*/

int moveValid (int* move, int joueur) {
    int valid = 0;
    if(*move == 0){
        *move = joueur;
        valid = 1; 
    }
    return valid;
}


/*!
 *  \fn int checkWin (int** myGrif)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 12:09:43
 *  \brief fonction permettant de vérifier qu'un joueur est gagné 
 *  \param myGrid tableau 2d de pointeur d'entier représentant la grille de jeu du Morpion 
 *  \return 0 si personne ne gagne, 1 si le joueur 1 a gagné et 2 si le joueur 2 a gagné 
*/
int checkWin(int** myGrid) {
    int i, j;
    int verifWin = 0;

    //Vérification des lignes
    for ( i = 0; i < 3; ++i) {
        if (myGrid[i][0] == myGrid[i][1] && myGrid[i][1] == myGrid[i][2] && myGrid[i][0] != 0) {
            verifWin = myGrid[i][0];
        }
    }

    // Vérification des colonnes
    for (j = 0; j < 3; ++j) {
        if (myGrid[0][j] == myGrid[1][j] && myGrid[1][j] == myGrid[2][j] && myGrid[0][j] != 0) {
            verifWin = myGrid[0][j];
        }
    }

    // Vérification de la diagonale principale
    if (myGrid[0][0] == myGrid[1][1] && myGrid[1][1] == myGrid[2][2] && myGrid[0][0] != 0) {
        verifWin = myGrid[0][0];
    }

    // Vérification de l'autre diagonale
    if (myGrid[0][2] == myGrid[1][1] && myGrid[1][1] == myGrid[2][0] && myGrid[0][2] != 0) {
        verifWin = myGrid[0][2];
    }
    if(verifWin == 0){
        verifWin = 3;
        for(i=0; i< 3; i++){
            for(j= 0; j<3; j++){
                if(myGrid[i][j] == 0){
                    verifWin = 0;
                }
            }
        }    
    }
    return verifWin;
}

/*!
 *  \fn void playMinMax (int** myGrid)
 *  \author SERRES Valentin <serresvale@cy-tech.fr>
 *  \version 0.1 Premier jet
 *  \date Mon 04 2023 - 15:37:46
 *  \brief procedure permettant de jouer contre l'algorithme MinMax 
 *  \param myGrid tableau 2d de pointeur d'entier représentant la grille de jeu du Morpio, 
*/

void playMinMax (int** myGrid) {
    int order;
    int numComputer;
    int x, y, verifMove;
    int verifWin = 0;
    
    printf("Voulez-vous commencer à jouer? \n 1 - Oui \n 2 - Non \n");
    order = checkInt(2, 1);
    
    if (order == 1) {
        numComputer = 2;
    } else {
        numComputer = 1;
        // Premier coup de l'ordinateur
        moveComputer(myGrid, numComputer);
        displayGrid(myGrid);
    }

    while (verifWin == 0) {
        // Tour du joueur
        printf("Joueur %d, veuillez choisir une case à jouer (entrez le numéro de ligne de la case): \n", order);
        x = checkInt(3, 1) - 1;
        printf("Choisissez le numéro de colonne : \n");
        y = checkInt(3, 1) - 1;
        verifMove = moveValid(&myGrid[x][y], order);

        while (verifMove == 0) {
            printf("Coup impossible veuillez réessayer! \n");
            printf("Joueur %d, veuillez choisir une case à jouer (entrez le numéro de ligne de la case): \n", order);
            x = checkInt(3, 1) - 1;
            printf("Choisissez le numéro de colonne : \n");
            y = checkInt(3, 1) - 1;
            verifMove = moveValid(&myGrid[x][y], order);
        }

        displayGrid(myGrid);
        verifWin = checkWin(myGrid);

        if(verifWin == 0){
            // Tour de l'ordinateur
            moveComputer(myGrid, numComputer);
            displayGrid(myGrid);
            verifWin = checkWin(myGrid);
        }


    }
    if (verifWin == order) {
        printf("Vous avez gagné! \n");
    } else if (verifWin == 3) {
        printf("Égalité! \n");
    }else{
        printf("L'ordinateur a gagné \n");
    }
}

