//
// Created by stardisblue on 12/02/16.
//

#include "Corolle.h"


Corolle::Corolle(const Piece *pieces, const int size, const int type, const int hamming)
{
    this->pieces = new Piece[size];

    for (int i = 0; i < size; ++i)
    {
        this->pieces[i] = pieces[i];
    }

    this->size = size;
    this->type = type;
    this->hamming = hamming;
}

Corolle::Corolle(const Corolle corolle)
{
    this->Corolle(corolle.getPieces(), corolle.getSize(), corolle.getType(), corolle.getHamming());
}


// Getter and Setters

const Piece *Corolle::getPieces() const
{ return this->pieces; }

const int Corolle::getRotation() const
{ return rotation; }

const int Corolle::getHamming() const
{ return hamming; }

const int Corolle::getType() const
{ return type; }

const int Corolle::getSize() const
{ return size; }

void Corolle::setPieces(Piece *pieces)
{ this->pieces = pieces; }

void Corolle::setRotation(int rotation)
{ this->rotation = rotation; }

void Corolle::setHamming(int hamming)
{ this->hamming = hamming; }

void Corolle::setType(int type)
{ this->type = type; }

void Corolle::setSize(int size)
{ this->size = size; }
