#include <iostream>

using namespace std;

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

int main()
{

    FileIn file_in("assets/pieces_6x6.txt");
    Jeu jeu = file_in.initJeu();
    cout << "Color" << jeu.getJeu()[3][3] << endl;
    cout << "Color" << jeu.getSize() << endl;

    Generator generator(jeu);
    generator.multipleGeneration(); //Génère toutes les corolles possible pour une taille de plateau.
}
