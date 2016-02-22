//
// Created by stardisblue on 12/02/16.
//

#include "Generator.h"
#include "Corolle.h"
#include "File/FileIn.h"


Generator::Generator(Jeu jeu)
{
    this->jeu = jeu;
    plateau = new Piece[jeu.getSize()][jeu.getSize()];
    disponibles = new bool[jeu.getSize() * jeu.getSize()]{true};
}

/**
 * Initialise l'ordre de parcours
 *
 * TODO : automatiser la création de la table
 */
void Generator::prerequisGeneration(int corolle_type)
{
    if (corolle_type == Corolle::C_1) {
        corolle_size = Corolle::SIZE_C_1;
        coordonnees = {{0, 0, POS_TYPE_COIN},
                       {0, 1, POS_TYPE_BORD_LEFT},
                       {1, 0, POS_TYPE_BORD_TOP},
                       {0, 2, POS_TYPE_BORD_LEFT},
                       {1, 1, POS_TYPE_INTERIEUR},
                       {2, 0, POS_TYPE_BORD_TOP}};
    } else {
        perror("Valeur de int corolle_type invalide");
    }
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
    FileIn;
    generationRecursive(piece_tab, 0);
}

/**
 * Compare deux bord de deux pièces
 *
 * @param Piece a La premiere pièce a comparer
 * @param Piece b La deuxieme pièce a comparer
 * @param int side_a le bord a comparer de la pièce a
 * @param int side_b le bord a comparer de la pièce b
 */
static const bool Generator::compareColors(Piece a, Piece b, int side_a, int side_b) const
{
    return a.getColor(side_a) == b.getColor(side_b);
}

/**
 * Compare un bord d'une pièce à la position souhaitée
 *
 * @return true si le les bords correspondent ou si le voisin est vide
 */
const bool Generator::compareSides(Piece piece, int x, int y, int side_to_compare) const
{
    if (side_to_compare == Piece::TOP && y > 0) { // on verifie en haut
        if (plateau[x][y - 1] == NULL) {
            return true;
        } else {
            return compareColors(piece, plateau[x][y - 1], Piece::TOP, Piece::BOTTOM);
        }
    } else if (side_to_compare == Piece::RIGHT && x < jeu.getSize() - 1) {// on verifie a droite
        if (plateau[x + 1][y] == NULL) {
            return true;
        } else {
            return compareColors(piece, plateau[x + 1][y], Piece::RIGHT, Piece::LEFT);
        }
    } else if (side_to_compare == Piece::BOTTOM && y < jeu.getSize() - 1) { // on verifie en bas
        if (plateau[x][y - 1] == NULL) {
            return true;
        } else {
            return compareColors(piece, plateau[x][y - 1], Piece::BOTTOM, Piece::TOP);
        }
    } else if (side_to_compare == Piece::LEFT && x > 0) { // on verifie a gauche
        if (plateau[x - 1][y] == NULL) {
            return true;
        } else {
            return compareColors(piece, plateau[x - 1][y], Piece::LEFT, Piece::RIGHT);
        }
    } else {
        perror("Valeur de int side_to_compare est invalide");
        return false;
    }
}

/**
 * Vérifie si on peut mettre la pièce sur le plateau
 *
 * TODO : ajouter pièce de bord (4 vérifications possibles)
 */
const bool Generator::canPutPiece(Piece piece, int x, int y, int position_type) const
{
    if (position_type > POS_TYPE_BORD) { //POS_TYPE_BORD_*
        bool can_put_piece = true; // on suppose que ca marche de base XD

        if (position_type != POS_TYPE_BORD_TOP) {
            can_put_piece &= compareSides(piece, x, y, Piece::TOP);
        }
        if (position_type != POS_TYPE_BORD_RIGHT) {
            can_put_piece &= compareSides(piece, x, y, Piece::RIGHT);
        }
        if (position_type != POS_TYPE_BORD_BOTTOM) {
            can_put_piece &= compareSides(piece, x, y, Piece::BOTTOM);
        }
        if (position_type != POS_TYPE_BORD_LEFT) {
            can_put_piece &= compareSides(piece, x, y, Piece::LEFT);
        }

        return can_put_piece;
    } else if (position_type == POS_TYPE_INTERIEUR) {
        return compareSides(piece, x, y, Piece::TOP) && compareSides(piece, x, y, Piece::RIGHT) &&
               compareSides(piece, x, y, Piece::BOTTOM) && compareSides(piece, x, y, Piece::LEFT)
    } else {
        perror("Valeur int position_type incorrecte");
        return false;
    }
}

/**
 * Met la piece sur le plateau
 */
void Generator::putPiece(int numero_piece, int x, int y, Piece piece) const
{
    plateau[x][y] = piece;
    disponibles[numero_piece] = false;
}

/**
 * Enleve la piece du plateau
 */
void Generator::pickOffPiece(int numero_piece, int x, int y) const
{
    plateau[x][y] = NULL;
    disponibles[numero_piece] = true;
}

/**
 * Génére et parcours récursivement l'arbre des possibilités
 *
 * TODO : marche seulement pour h1 (ajouter 4 pos_type_coin) méthode : parcours en profondeur
 */
void Generator::generationRecursive(Piece piece_tab[], int position) const
{
    if (position < corolle_size) {
        int position_type = coordonnees[position][POS_TYPE],
                coord_x = coordonnees[position][POS_X],
                coord_y = coordonnees[position][POS_Y];

        if (position_type == POS_TYPE_COIN) {
            for (int numero_piece = 0; numero_piece < 4; ++numero_piece) {
                Piece piece_coin = jeu.getTabC()[numero_piece];
                if (disponibles[numero_piece]) {
                    piece_coin.setRotation(Piece::LEFT);
                    putPiece(numero_piece, coord_x, coord_y, piece_coin);

                    //TODO : a optimiser position +1 ( duplication à chaque boucle récursive
                    generationRecursive(piece_tab, position + 1);
                    pickOffPiece(numero_piece, coord_x, coord_y);
                }
            }
        } else if (position_type > POS_TYPE_BORD) {
            for (int numero_piece = 0; numero_piece < (jeu.getSize() - 2) * 4; ++numero_piece) {

                if (disponibles[numero_piece]) {
                    Piece piece_bord = jeu.getTabB()[numero_piece];

                    if (position_type == POS_TYPE_BORD_RIGHT) {
                        piece_bord.setRotation(Piece::RIGHT);
                    } else if (position_type == POS_TYPE_BORD_BOTTOM) {
                        piece_bord.setRotation(Piece::BOTTOM);
                    } else if (position_type == POS_TYPE_BORD_LEFT) {
                        piece_bord.setRotation(Piece::LEFT);
                    }

                    if (canPutPiece(piece_bord, coord_x, coord_y, position_type)) {
                        putPiece(numero_piece, coord_x, coord_y, piece_bord);

                        // TODO : voir todo (l.174)
                        generationRecursive(piece_tab, position + 1);
                        pickOffPiece(numero_piece, coord_x, coord_y);
                    }
                }
            }
        } else if (position_type == POS_TYPE_INTERIEUR) {
            for (int numero_piece = 0; numero_piece < (jeu.getSize() - 2) * (jeu.getSize() - 2); ++numero_piece) {

                if (disponibles[numero_piece]) {
                    Piece piece_interieur = jeu.getTabI()[numero_piece];
                    for (int rotation = 0; rotation < 4; ++rotation) {

                        piece_interieur.setRotation(rotation);
                        if (canPutPiece(piece_interieur, coord_x, coord_y, position_type)) {
                            putPiece(numero_piece, coord_x, coord_y, piece_interieur);

                            // TODO : voir todo (l.174)
                            generationRecursive(piece_tab, position + 1);
                            pickOffPiece(numero_piece, coord_x, coord_y);
                        }
                    }
                }
            }
        }
    } else if (position == corolle_size) {
        int coord_x, coord_y;
        for (int i = 0; i < corolle_size; ++i) {
            coord_x = coordonnees[i][POS_X];
            coord_y = coordonnees[i][POS_Y];
            piece_tab[i] = plateau[coord_x][coord_y];
        }
    }
}

// Inutile pour l'instant
static const int Generator::pieceTypeByPosition(int x, int y) const
{
    if (x == 0 && y == 0) {
        return POS_TYPE_COIN;
    } else if (x == 0) {
        return POS_TYPE_BORD_LEFT;
    } else if (y == 0) {
        return POS_TYPE_BORD_TOP;
    } else {
        return POS_TYPE_INTERIEUR;
    }

}