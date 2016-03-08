#include "Generator.h"


Generator::Generator(Jeu jeu) : jeu(jeu)
{
    cout << "Generator " << jeu.getSize() << endl;
    file_out = NULL;

    jeu_size = jeu.getSize();
    for (int i = 0; i < JEU_PIECES_MAX; ++i) {
        disponibles[i] = true;
    }

    cout << "End Generator " << endl;
}

const int Generator::pieceTypeByPosition(int x, int y)
{
    //cout << "PieceTypeByPosition" << endl;
    if (x == 0 && y == 0) {
        return POS_TYPE_COIN_NW;
    } /*else if (x == jeu_size - 1 && y == 0) {
        return POS_TYPE_COIN_NE;
    } else if (x == jeu_size - 1 && y == jeu_size - 1) {
        return POS_TYPE_COIN_SE;
    } else if (x == 0 && y == jeu_size - 1) {
        return POS_TYPE_COIN_SW;
    }*/ else if (x == 0) {
        return POS_TYPE_BORD_LEFT;
    } else if (y == 0) {
        return POS_TYPE_BORD_TOP;
    } else {
        return POS_TYPE_INTERIEUR;
    }

}

/**
 * Positionnement diagonale des pièces,c'est cette fonction qui définit la forme de la corolle,
 * en changeant l'orientation du positionnement en fonction du hamming définit.
 *
 * @param int position_nb ordre de positionnement pour reformer la corolle.
 * @param int orientation le sens du positionnement des pièces sur la corolle. initialement définit à 0
 * @param int x, position x d'origine
 * @param int y, position y d'origine
 * @param int iteration entier pour savoir le nombre de pièce à placer dans une orientation, dépend du hamming.
 */
void Generator::parcoursDiagonal(int &position_nb, int orientation, int x, int y, int iteration)
{
    int to_x, to_y;
    int temp_x, temp_y;
    int i;
    do {
        if (orientation == SE) {
            to_x = 1;
            to_y = 1;
        } else if (orientation == SW) {
            to_x = -1;
            to_y = 1;
        } else if (orientation == NW) {
            to_x = -1;
            to_y = -1;
        } else if (orientation == NE) {
            to_x = 1;
            to_y = -1;
        }

        for (i = 0; i < iteration && (orientation != NE || i < iteration - 1); i++) {
            temp_x = x + (i + 1) * to_x;
            temp_y = y + (i + 1) * to_y;
            if (temp_x >= 0 && temp_x < jeu_size && temp_y >= 0 && temp_y < jeu_size) {
                coordonnees[position_nb][POS_X] = temp_x;
                coordonnees[position_nb][POS_Y] = temp_y;
                coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(temp_x, temp_y);
                position_nb++;
            }
        }
        if (orientation == NE) {
            orientation = SE;
        } else {
            orientation++;
        }
        x = temp_x;
        y = temp_y;
    } while (orientation != SE);

    return;
}

/**
 * Positionne une pièce au dessus de la précédente en utilisant les coordonnées d'origine x et y.
 * @param int corolle_type : le type de la corolle en fonction de la position de départ
 * @param int hamming : taille de la corolle
 */
void Generator::incrementationHamming(int &position_nb, int x, int y)
{
    if (x >= 0 && x < jeu_size && y >= 0 && y < jeu_size) {
        coordonnees[position_nb][POS_X] = x;
        coordonnees[position_nb][POS_Y] = y;
        coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(x, y);
        position_nb++;
    }
}

/**
 * Définit l'ordre de parcours de la corolle en faisant appel à 2 fonctions annexe pour le positionnement digonale et le positionnement "Nord"
 * @param int corolle_type : le type de la corolle en fonction de la position de départ
 * @param int hamming : taille de la corolle
 */
void Generator::parcoursRecursif(int &position_nb, int x, int y)
{
    incrementationHamming(position_nb, x, y); //placement de la première pièce
    int iteration = 1; // initialisation du nombre d'itération
    while (iteration <= corolle_hamming) {
        y--; //On décrémente la position y pour
        incrementationHamming(position_nb, x,
                              y); //placement de la pièce d'origine qui va initialiser le parcours diagonal
        parcoursDiagonal(position_nb, SE, x, y, iteration); // SE = orientation de départ
        iteration++;
    }
}

/**
 * Initialise l'ordre de parcours
 * @param int corolle_type : le type de la corolle en fonction de la position de départ
 * @param int hamming : taille de la corolle
 */
void Generator::prerequisGeneration(int corolle_type, int hamming)
{
    cout << "prerequisGeneration" << endl;

    corolle_hamming = hamming; // hamming de la corolle
    this->corolle_type = corolle_type;
    int x = 1;
    int y = 1;
    int position_nb = 0;


    if (x < 0 || y < 0 || position_nb < 0 || corolle_hamming < 0) {
        cerr << "Bad coordinates";
        exit(EXIT_FAILURE);
    }

    parcoursRecursif(position_nb, x, y);

    // TODO : a enlever test case
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 3; j++) {
            cout << coordonnees[i][j] << " ";
        }
        cout << " " << endl;
    }
}

/**
 * Lance la génération des possibilités de la corolle
 *
 * @param int type_corolle le type de la corolle.
 */
void Generator::initGeneration(int corolle_type, int hamming)
{

    cout << "InitGeneration" << endl;
    // preparation de tous les elements utilises dans la recursivite
    prerequisGeneration(corolle_type, hamming);

    for (int i = 0; i < jeu_size * jeu_size; ++i) {
        jeu.getJeu()[i].toStringDetail();
    }


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
const bool Generator::compareColors(Piece a, Piece b, int side_a, int side_b)
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
    } else if (side_to_compare == Piece::RIGHT && x < jeu_size - 1) {// on verifie a droite
        if (plateau[x + 1][y].getId() == -1) {
            return true;
        } else {
            return compareColors(piece, plateau[x + 1][y], Piece::RIGHT, Piece::LEFT);
        }
    } else if (side_to_compare == Piece::BOTTOM && y < jeu_size - 1) { // on verifie en bas
        if (plateau[x][y + 1].getId() == -1) {
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
void Generator::putPiece(int x, int y, Piece piece)
{
    plateau[x][y] = piece;
    disponibles[piece.getId()] = false;
}

/**
 * Enleve la piece du plateau
 */
void Generator::pickOffPiece(int numero_piece, int x, int y)
{
    Piece piece_vide;
    plateau[x][y] = piece_vide;
    disponibles[numero_piece] = true;
}

void Generator::writeInFile(Corolle &corolle)
{
    if (file_out != NULL) { // si un fichier est ouvert
        if (file_out->piece_number == corolle.getPieces()[0].getId()
            && file_out->rotation == corolle.getRotation()) { // si c'est le bon fichier
            file_out->put(corolle);
        } else {// si c'est pas le bon on le ferme et on ouvre le bon
            file_out->close();

            delete file_out;

            file_out = new FileOut(jeu_size, corolle.getHamming(), corolle.getType(), corolle.getPieces()[0].getId(),
                                   corolle.getRotation());
            file_out->open();
            file_out->put(corolle);
        }
    } else {// si aucun fichier n'est ouvert, on ouvre le bon
        file_out = new FileOut(jeu_size, corolle.getHamming(), corolle.getType(), corolle.getPieces()[0].getId(),
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
            for (int numero_piece = 0; numero_piece < 4; numero_piece++) { // parcours des coins

                Piece piece_coin = jeu.getTabC()[numero_piece];

                if (disponibles[piece_coin.getId()]) { // si la piece est disponible
                    if (position_type == POS_TYPE_COIN_NW) { //bonne orientation de la piece de coin
                        piece_coin.setRotation(Piece::RIGHT);
                    } else if (position_type == POS_TYPE_COIN_NE) { //bonne orientation de la piece de coin
                        piece_coin.setRotation(Piece::TOP);
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
            for (int numero_piece = 0; numero_piece < ((jeu_size - 2) * 4); ++numero_piece) {
                // parcours des pieces de bord

                Piece piece_bord = jeu.getTabB()[numero_piece];

                if (disponibles[piece_bord.getId()]) {// is la piece est disponible

                    if (position_type == POS_TYPE_BORD_TOP) { // bonne orientation de la piece de bord
                        piece_bord.setRotation(Piece::TOP);
                    } else if (position_type == POS_TYPE_BORD_RIGHT) { // bonne orientation de la piece de bord
                        piece_bord.setRotation(Piece::LEFT);
                    } else if (position_type == POS_TYPE_BORD_BOTTOM) {
                        piece_bord.setRotation(Piece::BOTTOM);
                    } else if (position_type == POS_TYPE_BORD_LEFT) {
                        piece_bord.setRotation(Piece::RIGHT);
                    }

                    if (canPutPiece(piece_bord, coord_x, coord_y, position_type)) { // verifie si on peut la placer
                        putPiece(coord_x, coord_y, piece_bord);
                        ++position;
                        generationRecursive(position);
                        --position;
                        pickOffPiece(piece_bord.getId(), coord_x, coord_y);
                    }
                }
            }
        } else if (position_type == POS_TYPE_INTERIEUR) { // si la position est interieure
            for (int numero_piece = 0; numero_piece < (jeu_size - 2) * (jeu_size - 2); ++numero_piece) {

                Piece piece_interieur = jeu.getTabI()[numero_piece];

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
        cerr << corolle.toString() << endl;

        writeInFile(corolle);
    }
}

// Inutile pour l'instant