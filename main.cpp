#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#include "Corolle.h"
#include "File/FileOut.h"
#include "File/FileUtils.h"
//#include "Piece/Piece.h"

int main() {
    cout << "Hello, World!" << endl;
    Corolle c1(NULL,4,0,1);
    FileOut f(c1,4);
    cout << f.getFileName(c1,4) << endl;
    f.open(f.fichier);
    f.put(f.fichier);
    f.close(f.fichier);
}
