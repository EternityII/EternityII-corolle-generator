//
// Created by stardisblue on 12/02/16.
//

#include "Corolle.h"


// Getter and Setters
Piece[]Corolle::getPieces() const
{
    return pieces;
}

void Corolle::setPieces(Piece *pieces)
{
    this->pieces = pieces;
}

int Corolle::getRotation() const
{
    return rotation;
}

void Corolle::setRotation(int rotation)
{
    this->rotation = rotation;
}

int Corolle::getHamming() const
{
    return hamming;
}

void Corolle::setHamming(int hamming)
{
    this->hamming = hamming;
}