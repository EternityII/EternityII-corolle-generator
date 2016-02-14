/*
 * Created by stardisblue on 12/02/16.
 */

#ifndef GENERATOR_H
#define GENERATOR_H


#include "Jeu.h"

class Generator {
public:
    Generator(Jeu jeu);

    void initGeneration(int type_corolle) const;

    const void generationRecursive(int *disponibles, int position, int size)const;
private:
    Jeu jeu;

};


#endif //GENERATOR_H
