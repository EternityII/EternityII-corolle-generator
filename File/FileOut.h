#ifndef FILEOUT_H
#define FILEOUT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#include "../Corolle.h"
#include "FileUtils.h"

class FileOut : public FileUtils
{
public:
    int size;
    int corolle_hamming;
    int corolle_type;
    int piece_number;
    int rotation;

    fstream fichier;

    FileOut(int size, int corolle_hamming, int corolle_type, int piece_number,
            int rotation) const;

    void open();

    void put(Corolle corolle) const;

    void close();

    const string getFileName();
};

#endif //FILEOUT_H

