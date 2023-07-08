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
	//初期デッキ
	deck_ = { 3,4,17 };

	//初期ユニット
	unitPool_ = { 0,4,5,6,7,17,13 };

}

void DeckManager::Release(void)
{
}

void DeckManager::LoadCmdData(void)
{
}

void DeckManager::SetDeck(std::array<int, 3> deck)
{
	deck_ = deck;
}

void DeckManager::AddUnit(const int& unitNum)
{
	unitPool_.push_back(unitNum);

	//ソート

}

DeckManager::DeckManager(void)
{
}

DeckManager::~DeckManager(void)
{
}
