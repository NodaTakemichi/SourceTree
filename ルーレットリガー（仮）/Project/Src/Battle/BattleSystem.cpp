#include <math.h>
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
#include "../Object/Unit/UnitBase.h"
#include "../Object/Unit/Status/Command.h"

#include "../_debug/_DebugDispOut.h"

#include"DeathStaging.h"
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
	totalTime_ = 0.0f;
	randUnit_ = 0;
}

void BattleSystem::Release(void)
{
	targetUnits_.clear();
	selectedUnits_.clear();
}

void BattleSystem::ProcessDamege(void)
{
	//�_���[�W�v�Z
	auto dmg = roundf(actUnit_->GetAttack() * actCmd_->GetTimes());
	for (auto& unit : targetUnits_)
	{
		//AVOIDANCE��Ԃ̃��j�b�g�́A�_���[�W���������Ȃ�
		if (unit->CheckOwnBuff(Buff::BUFF_TYPE::AVOIDANCE))continue;

		unit->Damage(dmg);
	}
}

void BattleSystem::ProcessHeal(void)
{
	//�񕜌v�Z
	auto heal = roundf(actUnit_->GetAttack() * actCmd_->GetTimes());
	for (auto& unit : targetUnits_)
	{
		unit->Heal(heal);
	}
}

void BattleSystem::ProcessBuff(void)
{
	//�o�t�̕t�^
	auto buff = actCmd_->GetCmdBuff();
	for (auto& unit : targetUnits_)
	{
		unit->GiveBuff(buff);
	}
}

void BattleSystem::SetBattleData(UnitBase* unit, Command* cmd, std::vector<UnitBase*> units)
{
	actUnit_ = unit;
	actCmd_ = cmd;
	units_ = units;
}

void BattleSystem::ResetSelectUnits(void)
{
	targetNum_ = 0;
	totalTime_ = 0.0f;

	//�^�[�Q�b�g
	for (auto target : targetUnits_)
	{
		target->SetTargeted(false);
	}
	targetUnits_.clear();

	//�I���ł��郆�j�b�g
	for (auto select : selectedUnits_)
	{
		select->SetTargeted(false);
	}
	selectedUnits_.clear();
}

void BattleSystem::CheckSelectTarget(void)
{
	//Select�z��ɓ��ꂽ���j�b�g���A
	//�S���ΏۂƂ��邩�A���̒������̑I�Ԃ����f����

	//�R�}���h�̑Ώ�
	auto& target = actCmd_->GetCmdTarget();

	switch (target)
	{
	case Command::CMD_TARGET::NONE:
		return;
	case Command::CMD_TARGET::ENEMY:
		SetTargetUnits(false);
		targetUnits_.push_back(selectedUnits_[0]);
		break;
	case Command::CMD_TARGET::ENEMY_ALL:
		SetTargetUnits(false);
		targetUnits_ = selectedUnits_;
		break;
	case Command::CMD_TARGET::ENEMY_RAND:
		SetTargetUnits(false);
		break;
	case Command::CMD_TARGET::SELF:
		selectedUnits_.push_back(actUnit_);
		targetUnits_ = selectedUnits_;
		break;
	case Command::CMD_TARGET::PLAYER:
		SetTargetUnits(true);
		targetUnits_.push_back(selectedUnits_[0]);
		break;
	case Command::CMD_TARGET::PLAYER_ALL:
		SetTargetUnits(true);
		targetUnits_ = selectedUnits_;
		break;
	case Command::CMD_TARGET::END:
		break;
	default:
		break;
	}
}

bool BattleSystem::SelectUnit(const bool& autom)
{
	//�R�}���h�̑ΏۂɂȂ��Ă��郆�j�b�g���A�����\��������
	for (auto& target : targetUnits_)
	{
		target->SetTargeted(true);
	}

	//�R�}���h�̑ΏۑI��
	auto& target = actCmd_->GetCmdTarget();
	switch (target)
	{
	case Command::CMD_TARGET::ENEMY:
	case Command::CMD_TARGET::PLAYER:
		return SelectInTarget(autom);
	case Command::CMD_TARGET::ENEMY_RAND:
		return SelectInTarget(true);
	default:
		break;
	}

	//�Ώۂ����ɑI���ς݁A���͕K�v�Ȃ�
	if (autom)
	{
		return AsoUtility::OverTime(totalTime_, STOP_WAIT_TIME_AIM);
	}
	else
	{
		//���͏��
		auto& ins = InputManager::GetInstance();
		//�N���b�N������A�I������
		return ins.IsTrgMouseLeft();
	}
}

void BattleSystem::CmdProcess(void)
{
	auto& type = actCmd_->GetCmdType();
	switch (type)
	{
	case Command::CMD_TYPE::MISS:
		break;
	case Command::CMD_TYPE::ATTACK:
		ProcessDamege();
		break;
	case Command::CMD_TYPE::HEAL:
		ProcessHeal();
		break;
	case Command::CMD_TYPE::BUFF:
		ProcessBuff();
		break;
	case Command::CMD_TYPE::CMD_UP:
		break;
	default:
		break;
	}


	//�s�����܂�����ꍇ�A�����œG��I������
	//�T�u�R�}���h
	//self������ȊO�ŁA�^�[�Q�b�g�����߂�
}

void BattleSystem::SetRandUnit(void)
{
	//�Ώۂ����Ȃ��G�͖���
	auto& target = actCmd_->GetCmdTarget();
	if (target == Command::CMD_TARGET::NONE)return;

	//�����_���l
	randUnit_ = SceneManager::GetInstance().GetRand(0, selectedUnits_.size() - 1);
}

bool BattleSystem::FinishedDecHP(void)
{
	bool finish = true;
	for (auto& unit : targetUnits_)
	{
		//���S���o���̏ꍇ�A�������~
		auto st = DeathStaging::GetInstance().PlayingStaging();
		if (st)return false;

		//���j�b�g��HP�����X�Ɍ��������鏈��
		//��ł����I��������ꍇ�Afinish��false�ɂ���
		finish &= unit->DecHpProcess();
	}

	return finish;
}

bool BattleSystem::FinishedBuffEffect(void)
{
	bool finish = true;
	for (auto& unit : targetUnits_)
	{
		//���j�b�g�̃o�t�G�t�F�N�g���Đ����鏈��
		//��ł����I��������ꍇ�Afinish��false�ɂ���
		finish &= unit->PlayBuffEffect();
	}

	return finish;
}

void BattleSystem::SetTargetUnits(const bool& equal)
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

bool BattleSystem::SelectInTarget(const bool& autom)
{

	if (autom)
	{
		//�ҋ@���Ԃ��I�[�o�[������A����
		auto time = AsoUtility::OverTime(totalTime_, STOP_WAIT_TIME_AIM);
		if (!time)return false;

		//���ԃ��Z�b�g
		totalTime_ = 0.0f;
		//�����_���l�ƃ^�[�Q�b�g�ԍ��̍��ۂ𔻒f
		if (randUnit_ == targetNum_)
		{
			return true;
		}
		else
		{
			//�Ώۃ��j�b�g���Ă������Z�b�g
			if (targetUnits_[0] != nullptr)
			{
				targetUnits_[0]->SetTargeted(false);
			}
			targetUnits_.clear();

			//�����_���l�ƍ����悤�ɁA�^�[�Q�b�g�ԍ���ύX
			targetNum_++;
			targetNum_ = AsoUtility::Wrap(targetNum_, 0, selectedUnits_.size());
			//�I���������j�b�g���i�[����
			targetUnits_.push_back(selectedUnits_[targetNum_]);

			return false;
		}
	}
	else
	{
		//�z�C�[���̓���
		int wheel = GetMouseWheelRotVol();

		//�I����͂�����ꍇ�A�Ώۃ��j�b�g��ό˂���
		if (wheel != 0)
		{
			//�Ώۃ��j�b�g�����Z�b�g
			if (targetUnits_[0] != nullptr)
			{
				targetUnits_[0]->SetTargeted(false);
			}
			targetUnits_.clear();


			//���͂��A�������������������f
			//���F�v���X�P�@�A�@���F�}�C�i�X�P
			targetNum_ += wheel > 0 ? 1 : -1;

			//�i���o�[��͈͓��Ɏ��߂�
			int max = selectedUnits_.size();
			targetNum_ = AsoUtility::Wrap(targetNum_, 0, max);

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
	}


	return false;
}

