#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::mInstance = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (mInstance == nullptr)
	{
		mInstance = new ResourceManager();
	}
	mInstance->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *mInstance;
}

void ResourceManager::Init(void)
{



}

void ResourceManager::Release(void)
{
	for (auto& p : mLoadedMap)
	{
		p.second->Release();
		delete p.second;
	}

	mLoadedMap.clear();
}

Resource ResourceManager::Load(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return Resource();
	}
	Resource ret = *res;
	return *res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource* res = _Load(src);
	if (res == nullptr)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res->mHandleId);
	res->mDuplicateModelIds.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

ResourceManager::~ResourceManager(void)
{
	delete mInstance;
}

Resource* ResourceManager::_Load(SRC src)
{
	const auto& lPair = mLoadedMap.find(src);
	if (lPair != mLoadedMap.end())
	{
		return lPair->second;
	}

	const auto& rPair = mResourcesMap.find(src);
	if (rPair == mResourcesMap.end())
	{
		// 登録されていない
		return nullptr;
	}

	rPair->second.Load();

	// 念のためコピーコンストラクタ
	Resource* ret = new Resource(rPair->second);
	mLoadedMap.emplace(src, ret);

	return ret;
}
