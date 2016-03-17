#include "Corolle.h"

using namespace std;

Corolle::Corolle()
{
    size = 0;
    posx = 0;
    posy = 0;
    hamming = 0;
    rotation = 0;
}

Corolle::Corolle(const Piece pieces[], int size, int posx, int posy, int hamming) : size(size), posx(posx), posy(posy), hamming(hamming)
{
    for (int i = 0; i < size; ++i) {
        this->pieces[i] = pieces[i];
    }

    rotation = pieces[0].rotation;
}

Corolle::Corolle(const Corolle &corolle)
{
    Corolle(corolle.getPieces(), corolle.getSize(), corolle.getPosX(), corolle.getPosY(), corolle.getHamming());
}

const string Corolle::toString()
{
    ostringstream output;
    for (int i = 0; i < size; ++i) {
        output << pieces[i].toString() << " ";
    }
    return output.str();
}


// Getter and Setters

const Piece *Corolle::getPieces() const
{ return this->pieces; }

const int Corolle::getRotation() const
{ return rotation; }

const int Corolle::getHamming() const
{ return hamming; }

const int Corolle::getPosX() const
{ return posx; }

const int Corolle::getPosY() const
{ return posy; }

const int Corolle::getSize() const
{ return size; }

void Corolle::setPieces(Piece pieces[Jeu::JEU_PIECES_MAX])
{
    for (int i = 0; i < size; ++i) {
        this->pieces[i] = pieces[i];
    }
}

void Corolle::setRotation(int rotation)
{ this->rotation = rotation; }

void Corolle::setHamming(int hamming)
{ this->hamming = hamming; }

void Corolle::setPosX(int posx)
{ this->posx = posx; }

void Corolle::setPosY(int posy)
{ this->posy = posy; }

void Corolle::setSize(int size)
{ this->size = size; }