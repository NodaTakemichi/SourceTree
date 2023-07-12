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
	deck_ = { 0,1,2 };

	//所持ユニット
	unitPool_ = { 0,1,2,4,5,6,7,17,13 };

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
	//ユニットの追加
	unitPool_.push_back(unitNum);

	//ソート

}

DeckManager::DeckManager(void)
{
}

DeckManager::~DeckManager(void)
{
}
