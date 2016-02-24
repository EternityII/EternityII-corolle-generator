#ifndef JEU_H
#define JEU_H

#include <math.h>
#include <iostream>

#include "Piece.h"


class Jeu
{

public:

    Jeu(const int size); //constructeur
    int addPiece(Piece p); //Ajout d'une piece dans le jeu

    //Getters
    int getSize();

    Piece *getJeu();

    Piece *getTabC();

    Piece *getTabB();

    Piece *getTabI();


private:

    int size;
    Piece *jeu;
    Piece *TabC;
    Piece *TabB;
    Piece *TabI;

	int nb_pieces_presentes;
	int nb_pieces_tabC;
	int nb_pieces_tabB;
	int nb_pieces_tabI;

};

#endif
