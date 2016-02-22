using namespace std;

#include "FileOut.h"

FileOut::FileOut(int size, int corolle_hamming, int corolle_type, int piece_number, int rotation) const
{
    this->size = size;
    this->corolle_hamming = corolle_hamming;
    this->corolle_type = corolle_type;
    this->piece_number = piece_number;
    this->rotation = rotation;
}

void FileOut::open()
{
    fichier.open(getFileName().c_str(), fstream::out | fstream::trunc);
}

void FileOut::put(Corolle corolle) const
{
    if (fichier) {
        fichier << corolle.toStringCorolle();
    }
}

void FileOut::close()
{
    fichier.close();
}

const string FileOut::getFileName()
{
    ostringstream output;
    output << size << "/" << corolle_hamming << "_" << corolle_type << "_" <<
    piece_number << "_" << rotation << ".txt";
    return output.str();
}


