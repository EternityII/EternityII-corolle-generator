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
		Corolle corolle;
		int size;
		fstream fichier;
		FileOut(Corolle corolle,int size);
		void open(fstream &fichier);
		void put(fstream &fichier);
		void close(fstream &fichier);
		string getFileName(Corolle corolle, int size);
};

#endif //FILEOUT_H

