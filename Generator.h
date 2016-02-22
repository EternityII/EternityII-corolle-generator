/*
 * Created by stardisblue on 12/02/16.
 */

#ifndef GENERATOR_H
#define GENERATOR_H


#include "Jeu.h"

class Generator
{
public:
    Generator(Jeu jeu);

    void initGeneration(int corolle_type);

    void prerequisGeneration(int corolle_type);


    static const int pieceTypeByPosition(int x, int y) const;

private:

    static const int POS_X = 0;

    static const int POS_Y = 1;

    static const int POS_TYPE = 2;

    static const int POS_TYPE_COIN = 0;
    static const int POS_TYPE_BORD = 10;
    static const int POS_TYPE_BORD_TOP = 11;
    static const int POS_TYPE_BORD_LEFT = 12;

    static const int POS_TYPE_BORD_BOTTOM = 13;
    static const int POS_TYPE_BORD_RIGHT = 14;
    static const int POS_TYPE_INTERIEUR = 2;
    Jeu jeu;
    Piece **plateau;
    bool *disponibles;

    int coordonnees[][3];
    int corolle_size;

    static const bool compareColors(Piece a, Piece b, int side_a, int side_b) const;

    const bool compareSides(Piece piece, int x, int y, int side_to_compare) const;

    const bool canPutPiece(Piece piece, int x, int y, int position_type) const;

    void putPiece(int numero_piece, int x, int y, Piece piece) const;

    void pickOffPiece(int numero_piece, int x, int y) const;

    void generationRecursive(Piece piece_tab[], int position) const;

};


#endif //GENERATOR_H
