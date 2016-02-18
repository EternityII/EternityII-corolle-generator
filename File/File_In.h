#ifndef FILE_IN_H
#define FILE_IN_H


#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

//Class Input
#include "Jeu.h"
#include "Piece.h"

using namespace std;

class File_In {

	public:

	//File *file;
	string pathFile;
	ifstream in_file;
	int size;

	File_In(int taille);
	void InitJeu();


};

#endif