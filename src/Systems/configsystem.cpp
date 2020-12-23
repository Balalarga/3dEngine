#include "configsystem.h"
#include "FileSystem/filesystem.h"

using namespace std;
using namespace rapidjson;

ConfigSystem* ConfigSystem::selfInstance = nullptr;

ConfigSystem &ConfigSystem::Instance()
{
    if(!selfInstance)
        selfInstance = new ConfigSystem;
    return *selfInstance;
}

void ConfigSystem::loadConfig(const std::string& name, const std::string& filepath)
{
    configs[name] = FileSystem::ReadFile(filepath);
}

void ConfigSystem::unloadConfig(const std::string& name)
{
    auto iter = configs.find(name);
    if(iter == configs.end())
        configs.erase(iter);
}

rapidjson::Document ConfigSystem::getConfig(const std::string& name)
{
    Document doc;
    if(configs.find(name) == configs.end())
        doc.Parse(configs[name].c_str());
    return doc;
}

ConfigSystem::ConfigSystem()
{

}
