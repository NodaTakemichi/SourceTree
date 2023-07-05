#include "DeckManager.h"

DeckManager* DeckManager::instance_ = nullptr;

void DeckManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new DeckManager();
	}
	instance_->Init();
}

DeckManager& DeckManager::GetInstance(void)
{
	return *instance_;
}

void DeckManager::Init(void)
{
}

void DeckManager::Release(void)
{
}

void DeckManager::LoadCmdData(void)
{
}

void DeckManager::AddUnit(const int& unitNum)
{
	unitPool_.push_back(unitNum);

	deck_ = { 1,1,1 };
}

DeckManager::DeckManager(void)
{
}

DeckManager::~DeckManager(void)
{
}
