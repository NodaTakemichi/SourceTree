#include "BattleDataManager.h"

BattleDataManager* BattleDataManager::instance_ = nullptr;

void BattleDataManager::CreateInstance(void)
{
    if (instance_ == nullptr)
    {
        instance_ = new BattleDataManager;
    }
    instance_->Init();
}

BattleDataManager& BattleDataManager::GetInstance(void)
{
    return *instance_;
}

void BattleDataManager::Init(void)
{
    //������
    bData_ = {
        {7,8,9},
        {4,14,15},
        0,
        0
    };
}

void BattleDataManager::Release(void)
{
}

void BattleDataManager::SetBattleData(const BattleData& data)
{
    bData_ = data;
}

BattleDataManager::BattleDataManager(void)
{
}

BattleDataManager::~BattleDataManager(void)
{
}
