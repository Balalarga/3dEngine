#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Systems/RenderSystem/rendersystem.h"

class FileSystem
{
public:
    FileSystem() = delete;
    static std::string ReadFile(const std::string& filename);
    static MeshData ReadObj(const std::string& filename);
    static MeshData ReadStl(const std::string& filename);

private:
    static bool StlFileHasASCIIFormat(const std::string& filename);
    static std::vector<std::string> Split(const std::string &s, char delimiter);
};

#endif // FILESYSTEM_H
