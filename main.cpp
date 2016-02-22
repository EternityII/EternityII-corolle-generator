#include <iostream>

using namespace std;

#include "Corolle.h"
#include "Generator.h"

int main()
{
    Jeu jeu; // incomplet

    Generator generator(jeu);
    generator.initGeneration(Corolle::C_1); // Triangle en hamming de 1
}
