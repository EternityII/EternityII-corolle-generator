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

}

Jeu FileIn::initJeu()
{

    //Ouverture du fichier
    in_file.open(this->path_file.c_str(), ios::out);

    if (in_file.eof() && !in_file.is_open()) {
        cout << "Fichier " << path_file << "  non ouvert" << endl;
        return -1;
    } else {

        int size_in_file;
        int couleur[4];
        int color = 0;

        string str = " "; // 4 premieres lignes

            for (int i = 0; i < 4; i++) {

                if(i==0){
                    in_file >> size_in_file;
                    cout << "Taille dans le fichier : " << size_in_file << endl;
                      if (size_in_file <= 0 || size_in_file > 16) return -1;
                      else {
                        size = size_in_file;
                        cout << "size" << size << endl;
                      }
                }
                else {
                    in_file >> str;
                    getline(in_file,str);
                    //cout << "Getline" << str << endl;
                }
            }
             Jeu jeu(this->size);

            for (int i = 0; i < (size * size); i++) {
                cout << i << endl;
                for (int j = 0; j < 4; j++) {
                    in_file >> color;
                    couleur[j] = color;
                    cout << "Couleur "<< color <<endl;
                }
                Piece p(i, couleur);

                jeu.addPiece(p);
            }

            in_file.close();
            return jeu;
            }
}

const string FileIn::getFileName() const
{
    ostringstream s;// Barbarisme a l'état pur
    s << "./assets/pieces_" << size << "x" << size << ".txt";
    return s.str();
}

