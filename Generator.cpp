//
// Created by stardisblue on 12/02/16.
//

#include "Generator.h"
#include "Corolle.h"


Generator::Generator(Jeu jeu)
{
    this->jeu = jeu;
    plateau = new Piece[jeu.getSize()][jeu.getSize()];
    disponibles = new bool[jeu.getSize() * jeu.getSize()]{true};
}

/**
 * Lance la génération des possibilités de la corolle
 *
 * @param int type_corolle le type de la corolle.
 */
void Generator::initGeneration(int corolle_type)
{
    // preparation de tous les elements utilises dans la recursivite
    prerequisGeneration(corolle_type);

    // nombre de piece de la corolle suivant le type de la corolle a générer
    Piece piece_tab[corolle_size];

    generationRecursive(piece_tab, 0);
}


void Generator::generationRecursive(Piece piece_tab[], int position)
{
    int type = pieceTypeByPosition((int *) coordonnees[position]);
    if (type == TYPE_COIN) {
        for (int numero_piece = 0; numero_piece < 4; ++numero_piece) {
            if (disponibles[numero_piece]) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    if (jeu.getTabC()[numero_piece].getColor(TOP) == 0 &&
                        jeu.getTabC()[numero_piece].getColor(LEFT) == 0) {
                        jeu.getTabC()[numero_piece].setRotation(rotation);
                        disponibles[numero_piece] = false;
                        plateau[coordonnees[position][0]][coordonnees[position][1]];
                    }
                }
            }
        }
    } else if (type == TYPE_BORD) {

    } else if (type == TYPE_COIN) {

    }
}

const bool Generator::compareColors(Piece a, Piece b, int orientation_a, int orientation_b) const
{
    return a.getColor(orientation_a) == b.getColor(orientation_b);
}

void Generator::prerequisGeneration(int corolle_type)
{
    if (corolle_type == Corolle::C_1) {
        corolle_size = Corolle::SIZE_C_1;
        coordonnees = new int[][2]{{0, 0},
                                   {0, 1},
                                   {1, 0},
                                   {2, 0},
                                   {1, 1},
                                   {0, 2}};
    }
}

const int Generator::pieceTypeByPosition(int position[2]) const
{
    if (position[0] == 0 && position[1] == 0) {
        return TYPE_COIN;
    } else if (position[0] == 0 || position[1] == 0) {
        return TYPE_BORD;
    } else {
        return TYPE_INTERIEUR;
    }
}