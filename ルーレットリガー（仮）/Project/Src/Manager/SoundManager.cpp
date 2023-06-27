#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "SoundManager.h"

SoundManager* SoundManager::mInstance = nullptr;

void SoundManager::CreateInstance(void)
{
	if (mInstance == nullptr)
	{
		mInstance = new SoundManager();
	}
	mInstance->Init();
}

SoundManager& SoundManager::GetInstance(void)
{
	return *mInstance;
}

void SoundManager::Init(void)
{

	Resource res;

	// スタートロゴ
	//res = Resource(Resource::TYPE::IMG, Application::PATH_IMAGE + "StartLogo.png");
	//mResourcesMap.emplace(SRC::START_LOGO, res);


}

void SoundManager::Release(void)
{
	//for (auto& p : mLoadedMap)
	//{
	//	p.second->Release();
	//	delete p.second;
	//}

	//mLoadedMap.clear();
}

int SoundManager::LoadSound(SRC src)
{
	//Resource* res = _Load(src);
	//if (res == nullptr)
	//{
	//	return Resource();
	//}
	//Resource ret = *res;
	//return *res;
}

SoundManager::SoundManager(void)
{
}

SoundManager::~SoundManager(void)
{
	delete mInstance;
}

//Resource* SoundManager::_Load(SRC src)
//{
	//const auto& lPair = mLoadedMap.find(src);
	//if (lPair != mLoadedMap.end())
	//{
	//	return lPair->second;
	//}

	//const auto& rPair = mResourcesMap.find(src);
	//if (rPair == mResourcesMap.end())
	//{
	//	// 登録されていない
	//	return nullptr;
	//}

	//rPair->second.Load();

	//// 念のためコピーコンストラクタ
	//Resource* ret = new Resource(rPair->second);
	//mLoadedMap.emplace(src, ret);

	//return ret;
//}
