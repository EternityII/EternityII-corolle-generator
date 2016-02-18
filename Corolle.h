//
// Created by stardisblue on 12/02/16.
//

#ifndef COROLLE_H
#define COROLLE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "Piece/Piece.h"

class Corolle
{
private:
    Piece pieces[];
    int rotation = 0;
    int size;
    int type;
    int hamming;

public:
    static const int C_1 = 0;
    static const int BC_1 = 1;
    static const int B_1 = 2;
    static const int IBB_1 = 3;
    static const int IB_1 = 4;
    static const int I_1 = 5;

    static const int SIZE_C_1 = 3;
    static const int SIZE_B_1 = 4;
    static const int SIZE_I_1 = 5;

	Corolle();

    Corolle(const Piece pieces[], const int size, const int type, const int hamming);

    Corolle(const Corolle corolle);

    ~Corolle()
    { };

// Getters and Setters

    void setPieces(Piece *pieces);

    void setHamming(int hamming);

    void setRotation(int rotation);

    void setType(int type);

    void setSize(int size);

    const Piece *getPieces() const;

    const int getHamming() const;

    const int getRotation() const;

    const int getType() const;

    const int getSize() const;

	string toStringCorolle();
};


#endif //COROLLE_H
