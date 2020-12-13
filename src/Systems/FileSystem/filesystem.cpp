#include "filesystem.h"
#include "Utils/utils.h"
#include <fstream>
#include <sstream>

using namespace std;

std::string FileSystem::readFile(const std::string &filename)
{
    ifstream file(filename);
    if(!file){
        cout<<"Unable to load "<<filename<<" file"<<endl;
        return "";
    }
    stringstream fileData;
    fileData << file.rdbuf();

    file.close();
    cout<<fileData.str()<<endl;
    return fileData.str();
}