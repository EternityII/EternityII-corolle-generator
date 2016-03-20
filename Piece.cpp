#include "Piece.h"

Piece::Piece() : couleur{0, 0, 0, 0}
{
    id = -1;
    rotation = 0;
}

Piece::Piece(int idPiece, int couleur[4]) : id(idPiece), rotation(0)
{
    for (int i = 0; i < 4; ++i) {
        this->couleur[i] = couleur[i];
    }
    //Compte le nombre de Zero afin de definir le type
    int nb_zero = 0;

    for (int i = 0; i < 4; i++) {
        if (couleur[i] == 0) {
            nb_zero++;
        }
    }

    if (nb_zero == 0) {
        type = INTERIEUR;
    } else if (nb_zero == 1) {
        type = BORD;
    } else if (nb_zero == 2) {
        type = COIN;
    }
}

const string Piece::toString()
{
    ostringstream s;
    s << id << " " << rotation;
    return s.str();
}

const string Piece::toStringDetail()
{
    ostringstream stream;
    stream << "Pièce n " << id << endl;

/*    for (int i = 0; i < 4; ++i) {
        stream << couleur[i] << " ";
    }*/

    return stream.str();
}


const int Piece::getColor(int position)
{
    if (position > 4) {
        return -1;
    }

    return couleur[(position + rotation) % 4];
}

//Getters
int Piece::getRotation()
{
    return rotation;
}

int *Piece::getTabCouleur()
{
    return couleur;
}

int Piece::getType()
{
    return type;
}

//Setters
Piece Piece::setRotation(int new_rotation)
{
    rotation = new_rotation;

    return *this;
}

void Piece::setTabCouleur(int new_tab_couleur[4])
{
    for (int i = 0; i < 5; ++i) {
        couleur[i] = new_tab_couleur[i];
    }
}

int Piece::operator[](int position)
{
    if (position < 4) {
        return couleur[(position + rotation) % 4];
    } else { return -1; }
}

