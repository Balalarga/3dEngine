#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include "Systems/RenderSystem/rendersystem.h"

class FileSystem
{
public:
    FileSystem() = delete;
    static std::string readFile(const std::string& filename);
    static MeshData readObj(const std::string& filename);
};

#endif // FILESYSTEM_H
