/*
 * Created by stardisblue on 12/02/16.
 */

#ifndef GENERATOR_H
#define GENERATOR_H
#include <stdlib.h> 

#include "Jeu.h"
#include "Corolle.h"
#include "File/FileOut.h"

class Generator
{
public:
    Generator(Jeu jeu);

    void initGeneration(int corolle_type, int hamming);

private:

    static const int POS_X = 0;
    static const int POS_Y = 1;
    static const int POS_TYPE = 2;

    static const int POS_TYPE_COIN_NW = 1;
    static const int POS_TYPE_COIN_NE = 2;
    static const int POS_TYPE_COIN_SE = 3;
    static const int POS_TYPE_COIN_SW = 4;
    static const int POS_TYPE_COIN = 5;

    static const int POS_TYPE_BORD = 10;
    static const int POS_TYPE_BORD_TOP = 11;
    static const int POS_TYPE_BORD_LEFT = 12;
    static const int POS_TYPE_BORD_BOTTOM = 13;
    static const int POS_TYPE_BORD_RIGHT = 14;

    static const int POS_TYPE_INTERIEUR = 6;

    static const int JEU_SIZE_MAX = 16;
    static const int JEU_PIECES_MAX = 256;

    static const int NW = 0;
    static const int NE = 1;
    static const int SE = 2;
    static const int SW = 3;

    Jeu jeu;

    int jeu_size;
    Piece plateau[JEU_SIZE_MAX][JEU_SIZE_MAX];

    bool disponibles[JEU_PIECES_MAX];
    FileOut *file_out;
    int coordonnees[25][3];
    int corolle_type;

    int corolle_size;
    int corolle_hamming;

    void parcoursDiagonal(int origin, int orientation, int size, int x, int y);

    const int pieceTypeByPosition(int x, int y);

    void coordonneesCreator();

    void prerequisGeneration(int corolle_type, int hamming);

    static const bool compareColors(Piece a, Piece b, int side_a, int side_b);

    const bool compareSides(Piece piece, int x, int y, int side_to_compare);

    const bool canPutPiece(Piece piece, int x, int y, int position_type);

    void putPiece(int x, int y, Piece piece);

    void pickOffPiece(int numero_piece, int x, int y);

    void writeInFile(Corolle &corolle);

    void generationRecursive(int &position);
};


#endif //GENERATOR_H
