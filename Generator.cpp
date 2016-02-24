//
// Created by stardisblue on 12/02/16.
//

#include "Generator.h"


Generator::Generator(Jeu jeu) : jeu(jeu)
{

    for (int i = 0; i < jeu.getSize(); ++i) {
        plateau[i] = new Piece[jeu.getSize()];
    }

    disponibles = new bool[jeu.getSize() * jeu.getSize()]{true};
}

/**
 * Initialise l'ordre de parcours
 *
 * TODO : automatiser la création de la table
 */
void Generator::prerequisGeneration(int corolle_type, int hamming)
{
    this->corolle_type = corolle_type;

    if (corolle_type == Corolle::C) {
        corolle_size = Corolle::SIZE_C_1;// nombre de piece de la corolle suivant le type de la corolle a générer
        corolle_hamming = hamming; // hamming de la corolle

        coordonneesCreator();

    } else {
        perror("Valeur de int corolle_type invalide");
    }
}

/**
 * Lance la génération des possibilités de la corolle
 *
 * @param int type_corolle le type de la corolle.
 */
void Generator::initGeneration(int corolle_type, int hamming)
{
    // preparation de tous les elements utilises dans la recursivite
    prerequisGeneration(corolle_type, hamming);

    int position = 0; // initialisation du parcours
    generationRecursive(position);
    if (file_out->isOpen()) {
        file_out->close(); //fermeture eventuels des fichiers ouverts
    }
}

/**
 * Compare deux bord de deux pièces
 *
 * @param Piece a La premiere pièce a comparer
 * @param Piece b La deuxieme pièce a comparer
 * @param int side_a le bord a comparer de la pièce a
 * @param int side_b le bord a comparer de la pièce b
 */
static const bool compareColors(Piece a, Piece b, int side_a, int side_b)
{
    return a.getColor(side_a) == b.getColor(side_b);
}

/**
 * Compare un bord d'une pièce à la position souhaitée
 *
 * @return true si le les bords correspondent ou si le voisin est vide
 */
const bool Generator::compareSides(Piece piece, int x, int y, int side_to_compare)
{
    if (side_to_compare == Piece::TOP && y > 0) { // on verifie en haut
        if (plateau[x][y - 1].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x][y - 1], Piece::TOP, Piece::BOTTOM);
        }
    } else if (side_to_compare == Piece::RIGHT && x < jeu.getSize() - 1) {// on verifie a droite
        if (plateau[x + 1][y].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x + 1][y], Piece::RIGHT, Piece::LEFT);
        }
    } else if (side_to_compare == Piece::BOTTOM && y < jeu.getSize() - 1) { // on verifie en bas
        if (plateau[x][y - 1].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x][y - 1], Piece::BOTTOM, Piece::TOP);
        }
    } else if (side_to_compare == Piece::LEFT && x > 0) { // on verifie a gauche
        if (plateau[x - 1][y].getId() == -1) {
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
 */
const bool Generator::canPutPiece(Piece piece, int x, int y, int position_type)
{
    if (position_type > POS_TYPE_BORD) { //POS_TYPE_BORD_* on verifie les cotés non-bord
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
    } else if (position_type < POS_TYPE_COIN) { //POS_TYPE_COIN_* on verifie les cotés non bords
        if (position_type == POS_TYPE_COIN_NW) {
            return compareSides(piece, x, y, Piece::RIGHT) && compareSides(piece, x, y, Piece::BOTTOM);
        } else if (position_type == POS_TYPE_COIN_NE) {
            return compareSides(piece, x, y, Piece::BOTTOM) && compareSides(piece, x, y, Piece::LEFT);
        } else if (position_type == POS_TYPE_COIN_SE) {
            return compareSides(piece, x, y, Piece::TOP) && compareSides(piece, x, y, Piece::LEFT);
        } else if (position_type == POS_TYPE_COIN_SW) {
            return compareSides(piece, x, y, Piece::TOP) && compareSides(piece, x, y, Piece::RIGHT);
        }
    } else if (position_type == POS_TYPE_INTERIEUR) { // on verifie tout les cotes pour
        return compareSides(piece, x, y, Piece::TOP) && compareSides(piece, x, y, Piece::RIGHT) &&
               compareSides(piece, x, y, Piece::BOTTOM) && compareSides(piece, x, y, Piece::LEFT);
    } else {
        perror("Valeur int position_type incorrecte");
    }

    return false;
}

/**
 * Met la piece sur le plateau
 */
void Generator::putPiece(int x, int y, Piece piece) const
{
    plateau[x][y] = piece;
    disponibles[piece.getId()] = false;
}

/**
 * Enleve la piece du plateau
 */
void Generator::pickOffPiece(int numero_piece, int x, int y) const
{
    Piece piece_vide;
    plateau[x][y] = piece_vide;
    disponibles[numero_piece] = true;
}

void Generator::writeInFile(const Corolle corolle)
{
    if (file_out->isOpen()) { // si un fichier est ouvert
        if (file_out->piece_number == corolle.getPieces()[0].getId()
            && file_out->rotation == corolle.getRotation()) { // si c'est le bon fichier
            file_out->put(corolle);
        } else {// si c'est pas le bon on le ferme et on ouvre le bon
            file_out->close();

            FileOut *new_file = new FileOut(jeu.getSize(), corolle.getHamming(), corolle.getType(),
                                            corolle.getPieces()[0].getId(),
                                            corolle.getRotation());
            file_out = new_file;
            file_out->put(corolle);
        }
    } else {// si aucun fichier n'est ouvert, on ouvre le bon
        file_out = new FileOut(jeu.getSize(), corolle.getHamming(), corolle.getType(), corolle.getPieces()[0].getId(),
                               corolle.getRotation());
        file_out->open();
        file_out->put(corolle);
    }


}

/**
 * Génére et parcours récursivement l'arbre des possibilités
 *
 */
void Generator::generationRecursive(int &position)
{
    if (position < corolle_size) { // si la corolle est incomplete
        int position_type = coordonnees[position][POS_TYPE],
                coord_x = coordonnees[position][POS_X],
                coord_y = coordonnees[position][POS_Y];

        if (position_type < POS_TYPE_COIN) { // si position est un coin
            Piece piece_coin;
            for (int numero_piece = 0; numero_piece < 4; ++numero_piece) { // parcours des coins

                piece_coin = jeu.getTabC()[numero_piece];

                if (disponibles[piece_coin.getId()]) { // si la piece est disponible
                    if (position_type == POS_TYPE_COIN_NW) { //bonne orientation de la piece de coin
                        piece_coin.setRotation(Piece::RIGHT);
                    } else if (position_type == POS_TYPE_COIN_SE) {
                        piece_coin.setRotation(Piece::LEFT);
                    } else if (position_type == POS_TYPE_COIN_SW) {
                        piece_coin.setRotation(Piece::BOTTOM);
                    }

                    if (canPutPiece(piece_coin, coord_x, coord_y, position_type)) { // vérifie si la piece est placable
                        putPiece(coord_x, coord_y, piece_coin);
                        generationRecursive(++position);
                        --position;
                        pickOffPiece(piece_coin.getId(), coord_x, coord_y);
                    }
                }
            }
        } else if (position_type > POS_TYPE_BORD) { // si la position est un bord
            Piece piece_bord;
            for (int numero_piece = 0;
                 numero_piece < (jeu.getSize() - 2) * 4;
                 ++numero_piece) {// parcours des pieces de bord

                piece_bord = jeu.getTabB()[numero_piece];

                if (disponibles[piece_bord.getId()]) {// is la piece est disponible

                    if (position_type == POS_TYPE_BORD_RIGHT) { // bonne orientation de la piece de bord
                        piece_bord.setRotation(Piece::LEFT);
                    } else if (position_type == POS_TYPE_BORD_BOTTOM) {
                        piece_bord.setRotation(Piece::BOTTOM);
                    } else if (position_type == POS_TYPE_BORD_LEFT) {
                        piece_bord.setRotation(Piece::RIGHT);
                    }

                    if (canPutPiece(piece_bord, coord_x, coord_y, position_type)) { // verifie si on peut la placer
                        putPiece(coord_x, coord_y, piece_bord);
                        generationRecursive(++position);
                        --position;
                        pickOffPiece(piece_bord.getId(), coord_x, coord_y);
                    }
                }
            }
        } else if (position_type == POS_TYPE_INTERIEUR) { // si la position est interieure
            Piece piece_interieur;
            for (int numero_piece = 0; numero_piece < (jeu.getSize() - 2) * (jeu.getSize() - 2); ++numero_piece) {

                piece_interieur = jeu.getTabI()[numero_piece];

                if (disponibles[piece_interieur.getId()]) { // si la piece est disponible
                    for (int rotation = 0; rotation < 4; ++rotation) {// test  des rotations possibles

                        piece_interieur.setRotation(rotation);// rotation de la piece

                        if (canPutPiece(piece_interieur, coord_x, coord_y, position_type)) {// si la piece est placable
                            putPiece(coord_x, coord_y, piece_interieur);
                            generationRecursive(++position);
                            --position; // fin de la corolle dépilage
                            pickOffPiece(piece_interieur.getId(), coord_x, coord_y);
                        }
                    }
                }
            }
        }
    } else if (position == corolle_size) {
        int coord_x, coord_y;
        Piece piece_tab[corolle_size];
        for (int i = 0; i < corolle_size; ++i) { // Creation de la corolle
            coord_x = coordonnees[i][POS_X];
            coord_y = coordonnees[i][POS_Y];
            piece_tab[i] = plateau[coord_x][coord_y];
        }

        Corolle corolle(piece_tab, corolle_size, corolle_type, corolle_hamming);
        writeInFile(corolle);
    }
}

// Inutile pour l'instant

void Generator::coordonneesCreator()
{

    if (corolle_type == Corolle::C) {
        int cpt = 0,
                x = 0,
                y = 0;

        coordonnees[cpt] = new int[3]{x, y, pieceTypeByPosition(x, y)};
        x++;
        cpt++;

        while (x < corolle_hamming + 1) {

            if (x != 0) {
                y++;
                x--;
                coordonnees[cpt++] = new int[3]{x, y, pieceTypeByPosition(x, y)};

            } else {
                x = y + 1;
                y = 0;
            }
        }
    }
}

const int Generator::pieceTypeByPosition(int x, int y)
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