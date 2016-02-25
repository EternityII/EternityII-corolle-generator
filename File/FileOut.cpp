using namespace std;

#include "FileOut.h"

FileOut::FileOut(int size, int corolle_hamming, int corolle_type, int piece_number, int rotation)
        : size(size), corolle_hamming(corolle_hamming), corolle_type(corolle_type), piece_number(piece_number),
          rotation(rotation)
{ }

void FileOut::open()
{
    fichier.open(getFileName().c_str(), ofstream::out | ofstream::trunc);
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
    output << "./output/" << size << "/" << corolle_hamming << "_" << corolle_type << "_" <<
    piece_number << "_" << rotation << ".txt";
    return output.str();
}


