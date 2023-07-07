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
	//�����f�b�L
	deck_ = { 3,4,5 };

	//�������j�b�g
	unitPool_ = { 3,4,5,6,7,8,13 };

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

	//�\�[�g

}

DeckManager::DeckManager(void)
{
}

DeckManager::~DeckManager(void)
{
}
