#include <sstream>
#include "FileIn.h"


FileIn::FileIn(int taille, string path) : size(taille), path_file(path)
{ }

FileIn::FileIn(int taille) : size(taille)
{
    path_file = getFileName();
}
FileIn::FileIn(string path) : path_file(path)
{
    in_file.open(this->path_file.c_str(),ios::out);

    if(in_file.is_open()){  

        int size_in_file;
        in_file >> size_in_file;
        cout << "Taille dans le fichier : " << size_in_file << endl;
        if (size_in_file <= 0 || size_in_file > 16) return;
        else {
            size = size_in_file;
            in_file.close();
        }
    }
    else {
        cout << "Erreur lors de l'ouverture du fichier" << endl; 
    }

}

Jeu FileIn::initJeu()
{
    Jeu jeu(this->size);

    //Ouverture du fichier
    in_file.open(this->path_file.c_str(), ios::out);

    if (!in_file.eof()) {
        cout << "Fichier " << path_file << " ouvert" << endl;
    }

    int couleur[4];
    int color = 0;

    string str = " "; // 4 premieres lignes

    for (int i = 0; i < 4; i++) {
        getline(in_file, str);
        cout << str << endl;
    }
    cout << "string" << endl;

    for (int i = 0; i < (size * size); i++) {
        cout << i << endl;
        for (int j = 0; j < 4; j++) {
            in_file >> color;
            couleur[j] = color;
        }

        Piece p(i, couleur);
        cout << p.toStringDetail() << endl;
        jeu.addPiece(p);

    }

    in_file.close();

    return jeu;
}

const string FileIn::getFileName() const
{
    ostringstream s;// Barbarisme a l'état pur
    s << "./assets/pieces_" << size << "x" << size << ".txt";
    return s.str();
}
