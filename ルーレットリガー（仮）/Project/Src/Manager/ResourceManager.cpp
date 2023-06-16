#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{



}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second->Release();
		delete p.second;
	}

	loadedMap_.clear();
}

//Resource ResourceManager::Load(SRC src)
//{
//	Resource* res = _Load(src);
//	if (res == nullptr)
//	{
//		return Resource();
//	}
//	Resource ret = *res;
//	return *res;
//}

Resource ResourceManager::Load(std::string key, Resource::TYPE type, std::string path)
{
	 Resource test = Resource(Resource::TYPE::EFFEKSEER, path);
	resourcesMap_.emplace(key, test);

	Resource* res = _Load(key);
	if (res == nullptr)
	{
		return Resource();
	}
	Resource ret = *res;
	return *res;

}

ResourceManager::ResourceManager(void)
{
}

ResourceManager::~ResourceManager(void)
{
	delete instance_;
}

Resource* ResourceManager::_Load(std::string key)
{

	const auto& rPair = resourcesMap_.find(key);
	if (rPair != resourcesMap_.end())
	{
		//登録されている
		return nullptr;
		//return rPair->second;
	}

	
	//(*rPair).second->Load();

	 //念のためコピーコンストラクタ
	Resource* ret = new Resource((*rPair).second);
	loadedMap_.emplace(key, ret);

	return ret;
}

//Resource* ResourceManager::_Load(SRC src)
//{
//	//const auto& lPair = mLoadedMap.find(src);
//	//if (lPair != mLoadedMap.end())
//	//{
//	//	登録されている
//	//	return lPair->second;
//	//}
//
//	//const auto& rPair = mResourcesMap.find(src);
//	//if (rPair == mResourcesMap.end())
//	//{
//	//	 登録されていない
//	//	return nullptr;
//	//}
//
//	//rPair->second.Load();
//
//	// 念のためコピーコンストラクタ
//	//Resource* ret = new Resource(rPair->second);
//	//mLoadedMap.emplace(src, ret);
//
//	//return ret;
//}
