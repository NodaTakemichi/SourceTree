#include<algorithm>
#include<iostream>
#include<tuple>
#include "./PlayerUnit.h"
#include "./EnemyUnit.h"
#include "UnitManager.h"

//シングルトン
/*
UnitManager* UnitManager::mInstance = nullptr;
void UnitManager::CreateInstance(void)
{
	if (mInstance == nullptr)
	{
		mInstance = new UnitManager();
	}
	mInstance->Init();
}
UnitManager& UnitManager::GetInstance(void)
{
	return *mInstance;
}
*/

UnitManager::UnitManager()
{
}

UnitManager::~UnitManager()
{
}

void UnitManager::Init(void)
{

	//ユニットの生成
	CreateUnit();

	//スピード降順ソート
	SpeedSort();
}

void UnitManager::Update(void)
{
	//ユニットの更新
	for (auto& unit : units_)
	{
		unit->Update();
	}
}

void UnitManager::Draw(void)
{
	//ユニットの描画
	for (auto& unit : units_)
	{
		unit->Draw();
	}
}

void UnitManager::Release(void)
{
	//ユニットの破棄
	for (auto& unit : units_)
	{
		unit->Release();
		delete unit;
	}
	units_.clear();
}

std::vector<Command*> UnitManager::GetCommand(void)
{
	//行動ユニットのコマンドを渡す
	for (auto& unit : units_)
	{
		if (unit->IsAct())return unit->GetCommands();
	}
}

UnitBase* UnitManager::GetActivUnit(void)
{
	//各ユニットから,行動が出来て最もスピードが速いユニットを探す。
	for (auto& unit : units_)
	{
		if (unit->IsAct())return unit;
	}
}

void UnitManager::CreateUnit(void)
{
	const std::string path = "Data/UnitData/";

	//ユニットの生成

	//味方
	PlayerUnit* pUnit = new PlayerUnit(2, 1);
		pUnit->Init();
		units_.push_back(pUnit);

		pUnit = new PlayerUnit(8, 2);
		pUnit->Init();
		units_.push_back(pUnit);

		pUnit = new PlayerUnit(3, 3);
		pUnit->Init();
		units_.push_back(pUnit);

	//敵
		EnemyUnit* eUnit = new EnemyUnit(1, 1);
		eUnit->Init();
		units_.push_back(eUnit);

		eUnit = new EnemyUnit(6, 2);
		eUnit->Init();
		units_.push_back(eUnit);

		eUnit = new EnemyUnit(5, 3);
		eUnit->Init();
		units_.push_back(eUnit);
		
}

void UnitManager::SpeedSort(void)
{
	//ユニットの配列を、スピードが大きい順にソートする。

	//スピード速度の比較
	auto compare = [&](UnitBase* x, UnitBase* y) {
		auto speedX = x->GetSpeed();
		auto speedY = y->GetSpeed();
		return  speedX > speedY;
	};
	//ソート
	std::sort(units_.begin(), units_.end(), compare);
}

void UnitManager::ChangeActivUnit(void)
{
	//全ユニットを、行動中ユニットから外す
	NotActUnitAll();

	//各ユニットから,行動が出来て最もスピードが速いユニットを探す。
	for (auto& unit : units_)
	{
		if (!unit->IsAlive())continue;	//死亡時、処理をしない
		if (unit->IsActed())continue;	//行動済みの場合、処理をしない

		//行動済み状態にする
		unit->SetActed(true);
		//行動中ユニットにする
		unit->SetAct(true);

		//行動できる中で、最も行動速度が速いユニットを行動ユニットにする
		return;
	}

	//すべて行動不可の場合、生存ユニットを行動可能状態にする
	for (auto& unit : units_)
	{
		if (!unit->IsAlive())continue;	//死亡時、処理をしない

		//行動可能状態にする
		unit->SetActed(false);
	}
	//もう一度、ユニット検索を行う。
	ChangeActivUnit();

	//return;
}

bool UnitManager::IsAnniUnit(void)
{
	//片方の生存ユニットを確認できなければ、全滅判定

	bool pUnit = false;
	bool eUnit = false;


	for (auto& unit : units_)
	{
		//両陣営、生存している
		if (pUnit && eUnit)return false;

		//生存ユニット
		if (!unit->IsAlive())continue;

		if (unit->GetUnitType() == UnitBase::UNIT_TYPE::PLAYER)
		{
			pUnit = true;
		}
		else
		{
			eUnit = true;
		}
	}


	//排他的論理和
	//片方陣営が全滅していたら、true
	return pUnit ^ eUnit;
}

void UnitManager::NotActUnitAll(void)
{
	for (auto& unit : units_)
	{
		//行動中ユニットから外す
		unit->SetAct(false);
	}
}
