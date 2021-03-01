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

std::string FileSystem::ReadFile(const std::string &filepath)
{
    ifstream file(filepath);
    if(!file){
        cout<<"Unable to load "<<filepath<<" file"<<endl;
        return "";
    }
    stringstream fileData;
    fileData << file.rdbuf();

    file.close();
    return fileData.str();
}

MeshData FileSystem::ReadObj(const string &filepath)
{
    vector<glm::vec3> normals;
    MeshData meshData;
    ifstream file(filepath);
    if(!file)
    {
        cout<<"Unable to load "<<filepath<<" file"<<endl;
        return meshData;
    }

    string token;
    while(!file.eof())
    {
        file >> token;
        if(token == "v")
        {
            Vertex v;
            file >> v.pos.x;
            file >> v.pos.y;
            file >> v.pos.z;
            meshData.vertices.push_back(v);
        }
        else if(token == "vn")
        {
            glm::fvec3 normal;
            file >> normal.x;
            file >> normal.y;
            file >> normal.z;
            normals.push_back(normal);
        }
        else if(token == "f")
        {
            file.get();
            string line;
            getline(file, line);
            auto vertices = Split(line, ' ');
            if(vertices.size() == 4)
                meshData.drawType = DrawType::QUADS;
            unsigned vertId, normId;
            for(auto v: vertices)
            {
                auto numbers = Split(v, '/');
                if(numbers.size() >= 3){
                    vertId = stoi(numbers[0])-1;
                    normId = stoi(numbers[2])-1;
                    meshData.indices.push_back(vertId);
                    meshData.vertices[normId].normal += normals[normId];
                    meshData.vertices[normId].normal = glm::normalize(meshData.vertices[normId].normal);
                }
            }
        }
    }
    if(meshData.vertices.empty()){
        cout<<"no vertices\n";
    }

    file.close();

    for(auto& i: meshData.vertices)
    {
        cout<<i.pos.x<<", "<<i.pos.y<<", "<<i.pos.z<<" ";
        cout<<i.normal.x<<", "<<i.normal.y<<", "<<i.normal.z<<endl;
    }

    return meshData;
}

MeshData FileSystem::ReadStl(const string &filepath)
{
    MeshData meshData;
    ifstream file(filepath);
    if(!file)
    {
        cout<<"Unable to load "<<filepath<<" file"<<endl;
        return meshData;
    }
    stringstream src;
    while(!file.eof())
        src << file.rdbuf();

    if(StlFileHasASCIIFormat(src.str()))
        cout<<"Non ascii format\n";

    file.close();
    return meshData;
}

bool FileSystem::StlFileHasASCIIFormat(const std::string& src)
{
    string buffer (src.substr(256));
    transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
    return buffer.find ("solid") != string::npos &&
            buffer.find ("\n") != string::npos &&
            buffer.find ("facet") != string::npos &&
            buffer.find ("normal") != string::npos;
}
