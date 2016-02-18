#include <iostream>
#include <fstream>

using namespace std;

#include "Corolle.h"
#include "File/FileOut.h"

int main()
{
    cout << "Hello, World!" << endl;
    Corolle c1(NULL, 4, 0, 1);
    FileOut f(c1, 4);
    cout << f.getFileName(c1, 4) << endl;
    f.open(f.fichier);
    f.put(f.fichier);
    f.close(f.fichier);
}
