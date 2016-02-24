#include <sstream>
#include "FileIn.h"


FileIn::FileIn(int taille, string path) : size(taille), path_file(path)
{ }

FileIn::FileIn(int taille) : size(taille), path_file(getFileName())
{ }

Jeu FileIn::initJeu()
{
    Jeu jeu(this->size);

    //Ouverture du fichier
    in_file.open(this->path_file.c_str(), ifstream::in);

    if (!in_file.eof()) {
        cout << "Fichier ouvert" << endl;
    }

    int *couleur = new int[4];
    int color = 0;

    string str; // 4 premieres lignes

    for (int i = 0; i < 4; i++) {
        in_file >> str;
        cout << str << endl;
    }
    cout << "string" << endl;

    for (int i = 0; i < (size * size); i++) {

        for (int j = 0; j < 4; j++) {

            in_file >> color;
            couleur[j] = color;
        }

        Piece p(i, couleur);
        jeu.addPiece(p);
        cout << p.toString() << endl;
    }
    return jeu;
}

const string FileIn::getFileName() const
{
    ostringstream s;
    s << "assets/pieces_" << size << "x" << size << ".txt";
    return s.str();
}