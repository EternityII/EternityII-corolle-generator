using namespace std;

#include "FileOut.h"

FileOut::FileOut(int size, int corolle_size, int corolle_hamming, int posx, int posy, int piece_number, int rotation, int coordonnees[25][3])
        : size(size), corolle_size(corolle_size), corolle_hamming(corolle_hamming), posx(posx), posy(posy), piece_number(piece_number),
          rotation(rotation)
{ 
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 3; j++) {
            this->coordonnees[i][j] = coordonnees[i][j];
        }
    }
}

void FileOut::open()
{   
    //Creer le repertoire pour stocker les corolles en fonction de size
    ostringstream create_dir;
    create_dir << "./output/" << size;
    mkdir(create_dir.str().c_str(),0777);

    fichier.open(getFileName().c_str(), ofstream::out | ofstream::trunc);
    fichier << corolle_hamming << "_" << posx << "_" << posy << "_" << piece_number << "_" << rotation << ".txt" << "\n";
    fichier << "# [taille plateau] [taille de la corolle] [hamming] [coordonnées x] [coordonnées y] [id pièce] [rotation]" << "\n";
    fichier << size << " " << corolle_size << " " << corolle_hamming << " " << posx << " " << posy << " " << piece_number << " " << rotation << "\n";
    for (int i = 0; i < corolle_size; i++) {
        fichier << i << " ";
    }
    fichier << "\n";  
}

void FileOut::put(Corolle &corolle)
{
    if (fichier) {
        fichier << corolle.toString() << endl;
    }
}

void FileOut::close()
{
    fichier.close();
}

const string FileOut::getFileName() const
{
    ostringstream output;
    output << "./output/" << size << "/" << corolle_hamming << "_" << posx << "_" << posy << "_" <<
    piece_number << "_" << rotation << ".txt";
    return output.str();
}


