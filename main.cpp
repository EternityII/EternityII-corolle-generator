#include <iostream>

using namespace std;

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

int main()
{

    FileIn file_in("assets/pieces_7x7.txt");
    Jeu jeu = file_in.initJeu();
    cout << "Color" << jeu.getJeu()[3][3] << endl;

    Generator generator(jeu);
    generator.initGeneration(Corolle::C, Corolle::HAMMING_3); // Triangle en hamming de 1
}
