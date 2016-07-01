#include <complex>
#include "Corolle.h"

using namespace std;

Corolle::Corolle()
{
    size = 4;
    ori_x = 0;
    ori_y = 0;
    hamming = 1;
    rotation = 0;
}

Corolle::Corolle(const Piece pieces[], int size, int ori_x, int ori_y, int hamming)
    : size(size), ori_x(ori_x), ori_y(ori_y), hamming(hamming)
{
    for (int i = 0; i < size; ++i) {
        this->pieces[i] = pieces[i];
    }

    rotation = (4 - pieces[0].rotation) % 4;
}

Corolle::Corolle(const Corolle &corolle)
{
    Corolle(corolle.getPieces(), corolle.getSize(), corolle.getOriX(), corolle.getOriY(), corolle.getHamming());
}

const string Corolle::toString(const int &lastdepth)
{
    ostringstream output;

    int j = lastdepth;
    while (pieces[j].getId() == -1 && j < size) {
        ++j;
    }

    if (j < size) {
        output << "\n" << lastdepth << ">";
        for (int i = j; i < size; ++i) {
            if (pieces[i].getId() != -1) {
                output << pieces[i].toString();
            }
            output << ";";
        }
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

void Corolle::setSize(int size)
{ this->size = size; }

const int Corolle::getOriY() const
{
    return ori_y;
}
const int Corolle::getOriX() const
{
    return ori_x;
}