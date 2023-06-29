#include "UnitDataManager.h"

UnitDataManager* UnitDataManager::instance_ = nullptr;

void UnitDataManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new UnitDataManager();
	}
	instance_->Init();
}

UnitDataManager& UnitDataManager::GetInstance(void)
{
	return *instance_;
}

void UnitDataManager::Init(void)
{
	LoadUnitData();
}

void UnitDataManager::Release(void)
{
}

void UnitDataManager::LoadUnitData(void)
{
}

const UnitData& UnitDataManager::GetUnitData(const int& num)
{
    // TODO: return ステートメントをここに挿入します
}

const int& UnitDataManager::GetUnitImg(const int& num)
{
	return 0;
}

UnitDataManager::UnitDataManager(void)
{
}

UnitDataManager::~UnitDataManager(void)
{
}

