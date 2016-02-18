#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

#include "FileUtils.h"

FileUtils::FileUtils(){};
const string FileUtils::getFileName()
{
	return file_name;
}
