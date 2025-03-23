//
// Created by Lama on 06/02/2025.
//
#include "Resource/ResourceManager.h"

#include <filesystem>

#include <SDL3/SDL_log.h>

#include "Logger/Module.h"


bool MLEngine::ResourceManager::RegisterResourceType(const std::string& typeName,
                                                     const Handle<IResourceLoader>& loader)
{
    if (!loaderRegistry.contains(typeName))
    {
        loaderRegistry.emplace(typeName, loader);
        return true;
    }
    return false;
}

void MLEngine::ResourceManager::LoadResourceFromFile(const std::string& path, const std::string& name,
                                                     std::string type)
{
    if (type.empty())
    {
        type = DeduceResourceTypeFromPath(path);
    }
    if (type.empty())
    {
        MLLogTrace("Could not deduce resource type from path : {}", path);
    }

    if (const auto loader = loaderRegistry.find(type); loader != loaderRegistry.end())
    {
        loader->second->LoadResource(path, name);
    }
    else
    {
        MLLogTrace("Could not find resource loader for type : {}", type);
    }
}

MLEngine::ResourceManager::ResourceManager()
{
    asyncIOQueue = SDL_CreateAsyncIOQueue();
}

MLEngine::ResourceManager::~ResourceManager()
{
    SDL_DestroyAsyncIOQueue(asyncIOQueue);
    asyncIOQueue = nullptr;
}

void MLEngine::ResourceManager::FlushLoading()
{
}

void MLEngine::ResourceManager::RemoveUnusedResources()
{
}

std::string MLEngine::ResourceManager::DeduceResourceTypeFromPath(const std::string& path)
{
    std::filesystem::path p(path.c_str());

    for (const auto loader : loaderRegistry)
    {
        if (loader.second->SupportsExtension(p.extension().string()))
        {
        }
    }
    return "";
}
