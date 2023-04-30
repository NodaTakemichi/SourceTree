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
	//コマンドの対象
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
	//入力情報
	auto& ins = InputManager::GetInstance();

	//コマンドの対象になっているユニットをわかりやすく表示させる
	for (auto& target : targetUnits_)
	{
		target->SetTargeted(true);
	}

	_dbgDrawFormatString(0, 0, 0x00ffff, "ターゲットナンバー：%d", targetNum_);

	//コマンドの対象
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

	//クリックしたら
	return ins.IsTrgMouseLeft();

}

void BattleSystem::SetTargetUnits(bool equal)
{
	for (auto& unit : units_)
	{
		if (!unit->IsAlive())continue;	//死亡状態の場合、処理しない

		//コマンド対象に味方を入れるか、相手を入れるかの判断
		if (equal)
		{
			//行動ユニットの相手の場合、処理をしない
			if (actUnit_->GetUnitType() != unit->GetUnitType())continue;
		}
		else
		{
			//行動ユニットの味方の場合、処理をしない
			if (actUnit_->GetUnitType() == unit->GetUnitType())continue;
		}

		//選択ユニットに格納
		selectedUnits_.push_back(unit);
	}
}

bool BattleSystem::SelectInTarget(void)
{

	int test = GetMouseWheelRotVol();

	//入力がある場合
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

		////ナンバーを範囲内に収める
		int max = selectedUnits_.size() - 1;
		targetNum_ = std::clamp(targetNum_, 0, max);

		//選択したユニットを格納する
		targetUnits_.push_back(selectedUnits_[targetNum_]);
	}
	else if (test < 0)
	{
		targetNum_--;
		////ナンバーを範囲内に収める
		int max = selectedUnits_.size() - 1;
		targetNum_ = std::clamp(targetNum_, 0, max);

		//選択したユニットを格納する
		targetUnits_.push_back(selectedUnits_[targetNum_]);


	}


	
	//入力情報
	auto& ins = InputManager::GetInstance();
	//決定
	if (ins.IsClickMouseLeft())
	{
		return true;
	}


	return false;
}

void BattleSystem::None(void)
{
	//何もしない
}

void BattleSystem::Self(void)
{
	//自分自身
	selectedUnits_.push_back(actUnit_);
}

void BattleSystem::Enemy(void)
{
	//相手（一体）

	//対象の相手（全）をセット
	SetTargetUnits(false);

	//テスト
	auto dmg = roundf(actUnit_->GetAttack() * actCmd_->GetTimes());

	targetUnits_[0]->Damage(dmg);
}
