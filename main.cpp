#include <iostream>

using namespace std;

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

int main()
{

    FileIn file_in(4);
    Jeu jeu = file_in.initJeu();

    Generator generator(jeu);
    generator.initGeneration(Corolle::C, Corolle::HAMMING_2); // Triangle en hamming de 1
}
