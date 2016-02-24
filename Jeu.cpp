#include "Jeu.h"

Jeu::Jeu(const int sizeJeu) : size(sizeJeu)
{

    //Initialize Variables
    jeu = new Piece[size];
    TabC = new Piece[4];
    TabB = new Piece[(size - 2) * 4];
    TabI = new Piece[(size - 2) * (size - 2)];

    nb_pieces_presentes = 0;
    nb_pieces_tabC = 0;
    nb_pieces_tabB = 0;
    nb_pieces_tabI = 0;

}

int Jeu::addPiece(Piece p)
{

    if (nb_pieces_presentes < (size * size)) {
        jeu[nb_pieces_presentes] = p;
        nb_pieces_presentes++;

        if (p.getType() == Piece::BORD) {
            TabB[nb_pieces_tabB] = p;
            nb_pieces_tabB++;
            cout << "Ajout d'une piece de Bord" << endl;
        } else if (p.getType() == Piece::COIN) {
            TabC[nb_pieces_tabC] = p;
            nb_pieces_tabC++;
            cout << "Ajout d'une piece de Coin" << endl;
        } else if (p.getType() == Piece::INTERIEUR) {
            TabI[nb_pieces_tabI] = p;
            nb_pieces_tabI++;
            cout << "Ajout d'une piece Interieur" << endl;
        }
    }
}

// Getters 
int Jeu::getSize()
{
    return size;
}

Piece *Jeu::getJeu()
{
    return jeu;
}

Piece *Jeu::getTabC()
{
    return TabC;
}

Piece *Jeu::getTabB()
{
    return TabB;
}

Piece *Jeu::getTabI()
{
    return TabI;
}
