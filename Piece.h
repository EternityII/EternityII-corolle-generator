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
    static const int TOP = 1;
    static const int RIGHT = 2;
    static const int BOTTOM = 3;
    static const int LEFT = 0;

    Piece();

    ~Piece()
    { };

    Piece(const int idPiece, int couleur[4]);

    const string toString();

    string toStringDetail() const;

    const int getColor(const int position);

    int getId() const
    { return id; };

    const int getRotation();

    const int *getTabCouleur();

    const int getType();

    void setRotation(const int new_rotation);

    void setTabCouleur(const int *new_tab_couleur);

    int operator[](const int &position);

    int rotation;

private:
    int id;
    int couleur[4];
    int type;

};

#endif
