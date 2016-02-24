#include <sstream>
#include "FileIn.h"


FileIn::FileIn(int taille)
{

    this->size = taille;

    string extension = ".txt";

    ostringstream s;
    s << "../assets/";
    s << "pieces_" << taille << "x" << taille << extension;

    this->pathFile = s.str();

    cout << s.str() << endl;

}

Jeu FileIn::InitJeu()
{
    Jeu jeu(this->size);

    string stringPiece;

    int id = 0;

    int nbLignesLus = 0;
    int startPiece = 4;

    //Ouverture du fichier
    in_file.open(this->pathFile.c_str(), ios::in);

    if(!in_file.eof()){
        cout <<"Fichier ouvert" << endl;
    }

    int *couleur = new int[4];
    int color = 0;

    string str = ""; // 4 premieres lignes
    
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

        Piece p(id, couleur);
	    jeu.addPiece(p);
        cout << p.toString() << endl;
        id++;
    }
return jeu;
}