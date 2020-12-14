#include "filesystem.h"
#include "Utils/utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> FileSystem::Split(const std::string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

std::string FileSystem::ReadFile(const std::string &filename)
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

MeshData FileSystem::ReadObj(const string &filename)
{
    MeshData meshData;
    ifstream file(filename);
    if(!file)
    {
        cout<<"Unable to load "<<filename<<" file"<<endl;
        return meshData;
    }

    string token;
    while(!file.eof())
    {
        file >> token;
        if(token == "v")
        {
            glm::vec3 vertex;
            file >> vertex.x;
            file >> vertex.y;
            file >> vertex.z;
            meshData.verteces.push_back(vertex);
        }
        else if(token == "f")
        {
            file.get();
            string line;
            getline(file, line);
            auto vertices = Split(line, ' ');
            if(vertices.size() == 4)
                meshData.drawType = DrawType::QUADS;
            unsigned idx;
            for(auto v: vertices){
                auto del = v.find('/');
                if(del != string::npos){
                    idx = stoi(v.substr(0, del))-1;
                    meshData.indices.push_back(idx);
                }
                cout<<idx<<" ";
            }
            cout<<endl;
        }
    }
    if(meshData.verteces.empty()){
        cout<<"no vertices\n";
    }

    file.close();
    return meshData;
}

MeshData FileSystem::ReadStl(const string &filename)
{
    MeshData meshData;
    ifstream file(filename);
    if(!file)
    {
        cout<<"Unable to load "<<filename<<" file"<<endl;
        return meshData;
    }
    if(StlFileHasASCIIFormat(filename)){
        cout<<"Non ascii format\n";
    }

    file.close();

    return meshData;
}

bool FileSystem::StlFileHasASCIIFormat(const std::string& filename)
{
    using namespace std;
    ifstream in(filename);
    if(!in)
    {
        cout<<"Couldnt open file " << filename<<endl;
    }

    char chars [256];
    in.read (chars, 256);
    string buffer (chars, in.gcount());
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    return buffer.find ("solid") != string::npos &&
            buffer.find ("\n") != string::npos &&
            buffer.find ("facet") != string::npos &&
            buffer.find ("normal") != string::npos;
}
