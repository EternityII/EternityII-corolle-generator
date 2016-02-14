//
// Created by stardisblue on 12/02/16.
//

#include "Generator.h"
#include "Corolle.h"


Generator::Generator(Jeu jeu)
{
    this->jeu = jeu;
}

/**
 * Lance la génération des possibilités de la corolle
 *
 * @param int type_corolle le type de la corolle.
 */
void Generator::initGeneration(int type_corolle) const
{
    // TODO
    int nb_pieces = jeu.getSize() * jeu.getSize();
    int plateau[jeu.getSize()][jeu.getSize()];

    Piece *corolle_tab;
    if (type_corolle == Corolle::C_1) {
        corolle_tab = new Piece[Corolle::SIZE_C_1];
    } else if (type_corolle == Corolle::BC_1) {
        corolle_tab = new Piece[Corolle::SIZE_BC_1];
    } else if (type_corolle == Corolle::B_1) {
        corolle_tab = new Piece[Corolle::SIZE_B_1];
    } else if (type_corolle == Corolle::IBB_1) {
        corolle_tab = new Piece[Corolle::SIZE_IBB_1];
    } else if (type_corolle == Corolle::IB_1) {
        corolle_tab = new Piece[Corolle::SIZE_IB_1];
    } else if (type_corolle == Corolle::I_1) {
        corolle_tab = new Piece[Corolle::SIZE_I_1];
    }
}


const void Generator::generationRecursive(int *disponibles, int position, int size) const
{
    // TODO

}
