#ifndef FILE_IN_H
#define FILE_IN_H


#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

class FileIn
{

public:

    //File *file;
    string pathFile;
    ifstream in_file;
    int size;

    FileIn(int taille);

    void InitJeu();


};

#endif