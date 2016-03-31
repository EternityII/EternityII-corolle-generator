#include <iostream>

using namespace std;

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

int main()
{

    FileIn file_in(6);

    Jeu jeu = file_in.initJeu();

    Generator generator(jeu);
    generator.multipleGeneration(3); //Génère toutes les corolles possible pour une taille de plateau.
}
