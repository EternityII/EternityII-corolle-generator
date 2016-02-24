#include <sstream>
#include "FileIn.h"
#include "../Jeu.h"

FileIn::FileIn(int taille)
{

    this->size = taille;

    string extension = ".txt";

    ostringstream s;
    s << "Pieces_" << taille << "x" << taille << extension;

    this->pathFile = s.str();

}

void FileIn::InitJeu()
{
    Jeu jeu(this->size);

    string stringPiece;

    int id = 0;

    int nbLignesLus = 0;
    int startPiece = 4;

    //Ouverture du fichier
    in_file.open(this->pathFile.c_str(), ifstream::in);


    int *couleur = new int[4];
    int color;

    string str; // 4 premieres lignes
    for (int i = 0; i < 4; ++i) {
        in_file >> str;
    }

    for (int i = 0; i < (size * size); i++) {
        for (int j = 0; j < 4; j++) {
            in_file >> color;
            couleur[i] = color;
        }

        Piece p(id, couleur);
        cout << p.toString() << endl;
        id++;
    }
}

