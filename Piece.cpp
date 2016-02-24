#include "Piece.h"

Piece::Piece()
{
    rotation = 0;
}

Piece::Piece(int idPiece, int *couleur)
{

    this->id = idPiece;
    this->couleur = couleur;
    this->rotation = 0;
    //Compte le nombre de Zero afin de definir le type
    int nbZero = 0;

    for (int i = 0; i < 4; i++) {
        if (couleur[i] == 0) {
            nbZero++;
        }
    }

    if (nbZero == 0) {
        this->type = INTERIEUR;
    }
    else {
        if (nbZero == 1) {
            this->type = BORD;
        }
        else {
            if (nbZero == 2) {
                this->type = COIN;

            }
        }
    }
}

string Piece::toString()
{

    ostringstream s;
    s << "La Piece : ";
    s << this->id;
    s << " a été ajouté";
    s << "avec la couleur";
    for(int i=0;i<4;i++){
        s << couleur[i];
    }

    return s.str();
}

int Piece::getColor(int position)
{
    if (position > 4) {
        return -1;
    }
    return couleur[(position + rotation) % 4];
}

//Getters 
int Piece::getRotation()
{
return this->rotation;
}

int* Piece::getTabCouleur(){
return this->couleur;
}

int Piece::getType(){
return this->type;
}

//Setters
void Piece::setRotation(int new_rotation)
{
this->rotation = new_rotation;
}

void Piece::setTabCouleur(int * new_tab_couleur)
{
this->couleur = new_tab_couleur;
}


