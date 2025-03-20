//
// Created by Lama on 06/02/2025.
//
#pragma once

#include <set>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <SDL3/SDL_asyncio.h>
#include <SDL3/SDL_thread.h>

namespace MLEngine
{
    class IResource
    {
        friend class IResourceLoader;
        public:
        virtual ~IResource() = default;

    };

    class IResourceLoader
    {
        friend class ResourceManager;
    public:
        virtual ~IResourceLoader() = default;

    protected:
        bool supportAsyncLoading = false;

        virtual std::shared_ptr<IResource> LoadResource(const std::string& path, const std::string& name) {
            return nullptr;
        };

        virtual bool SupportsExtension(std::string extension);
    };

    enum class LoadingStatus
    {
        NOT_LOADED,
        LOADING,
        LOADED,
        FAILED
    };

    struct AssetMetadata
    {
        std::string type;
        std::string path;

        LoadingStatus status;
        bool isLoadedFromFilesystem;
    };

    class ResourceManager
    {
    public:
        ResourceManager();

        ~ResourceManager();

        bool RegisterResourceType(const std::string& typeName, std::shared_ptr<IResourceLoader> loader);

        void LoadResourceFromFile(const std::string& path, const std::string& name = "",
                                  std::string type = "");

        void FlushLoading();

        void RemoveUnusedResources();

    private:
        std::string DeduceResourceTypeFromPath(const std::string& path);


        std::unordered_map<std::string, std::shared_ptr<IResourceLoader> > loaderRegistry;
        std::unordered_map<std::string, std::shared_ptr<IResource> > assetRegistry;

        std::set<std::string> resourceToLoad;

        SDL_AsyncIOQueue* asyncIOQueue = nullptr;
        std::vector<SDL_Thread*> threadPool;
    };
}
