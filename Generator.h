/*
 * Created by stardisblue on 12/02/16.
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdlib.h>
#include <time.h>

#include "Jeu.h"
#include "Corolle.h"
#include "File/FileOut.h"


class Generator
{
public:
    Generator(Jeu jeu);

    void multipleGeneration(const int end = 3, const int begin = 1);

    void initGeneration(const int &x, const int &y, const int hamming);

    void parcoursBruteForce(const int &type_parcours);

private:

    static const int POS_X = 0;
    static const int POS_Y = 1;
    static const int POS_TYPE = 2;

    static const int POS_TYPE_COIN_NW = 1;
    static const int POS_TYPE_COIN_NE = 2;
    static const int POS_TYPE_COIN_SE = 3;
    static const int POS_TYPE_COIN_SW = 4;
    static const int POS_TYPE_COIN = 5;
    static const int POS_TYPE_EXT = 7;

    static const int POS_TYPE_BORD = 10;
    static const int POS_TYPE_BORD_TOP = 11;
    static const int POS_TYPE_BORD_LEFT = 12;
    static const int POS_TYPE_BORD_BOTTOM = 13;
    static const int POS_TYPE_BORD_RIGHT = 14;

    static const int POS_TYPE_INTERIEUR = 6;

    static const int JEU_SIZE_MAX = 16;
    static const int JEU_PIECES_MAX = 256;

    static const int SE = 0;
    static const int SW = 1;
    static const int NW = 2;
    static const int NE = 3;

    static const int PARCOURS_COROLLE = 0;
    static const int PARCOURS_ROW = 1;
    static const int PARCOURS_DIAGONAL = 2;

    Jeu jeu;

    int jeu_size;
    Piece plateau[JEU_SIZE_MAX][JEU_SIZE_MAX];

    bool disponibles[JEU_PIECES_MAX];
    FileOut *file_out;
    int coordonnees[25][3];

    int corolle_size;
    int corolle_hamming;

    long long nb_noeuds;
    long long nb_solutions;
    long long nb_solutions_max;

    void diagonalWalker(int &position_nb, int &x, int &y, const int orientation, const int &length);

    void coordinatesCreator(int x, int y, const int type_parcours);

    void addCoordinate(int &position_nb, const int &x, const int &y);

    const int pieceTypeByPosition(const int &x, const int &y);

    const bool compareColors(Piece &a, Piece &b, const int side_a, const int side_b);

    const bool compareSides(Piece &piece, const int &x, const int &y, const int side_to_compare);

    const bool canPutPiece(Piece &piece, const int &x, const int &y, const int position_type);

    void putPiece(const int &x, const int &y, Piece &piece);

    void pickOffPiece(const int &numero_piece, const int &x, const int &y);

    void writeInFile(Corolle &corolle);

    void generationRecursive(int &position, int &lastdepth);

    void putPieceEvent();

    void pickOffPieceEvent();

    void solutionFoundEvent();
    void writeInFile(Corolle &corolle, string &append, int &lastdepth);
};


#endif //GENERATOR_H
