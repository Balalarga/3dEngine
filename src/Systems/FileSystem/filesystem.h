#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>

class FileSystem
{
public:
    FileSystem() = delete;
    static std::string readFile(const std::string& filename);
};

#endif // FILESYSTEM_H
