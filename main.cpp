#include <iostream>

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

using namespace std;

int main()
{
    for (int i = 4; i < 11; ++i) {
        string str = "./assets/pieces_";
        str += to_string(i);
        str += "x";
        str += to_string(i);
        str += ".txt";
        FileIn file_in(str);
        Jeu jeu = file_in.initJeu();
        Generator generator(jeu);
        generator.multipleGeneration(); //Génère toutes les corolles possible pour une taille de plateau.
    }
    return 0;
}
