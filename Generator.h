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

    const bool compareColors(Piece a, Piece b, int orientation_a, int position_b) const;

    void prerequisGeneration(int corolle_type);

    const int pieceTypeByPosition(int *position) const;

private:

    Jeu jeu;
    Piece *plateau;
    bool *disponibles;
    int *coordonnees;
    int corolle_size;

    void generationRecursive(Piece *piece_tab, int position);

    static const int TYPE_COIN = 0;
    static const int TYPE_BORD = 1;
    static const int TYPE_INTERIEUR = 2;


};


#endif //GENERATOR_H
