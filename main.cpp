#include <iostream>

#include "Corolle.h"
#include "Generator.h"
#include "File/FileIn.h"

using namespace std;

int main(int argc, const char *argv[])
{

    if (argc > 1) {
        string str(argv[1]);
        FileIn file_in(str);
        Jeu jeu = file_in.initJeu();
        Generator generator(jeu);

        cout << argc << endl;
        if (argc > 3) {
            generator.multipleGeneration(atoi(argv[3]), atoi(argv[2]));
        } else if (argc > 2) {
            generator.multipleGeneration(atoi(argv[2]));
        } else {
            generator.multipleGeneration(2); //Génère toutes les corolles possible pour une taille de plateau
        }

        return 0;
    }

    cerr << "The input file was not specified" << endl;

    return 1;

}
