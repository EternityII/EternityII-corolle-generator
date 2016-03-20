#include <iostream>

using namespace std;

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

int main()
{

    FileIn file_in("assets/pieces_5x5.txt");
    Jeu jeu = file_in.initJeu();
    cout << "Color" << jeu.getJeu()[3][3] << endl;

    Jeu jeu = file_in.initJeu();
    cout << "Color" << jeu.getJeu()[3][3] << endl;

    Generator generator(jeu);
    generator.multipleGeneration(3); //Génère toutes les corolles possible pour une taille de plateau.
}
