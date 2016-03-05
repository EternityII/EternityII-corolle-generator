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
    cout << "PieceTypeByPosition" << endl;
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
 * Génère les coordonnées pour la création d'une corolle
 */
void Generator::parcoursDiagonal(int &position_nb, int orientation, int size, int [] posxy, int iteration, bool nw)
{
/*
position_nb = ordre de positionnement pour reformer la corolle.
orientation = le sens du positionnement des pièces sur la corolle.
size = taille du plateau
posxy = coordonnées du point de départ
iteration = entier pour savoir le nombre de pièce à placer dans une orientation.
nw = booléen qui permet de stoper la récursivité.
*/
    if (posxy[POS_X] < 0 || posxy[POS_Y] < 0 || position_nb < 0 || orientation < 0) { 
        perror("Bad coordinates");
        exit(EXIT_FAILURE);
    }
    if (orientation == NW) {
        
        if(iteration == 0 || (iteration < hamming && nw == true)){
            posxy[POS_Y]--; 
            if(posxy[POS_X] >= 0 || posxy[POS_X] < size || posxy[POS_Y] >= 0 || posxy[POS_Y] < size) {
                coordonnees[position_nb][POS_X] = posxy[POS_X];
                coordonnees[position_nb][POS_Y] = posxy[POS_Y];
                coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(posxy[POS_X], posxy[POS_Y]);
                position_nb++;
            }
            iteration++;
            parcoursDiagonal(position_nb,orientation,size,posxy,iteration,nw);
        } else if(iteration == hamming && nw == true) {
            cout << "Le programme termine" << endl;
            exit(EXIT_SUCCESS);
        }
        else {
            for(int i = 0; i < iteration; i++) {
                posxy[POS_X]++;
                posxy[POS_Y]++;
                if(posxy[POS_X] >= 0 || posxy[POS_X] < size || posxy[POS_Y] >= 0 || posxy[POS_Y] < size) {
                    coordonnees[position_nb][POS_X] = posxy[POS_X];
                    coordonnees[position_nb][POS_Y] = posxy[POS_Y];
                    coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(posxy[POS_X], posxy[POS_Y]);
                    position_nb++;
                }
            }
            orientation = SW;
            nw = true;
            parcoursDiagonal(position_nb,orientation,size,posxy,iteration,nw);
        }
        
    } else if (orientation == SW) {
        for(int i = 0; i < iteration; i++) {
            posxy[POS_X]--;
            posxy[POS_Y]++;
            if(posxy[POS_X] >= 0 || posxy[POS_X] < size || posxy[POS_Y] >= 0 || posxy[POS_Y] < size) {
                coordonnees[position_nb][POS_X] = posxy[POS_X];
                coordonnees[position_nb][POS_Y] = posxy[POS_Y];
                coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(posxy[POS_X], posxy[POS_Y]);
                position_nb++;
            }
        }
        orientation = SE;
        parcoursDiagonal(position_nb,orientation,size,posxy,iteration,nw);
    } else if (orientation == SE) {
        for(int i = 0; i < iteration; i++) {
            posxy[POS_X]--;
            posxy[POS_Y]--;
            if(posxy[POS_X] >= 0 || posxy[POS_X] < size || posxy[POS_Y] >= 0 || posxy[POS_Y] < size) {
                coordonnees[position_nb][POS_X] = posxy[POS_X];
                coordonnees[position_nb][POS_Y] = posxy[POS_Y];
                coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(posxy[POS_X], posxy[POS_Y]);
                position_nb++;
            }
        }
        orientation = NE;
        parcoursDiagonal(position_nb,orientation,size,posxy,iteration,nw);
        
    } else if (orientation == NE) {
        for(int i = 0; i < iteration; i++) {
            posxy[POS_X]++;
            posxy[POS_Y]--;
            if(posxy[POS_X] >= 0 || posxy[POS_X] < size || posxy[POS_Y] >= 0 || posxy[POS_Y] < size) {
                coordonnees[position_nb][POS_X] = posxy[POS_X];
                coordonnees[position_nb][POS_Y] = posxy[POS_Y];
                coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(posxy[POS_X], posxy[POS_Y]);
                position_nb++;
            }
        }
        orientation = NW;
        parcoursDiagonal(position_nb,orientation,size,posxy,iteration,nw);
    }
    
}

void Generator::coordonneesCreator()
{
    cout << "coordonnesCreator" << endl;
    if (corolle_type == Corolle::C) {
        int cpt = 0,
                x = 0,
                y = 0;
        coordonnees[cpt][POS_X] = x;
        coordonnees[cpt][POS_Y] = y;
        coordonnees[cpt][POS_TYPE] = pieceTypeByPosition(x, y);
        x++;
        cpt++;

        while (x < corolle_hamming + 1) {
            if (x >= 0) {

                coordonnees[cpt][POS_X] = x;
                coordonnees[cpt][POS_Y] = y;
                coordonnees[cpt][POS_TYPE] = pieceTypeByPosition(x, y);
                y++;
                x--;
                cpt++;

            } else {
                x = y;
                y = 0;
            }
        }
    }
}

/**
 * Initialise l'ordre de parcours
 */
void Generator::prerequisGeneration(int corolle_type, int hamming)
{
    cout << "prerequisGeneration" << endl;

    corolle_hamming = hamming; // hamming de la corolle
    this->corolle_type = corolle_type;
    int posxy [2] = {1,0}; //coordonnées de la pièce de départ.
    parcoursDiagonal(position_nb,0,size,posxy,0,false);
    //coordonneesCreator(); Du coup ça devient inutile


    /*if (corolle_type == Corolle::C) {
        // nombre de piece de la corolle suivant le type de la corolle a générer

        if (corolle_hamming == Corolle::HAMMING_1) {
            corolle_size = Corolle::SIZE_C_1;
        } else if (corolle_hamming == Corolle::HAMMING_2) {
            corolle_size = Corolle::SIZE_C_2;
        } else if (corolle_hamming == Corolle::HAMMING_3) {
            corolle_size = Corolle::SIZE_C_3;
        }

    } else if (corolle_type == Corolle::BC || corolle_type == Corolle::B) {
        // nombre de piece de la corolle suivant le type de la corolle a générer

        if (corolle_hamming == Corolle::HAMMING_1) {
            corolle_size = Corolle::SIZE_B_1;
        } else if (corolle_hamming == Corolle::HAMMING_2) {
            corolle_size = Corolle::SIZE_B_2;
        } else if (corolle_hamming == Corolle::HAMMING_3) {
            corolle_size = Corolle::SIZE_B_3;
        }

    } else {
        perror("Valeur de int corolle_type invalide");
    }*/

    
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