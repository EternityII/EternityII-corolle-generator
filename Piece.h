#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <sstream>

using namespace std;

class Piece
{

public:
    //Type de Piece
    static const int INTERIEUR = 0;
    static const int BORD = 1;
    static const int COIN = 2;

    //Rotation
    static const int TOP = 0;
    static const int RIGHT = 1;
    static const int BOTTOM = 2;
    static const int LEFT = 3;

    Piece();

    Piece(int i, int couleur[4]);

    const string toString();

    const int getColor(int position);

    const int getId() const
    { return id; };

    int getRotation();
    int* getTabCouleur();
    int  getType();
    void setRotation(int new_rotation);
    void setTabCouleur(int * new_tab_couleur);

private:

    int id;
    int couleur[4];
    int rotation;
    int type;

};

#endif
