using namespace std;

#include "FileOut.h"

FileOut::FileOut(int size,
    int corolle_hamming,
    int corolle_x,
    int corolle_y,
    int piece_number,
    int rotation,
    int corolle_size)
    : size(size), corolle_hamming(corolle_hamming), corolle_x(corolle_x), corolle_y(corolle_y),
      piece_number(piece_number),
      rotation(rotation), corolle_size(corolle_size)
{ }

void FileOut::open()
{
    //Creer le repertoire pour stocker les corolles en fonction de size
    ostringstream create_dir;
    create_dir << "./output/" << size;
    mkdir(create_dir.str().c_str(), 0777);

    fichier.open(getFileName().c_str(), ofstream::out | ofstream::trunc);
    fichier << "# taille n°piece rotation x y hamming nb_pieces" << endl;
    fichier << "# " << size << " "
        << piece_number << " "
        << rotation << " "
        << corolle_x << " "
        << corolle_y << " "
        << corolle_hamming << " "
        << corolle_size << endl;
    fichier << "# (n°piece:rotation;){nb_pieces}(couleur:n°frontiere;){4(2hammings+1)}" << endl;
    fichier << "# ((([0-9]{1,3}:[0-4])|-1);){" << corolle_size
        << "}((([0-9]{1,2})|-1);){" << (corolle_hamming * 4) * 2 + 4 << "}" << endl;
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
    output << "./output/" << size << "/N(" << size << ")_P(" << piece_number << ":" << rotation << ")_Z(" << corolle_x
        << "," << corolle_y
        << ")_H("
        << corolle_hamming << ").txt";
    return output.str();
}


