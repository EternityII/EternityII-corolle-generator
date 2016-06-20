using namespace std;

#include "FileOut.h"

FileOut::FileOut(int size, int corolle_hamming, int corolle_type, int piece_number, int rotation, int corolle_size)
    : size(size), corolle_hamming(corolle_hamming), corolle_type(corolle_type), piece_number(piece_number),
      rotation(rotation), corolle_size(corolle_size)
{ }

void FileOut::open()
{
    //Creer le repertoire pour stocker les corolles en fonction de size
    ostringstream create_dir;
    create_dir << "./output/" << size;
    mkdir(create_dir.str().c_str(), 0777);

    fichier.open(getFileName().c_str(), ofstream::out | ofstream::trunc);
    fichier << "# taille hamming n°piece rotation nb_pieces" << endl;
    fichier << "# " << size << " "
        << corolle_hamming << " "
        << piece_number << " "
        << rotation << " "
        << corolle_size << endl;
    fichier << "# (n°piece:rotation;){nb_pieces}(couleur:n°frontiere;){(hamming+1)*2}" << endl;
    fichier << "# ([0-9]{1,3}:[0-4];){" << corolle_size
        << "}([0-9]{1,2}:[0-9]{1,3};){" << (corolle_hamming + 1) * 2 << "}" << endl;
}

void FileOut::put(Corolle &corolle)
{
    if (fichier.good()) {
        fichier << corolle.toString() << endl;
    }
}

void FileOut::put(Corolle &corolle, string &append)
{
    if (fichier.good()) {
        fichier << corolle.toString() << append << endl;
    }
}

void FileOut::close()
{
    fichier.close();
}

const string FileOut::getFileName() const
{
    ostringstream output;
    output << "./output/" << size << "/" << corolle_hamming << "_" << corolle_type << "_" <<
        piece_number << "_" << rotation << ".txt";
    return output.str();
}


