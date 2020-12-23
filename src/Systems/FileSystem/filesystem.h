#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Systems/RenderSystem/rendersystem.h"

class FileSystem
{
public:
    FileSystem() = delete;
    static std::string ReadFile(const std::string& filepath);
    static MeshData ReadObj(const std::string& filepath);
    static MeshData ReadStl(const std::string& filepath);

private:
    static bool StlFileHasASCIIFormat(const std::string& src);
    static std::vector<std::string> Split(const std::string &s, char delimiter);
};

#endif // FILESYSTEM_H
