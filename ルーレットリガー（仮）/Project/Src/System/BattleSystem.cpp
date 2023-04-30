#include <math.h>
#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Object/Unit/UnitBase.h"
#include "../Object/Unit/Command.h"

#include "../_debug/_DebugDispOut.h"

#include "BattleSystem.h"

BattleSystem::BattleSystem()
{
}

BattleSystem::~BattleSystem()
{
}

void BattleSystem::Init(void)
{
	targetNum_ = 0;
}

void BattleSystem::Release(void)
{
}

void BattleSystem::SetBattleData(UnitBase* unit, Command* cmd, std::vector<UnitBase*> units)
{
	actUnit_ = unit;
	actCmd_ = cmd;
	units_ = units;
}

void BattleSystem::CheckSelectTarget(void)
{
	//�R�}���h�̑Ώ�
	auto target = actCmd_->GetSkillTarget();

	switch (target)
	{
	case Command::SKILL_TARGET::NONE:
		return;
	case Command::SKILL_TARGET::ENEMY:
		SetTargetUnits(false);
		targetUnits_.push_back(selectedUnits_[0]);
		break;
	case Command::SKILL_TARGET::ENEMY_ALL:
		SetTargetUnits(false);
		targetUnits_ = selectedUnits_;
		break;
	case Command::SKILL_TARGET::ENEMY_RAND:
		SetTargetUnits(false);
		break;
	case Command::SKILL_TARGET::SELF:
		selectedUnits_.push_back(actUnit_);
		targetUnits_ = selectedUnits_;
		break;
	case Command::SKILL_TARGET::PLAYER:
		SetTargetUnits(true);
		targetUnits_.push_back(selectedUnits_[0]);
		break;
	case Command::SKILL_TARGET::PLAUER_ALL:
		targetUnits_ = selectedUnits_;
		SetTargetUnits(true);
		break;
	case Command::SKILL_TARGET::END:
		break;
	default:
		break;
	}
}

bool BattleSystem::SelectUnit(void)
{
	//���͏��
	auto& ins = InputManager::GetInstance();

	//�R�}���h�̑ΏۂɂȂ��Ă��郆�j�b�g���킩��₷���\��������
	for (auto& target : targetUnits_)
	{
		target->SetTargeted(true);
	}

	_dbgDrawFormatString(0, 0, 0x00ffff, "�^�[�Q�b�g�i���o�[�F%d", targetNum_);

	//�R�}���h�̑Ώ�
	auto target = actCmd_->GetSkillTarget();

	switch (target)
	{
	case Command::SKILL_TARGET::ENEMY:
		return SelectInTarget();
		break;
	case Command::SKILL_TARGET::ENEMY_RAND:
		break;
	case Command::SKILL_TARGET::PLAYER:
		return SelectInTarget();
		break;
	default:
		break;
	}

	//�N���b�N������
	return ins.IsTrgMouseLeft();

}

void BattleSystem::SetTargetUnits(bool equal)
{
	for (auto& unit : units_)
	{
		if (!unit->IsAlive())continue;	//���S��Ԃ̏ꍇ�A�������Ȃ�

		//�R�}���h�Ώۂɖ��������邩�A��������邩�̔��f
		if (equal)
		{
			//�s�����j�b�g�̑���̏ꍇ�A���������Ȃ�
			if (actUnit_->GetUnitType() != unit->GetUnitType())continue;
		}
		else
		{
			//�s�����j�b�g�̖����̏ꍇ�A���������Ȃ�
			if (actUnit_->GetUnitType() == unit->GetUnitType())continue;
		}

		//�I�����j�b�g�Ɋi�[
		selectedUnits_.push_back(unit);
	}
}

bool BattleSystem::SelectInTarget(void)
{

	int test = GetMouseWheelRotVol();

	//���͂�����ꍇ
	if (test != 0)
	{
		//////////////////////////////////////////////////////////////////
		if (targetUnits_[targetNum_] != nullptr)
		{
			targetUnits_[targetNum_]->SetTargeted(false);
		}
		targetUnits_.clear();
	}

	if (test > 0)
	{

		targetNum_++;

		////�i���o�[��͈͓��Ɏ��߂�
		int max = selectedUnits_.size() - 1;
		targetNum_ = std::clamp(targetNum_, 0, max);

		//�I���������j�b�g���i�[����
		targetUnits_.push_back(selectedUnits_[targetNum_]);
	}
	else if (test < 0)
	{
		targetNum_--;
		////�i���o�[��͈͓��Ɏ��߂�
		int max = selectedUnits_.size() - 1;
		targetNum_ = std::clamp(targetNum_, 0, max);

		//�I���������j�b�g���i�[����
		targetUnits_.push_back(selectedUnits_[targetNum_]);


	}


	
	//���͏��
	auto& ins = InputManager::GetInstance();
	//����
	if (ins.IsClickMouseLeft())
	{
		return true;
	}


	return false;
}

void BattleSystem::None(void)
{
	//�������Ȃ�
}

void BattleSystem::Self(void)
{
	//�������g
	selectedUnits_.push_back(actUnit_);
}

void BattleSystem::Enemy(void)
{
	//����i��́j

	//�Ώۂ̑���i�S�j���Z�b�g
	SetTargetUnits(false);

	//�e�X�g
	auto dmg = roundf(actUnit_->GetAttack() * actCmd_->GetTimes());

	targetUnits_[0]->Damage(dmg);
}
