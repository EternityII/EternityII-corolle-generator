#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "FileOut.h"

FileOut::FileOut(Corolle c, int s)
{
	corolle = c;
	size = s;
}
void FileOut::open(fstream &fichier)
{
	fichier.open(getFileName(corolle,size).c_str(),  fstream::out | fstream::trunc);
}
void FileOut::put(fstream &fichier)
{
	if(fichier){
		fichier << corolle.toStringCorolle();
	}
}
void FileOut::close(fstream &fichier)
{
	fichier.close();
}
string FileOut::getFileName(Corolle corolle, int size)
{
	ostringstream output;
	output << "[" << size << "]/[" << corolle.getHamming() << "]_[" << corolle.getType() << "]_[" << "corolle.getPieces()[0]" << "]_[" << corolle.getRotation() << "].txt";
	return output.str();
}


