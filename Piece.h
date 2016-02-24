#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <sstream>

using namespace std;

class Piece
{

public:
    //Type de Piece
    static const int BORD = 0;
    static const int COIN = 1;
    static const int INTERIEUR = 2;
    //Rotation
    static const int TOP = 0;
    static const int RIGHT = 1;
    static const int BOTTOM = 2;
    static const int LEFT = 3;

    Piece();

    Piece(int i, int *couleur);

    string toString();

    int getColor(int position);

    const int getId()const
    { return id; };

private:

    int id;
    int *couleur;
    int rotation;
    int type;

};

#endif
