#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include "rapidjson/document.h"
#include <map>

class ConfigSystem
{
public:
    static ConfigSystem& Instance();
    void loadConfig(const std::string &name, const std::string &filepath);
    void unloadConfig(const std::string &name);
    rapidjson::Document getConfig(const std::string& name);

private:
    ConfigSystem();
    static ConfigSystem* selfInstance;
    std::map<std::string, std::string> configs;
};

#endif // CONFIGSYSTEM_H
