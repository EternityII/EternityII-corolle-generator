#include "Generator.h"


Generator::Generator(Jeu jeu) : jeu(jeu)
{
    cout << "Generator Constructor " << jeu.getSize() << endl;
    file_out = NULL;

    jeu_size = jeu.getSize();
    for (int i = 0; i < JEU_PIECES_MAX; ++i) {
        disponibles[i] = true;
    }

    cout << "end " << endl;
}

/**
 * Retourne le type de pièce suivant les coordonnée x et y
 *
 * @param int x
 * @param int y
 */
const int Generator::pieceTypeByPosition(int x, int y)
{
    //cout << "PieceTypeByPosition" << endl;
    if (x == 0 && y == 0) {
        return POS_TYPE_COIN_NW;
    } else if (x == jeu_size - 1 && y == 0) {
        return POS_TYPE_COIN_NE;
    } else if (x == jeu_size - 1 && y == jeu_size - 1) {
        return POS_TYPE_COIN_SE;
    } else if (x == 0 && y == jeu_size - 1) {
        return POS_TYPE_COIN_SW;
    } else if (x == 0) {
        return POS_TYPE_BORD_LEFT;
    } else if (y == 0) {
        return POS_TYPE_BORD_TOP;
    } else if (x == jeu_size - 1) {
        return POS_TYPE_BORD_RIGHT;
    } else if (y == jeu_size - 1) {
        return POS_TYPE_BORD_BOTTOM;
    } else {
        return POS_TYPE_INTERIEUR;
    }
}

/**
 * Ajoute une la coordonnée x,y à la position voulue, si x et y existent. Incrémente la position
 *
 * @param int &position_nb position a laquelle places les coordonnées
 * @param int x coordonnées x à verifier
 * @param int y coordonnées y à vérifier
 */
void Generator::addCoordinate(int &position_nb, int x, int y)
{
    if (x >= 0 && x < jeu_size && y >= 0 && y < jeu_size) {
        coordonnees[position_nb][POS_X] = x;
        coordonnees[position_nb][POS_Y] = y;
        coordonnees[position_nb][POS_TYPE] = pieceTypeByPosition(x, y);
        position_nb++;
    }
}

/**
 * Positionne les coordonnées en diagonale.
 *
 * @param int position_nb ordre de positionnement pour reformer la corolle.
 * @param int x, position x d'origine
 * @param int y, position y d'origine
 * @param int direction de la diagonale.
 * @param int length longueur de la diagonale.
 */
void Generator::diagonalWalker(int &position_nb, int &x, int &y, int orientation, int length)
{
    if (position_nb < 0 || orientation < 0 || length < 0) {
        perror("Invalid diagonalWalker values");
        exit(EXIT_FAILURE);
    }

    int walker_x = x,
            walker_y = y;
    int to_x = 1,
            to_y = 1;

    if (orientation == SW) {
        to_x = -1;
    } else if (orientation == NE) {
        to_y = -1;
    } else if (orientation == NW) {
        to_x = -1;
        to_y = -1;
    }

    for (int i = 1; i <= length; ++i) {
        walker_x = x + i * to_x;
        walker_y = y + i * to_y;

        addCoordinate(position_nb, walker_x, walker_y);
    }

    // Fin du parcours diagonal, passage des valeurs au parcours suivant
    x = walker_x;
    y = walker_y;
}

/**
 * Définit l'ordre de parcours de la corolle.
 *
 * @param int x coordonnée x d'origine
 * @param int y coordonnée y d'origine
 */
void Generator::coordinatesCreator(int x, int y, const int hamming)
{
    int position_nb = 0; // pièce en position 0, Initialisation du parcours

    addCoordinate(position_nb, x, y); // pièce initiale
    y--;// HAMMING 1

    for (int iteration = 1; iteration <= hamming; ++iteration) {  // HAMMING <= 1 ?

        int walking_x = x, walking_y = y;
        //placement de la pièce NORD qui va initialiser le parcours diagonal.
        addCoordinate(position_nb, walking_x, walking_y);
        diagonalWalker(position_nb, walking_x, walking_y, SE, iteration); // Génération des coordonnées vers le SE
        diagonalWalker(position_nb, walking_x, walking_y, SW, iteration); // vers le SW
        diagonalWalker(position_nb, walking_x, walking_y, NW, iteration); // vers le NW
        diagonalWalker(position_nb, walking_x, walking_y, NE, iteration - 1); // vers le NE sans la dernière valeur
        y--; //On décrémente la position y : on incrémente le hamming
    }

    corolle_size = position_nb; // Taille de la corolle
}

/*
* Initialise la génération multiple de toutes les corolles possibles en fonction de la taille du jeu
*/
void Generator::multipleGeneration(int hamming)
{
    int y = 0;
    int reduc;
    if (jeu_size % 2 == 1) {
        reduc = ((jeu_size - 1) / 2) + 1;
    } else {
        reduc = jeu_size / 2;
    }
    for (int j = 0; j < reduc; j++) {
        for (int i = y; i < reduc; i++) {
            initGeneration(i, j, hamming);
        }
    }
}

/**
 * Lance la génération des possibilités de la corolle et initialise l'ordre du parcours
 * @param int x coordonnée x de la position initiale
 * @param int y coordonnée y de la position initiale
 * @param int hamming hamming de la corolle
 */
void Generator::initGeneration(int x, int y, int hamming)
{

    cout << "InitGeneration : " << x << " " << y << " " << hamming <<
    endl; // preparation de tous les elements utilises dans la recursivite
    corolle_hamming = hamming; // hamming de la corolle

    if (x < 0 || y < 0 || corolle_hamming < 0) {
        cerr << "Bad coordinates";
        exit(EXIT_FAILURE);
    }

    coordinatesCreator(x, y, corolle_hamming);

    // TODO : a enlever test case
    /*for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 3; j++) {
            cout << coordonnees[i][j] << " ";
        }
        cout << endl;
    }
    cout << corolle_size << endl;*/

    genererHamming(hamming);
    //generationRecursive(position,0);
    if (!file_out == NULL && file_out->isOpen()) {
        file_out->close(); //fermeture eventuels des fichiers ouverts
    }
}

void Generator::genererHamming(int hamming)
{
    ifstream in_file;

    int ori_x = coordonnees[0][POS_X],
            ori_y = coordonnees[0][POS_Y];

    if (1 == hamming) { // Genere le hamming 1 si ce n'est deja fait
        cout << "hamming == 1 " << endl;

        // on vérifie si le hamming 1 a été généré a cette position :
        // -> il existe au moins un fichier ayant ce hamming et cette position
        bool existe = false;

        for (int id_piece = 0; id_piece < jeu_size * jeu_size; id_piece++) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                // Construction des chemins vers le fichier
                ostringstream output_path;

                output_path << "output/";
                output_path << jeu_size;
                output_path << "/" << hamming;
                output_path << "_" << ori_x << "_" << ori_y;
                output_path << "_" << id_piece << "_" << rotation << ".txt";

                in_file.open(output_path.str().c_str(), ios::out);

                if (in_file.good()) { // un fichier existe
                    existe = true;
                    in_file.close(); // c'est mieux de fermer le fichier
                    cout << "Le hamming 1 existe" << endl;
                    break; // on sort de la boucle des rotations
                }
            }

            if (existe) {// on sort de la boucle des id_pieces
                break;
            }
        }

        // bool existe : nous dit si le hamming a ete genere a cette position
        if (!existe) {
            cout << "Generation du hamming 1" << endl;

            int position = 0; // initialisation du parcours
            corolle_hamming = 1;
            coordinatesCreator(ori_x, ori_y, corolle_hamming); // on redéfinit la position max
            generationRecursive(position);
        }
    } else if (hamming > 1) {
        cout << "Hamming = " << hamming << endl;

        // on vérifie si le hamming a été généré a cette position :
        // -> il existe au moins un fichier ayant ce hamming et cette position
        // Le hamming est déja fait ?
        bool fait = false;

        for (int id_piece = 0; id_piece < jeu_size * jeu_size; id_piece++) {
            for (int rotation = 0; rotation < 4; ++rotation) {
                // Construction des chemins vers le fichier
                ostringstream output_path;

                output_path << "output/";
                output_path << jeu_size;
                output_path << "/" << hamming;
                output_path << "_" << ori_x << "_" << ori_y;
                output_path << "_" << id_piece << "_" << rotation << ".txt";

                in_file.open(output_path.str().c_str(), ios::out);

                if (in_file.good()) { // un fichier existe !
                    fait = true;
                    in_file.close();
                    cout << "Le hamming " << hamming << " existe" << endl;
                    break; // on sort de la boucle des rotations
                }
            }

            if (fait) {// on sort de la boucle des id_pieces
                break;
            }
        }

        if (!fait) { // le hamming n'est pas fait !
            // on genere le hamming-1
            genererHamming(hamming - 1);

            cout << "Generation du hamming " << hamming << endl;

            // on fait le hamming a partir du hamming - 1
            corolle_hamming = hamming;
            coordinatesCreator(ori_x, ori_y, corolle_hamming); // on rafraichit le nombre de piece de la corolle

            ori_x = coordonnees[0][POS_X];
            ori_y = coordonnees[0][POS_Y];

            // on parcours tout les fichiers hamming_fils existants
            for (int id_piece = 0; id_piece < jeu_size * jeu_size; id_piece++) {
                for (int rotation = 0; rotation < 4; ++rotation) {
                    // Construction des chemins vers le fichier
                    ostringstream output_path;
                    output_path << "output/";
                    output_path << jeu_size;
                    output_path << "/" << hamming - 1;
                    output_path << "_" << ori_x << "_" << ori_y;
                    output_path << "_" << id_piece << "_" << rotation << ".txt";

                    in_file.open(output_path.str().c_str(), ios::out);

                    if (in_file.good()) { // un fichier existe
                        cout << "Fichier hamming fils :" << hamming - 1 << ", x= " << ori_x << ", y=" << ori_y << endl;

                        string line;
                        int not_useful;
                        int child_corolle_size;
                        getline(in_file, line); // on ignore le nom du fichier
                        getline(in_file, line); // on ignore les eventuels commentaires
                        getline(in_file, line); // on ignore la syntaxe

                        in_file >> not_useful; // la taille du jeu
                        in_file >> child_corolle_size; // La taille de la corolle

                        getline(in_file, line); // le reste n'est pas utile
                        getline(in_file, line); // par utile pour la generation

                        int id_pieces[child_corolle_size][2];


                        while (!in_file.eof()) {
                            for (int l = 0; l < child_corolle_size; l++) { // on récupère l'ancienne corolle
                                in_file >> id_pieces[l][0];
                                in_file >> id_pieces[l][1];
                            }

                            placerCorolle(id_pieces, child_corolle_size); // on la place dans le jeu
                            int position = child_corolle_size; // on part a partir de la fin de la corolle fils
                            generationRecursive(position);
                            enleverCorolle(id_pieces, child_corolle_size);
                        }
                        cout << endl;

                        in_file.close();
                    }
                }
            }
        }
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
    return a[side_a] == b[side_b];
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
            return compareColors(piece, plateau[x][y + 1], Piece::BOTTOM, Piece::TOP);
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

void Generator::placerCorolle(int id_pieces[][2], int length_corolle)
{
    for (int i = 0; i < length_corolle; ++i) {
        putPiece(coordonnees[i][POS_X], coordonnees[i][POS_Y],
                 jeu.getJeu()[id_pieces[i][0]].setRotation(id_pieces[i][1]));
    }
}

void Generator::enleverCorolle(int id_pieces[][2], int length_corolle)
{
    for (int i = 0; i < length_corolle; ++i) {
        pickOffPiece(id_pieces[i][0], coordonnees[i][POS_X], coordonnees[i][POS_Y]);
    }
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

            file_out = new FileOut(jeu_size, corolle.getSize(), corolle.getHamming(), corolle.getPosX(),
                                   corolle.getPosY(), corolle.getPieces()[0].getId(),
                                   corolle.getRotation(), coordonnees);
            file_out->open();
            file_out->put(corolle);
        }
    } else {// si aucun fichier n'est ouvert, on ouvre le bon
        file_out = new FileOut(jeu_size, corolle.getSize(), corolle.getHamming(), corolle.getPosX(), corolle.getPosY(),
                               corolle.getPieces()[0].getId(),
                               corolle.getRotation(), coordonnees);
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
                        generationRecursive(++position);
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
        Corolle corolle(piece_tab, corolle_size, coordonnees[0][POS_X], coordonnees[0][POS_Y], corolle_hamming);

        //cout << corolle.toString() << endl;

        writeInFile(corolle);
    }
}

// Inutile pour l'instant
