#include<algorithm>
#include<iostream>
#include<tuple>
#include "./PlayerUnit.h"
#include "./EnemyUnit.h"
#include "UnitManager.h"

//�V���O���g��
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

	//���j�b�g�̐���
	CreateUnit();

	//�X�s�[�h�~���\�[�g
	SpeedSort();
}

void UnitManager::Update(void)
{
	//���j�b�g�̍X�V
	for (auto& unit : units_)
	{
		unit->Update();
	}
}

void UnitManager::Draw(void)
{
	//���j�b�g�̕`��
	for (auto& unit : units_)
	{
		unit->Draw();
	}
}

void UnitManager::Release(void)
{
	//���j�b�g�̔j��
	for (auto& unit : units_)
	{
		unit->Release();
		delete unit;
	}
	units_.clear();
}

std::vector<Command*> UnitManager::GetCommand(void)
{
	//�s�����j�b�g�̃R�}���h��n��
	for (auto& unit : units_)
	{
		if (unit->IsAct())return unit->GetCommands();
	}
}

UnitBase* UnitManager::GetActivUnit(void)
{
	//�e���j�b�g����,�s�����o���čł��X�s�[�h���������j�b�g��T���B
	for (auto& unit : units_)
	{
		if (unit->IsAct())return unit;
	}
}

void UnitManager::CreateUnit(void)
{
	const std::string path = "Data/UnitData/";

	//���j�b�g�̐���

	//����
	PlayerUnit* pUnit = new PlayerUnit(2, 1);
		pUnit->Init();
		units_.push_back(pUnit);

		pUnit = new PlayerUnit(8, 2);
		pUnit->Init();
		units_.push_back(pUnit);

		pUnit = new PlayerUnit(3, 3);
		pUnit->Init();
		units_.push_back(pUnit);

	//�G
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
	//���j�b�g�̔z����A�X�s�[�h���傫�����Ƀ\�[�g����B

	//�X�s�[�h���x�̔�r
	auto compare = [&](UnitBase* x, UnitBase* y) {
		auto speedX = x->GetSpeed();
		auto speedY = y->GetSpeed();
		return  speedX > speedY;
	};
	//�\�[�g
	std::sort(units_.begin(), units_.end(), compare);
}

void UnitManager::ChangeActivUnit(void)
{
	//�S���j�b�g���A�s�������j�b�g����O��
	NotActUnitAll();

	//�e���j�b�g����,�s�����o���čł��X�s�[�h���������j�b�g��T���B
	for (auto& unit : units_)
	{
		if (!unit->IsAlive())continue;	//���S���A���������Ȃ�
		if (unit->IsActed())continue;	//�s���ς݂̏ꍇ�A���������Ȃ�

		//�s���ςݏ�Ԃɂ���
		unit->SetActed(true);
		//�s�������j�b�g�ɂ���
		unit->SetAct(true);

		//�s���ł��钆�ŁA�ł��s�����x���������j�b�g���s�����j�b�g�ɂ���
		return;
	}

	//���ׂčs���s�̏ꍇ�A�������j�b�g���s���\��Ԃɂ���
	for (auto& unit : units_)
	{
		if (!unit->IsAlive())continue;	//���S���A���������Ȃ�

		//�s���\��Ԃɂ���
		unit->SetActed(false);
	}
	//������x�A���j�b�g�������s���B
	ChangeActivUnit();

	//return;
}

bool UnitManager::IsAnniUnit(void)
{
	//�Е��̐������j�b�g���m�F�ł��Ȃ���΁A�S�Ŕ���

	bool pUnit = false;
	bool eUnit = false;


	for (auto& unit : units_)
	{
		//���w�c�A�������Ă���
		if (pUnit && eUnit)return false;

		//�������j�b�g
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


	//�r���I�_���a
	//�Е��w�c���S�ł��Ă�����Atrue
	return pUnit ^ eUnit;
}

void UnitManager::NotActUnitAll(void)
{
	for (auto& unit : units_)
	{
		//�s�������j�b�g����O��
		unit->SetAct(false);
	}
}
