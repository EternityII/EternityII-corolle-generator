//
// Created by stardisblue on 12/02/16.
//

#ifndef COROLLE_H
#define COROLLE_H

#include "Piece/Piece.h"

class Corolle
{
private:
    Piece pieces[];
    int rotation;
    int hamming;

public:

// Getters and Setters
    void setHamming(int hamming);

    int getHamming() const;

    void setRotation(int rotation);

    int getRotation() const;

    void setPieces(Piece *pieces);

    Piece[]getPieces() const;
};


#endif //COROLLE_H
