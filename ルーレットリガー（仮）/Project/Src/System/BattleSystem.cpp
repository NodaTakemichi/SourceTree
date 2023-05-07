#include <math.h>
#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
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
	//ダメージ計算
	auto dmg = roundf(actUnit_->GetAttack() * actCmd_->GetTimes());
	for (auto& unit : targetUnits_)
	{
		unit->Damage(dmg);
	}
}

void BattleSystem::ProcessHeal(void)
{
	//回復計算
	auto heal = roundf(actUnit_->GetAttack() * actCmd_->GetTimes());
	for (auto& unit : targetUnits_)
	{
		unit->Heal(heal);
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

	//ターゲット
	for (auto target : targetUnits_)
	{
		target->SetTargeted(false);
	}
	targetUnits_.clear();

	//選択できるユニット
	for (auto select : selectedUnits_)
	{
		select->SetTargeted(false);
	}
	selectedUnits_.clear();
}

void BattleSystem::CheckSelectTarget(void)
{
	//コマンドの対象
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
	//コマンドの対象になっているユニットを、協調表示させる
	for (auto& target : targetUnits_)
	{
		target->SetTargeted(true);
	}

	//コマンドの対象選択
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

	//対象が既に選択済み、又は必要なし
	if (autom)
	{
		return AsoUtility::OverTime(totalTime_, STOP_WAIT_TIME_AIM);
	}
	else
	{
		//入力情報
		auto& ins = InputManager::GetInstance();
		//クリックしたら、選択完了
		return ins.IsTrgMouseLeft();
	}


}

void BattleSystem::CmdProcess(void)
{
	auto& type = actCmd_->GetCmdType();
	switch (type)
	{
	case Command::CMD_TYPE::NONE:
		break;
	case Command::CMD_TYPE::MISS:
		break;
	case Command::CMD_TYPE::ATTACK:
		ProcessDamege();
		break;
	case Command::CMD_TYPE::HEAL:
		ProcessHeal();
		break;
	case Command::CMD_TYPE::BUFF:
		break;
	case Command::CMD_TYPE::CMD_UP:
		break;
	case Command::CMD_TYPE::END:
		break;
	default:
		break;
	}


	//行動がまだある場合、ここで敵を選択する
	//サブコマンド
	//selfかそれ以外で、ターゲットを決める
}

void BattleSystem::SetRandUnit(void)
{
	//対象がいない敵は無視
	auto& target = actCmd_->GetCmdTarget();
	if (target == Command::CMD_TARGET::NONE)return;

	randUnit_ = rand() % selectedUnits_.size();
}

void BattleSystem::SetTargetUnits(const bool& equal)
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

bool BattleSystem::SelectInTarget(const bool& autom)
{

	if (autom)
	{
		//待機時間をオーバーしたら、処理
		auto time = AsoUtility::OverTime(totalTime_, STOP_WAIT_TIME_AIM);
		if (!time)return false;

		//時間リセット
		totalTime_ = 0.0f;
		//ランダム値とターゲット番号の合否を判断
		if (randUnit_ == targetNum_)
		{
			return true;
		}
		else
		{
			//対象ユニットしていたリセット
			if (targetUnits_[0] != nullptr)
			{
				targetUnits_[0]->SetTargeted(false);
			}
			targetUnits_.clear();

			//ランダム値と合うように、ターゲット番号を変更
			targetNum_++;
			targetNum_ = AsoUtility::Wrap(targetNum_, 0, selectedUnits_.size());
			//選択したユニットを格納する
			targetUnits_.push_back(selectedUnits_[targetNum_]);

			return false;
		}
	}
	else
	{
		//ホイールの入力
		int wheel = GetMouseWheelRotVol();

		//選択入力がある場合、対象ユニットを変戸する
		if (wheel != 0)
		{
			//対象ユニットをリセット
			if (targetUnits_[0] != nullptr)
			{
				targetUnits_[0]->SetTargeted(false);
			}
			targetUnits_.clear();


			//入力が、正方向か負方向か判断
			//正：プラス１　、　負：マイナス１
			targetNum_ += wheel > 0 ? 1 : -1;

			//ナンバーを範囲内に収める
			int max = selectedUnits_.size();
			targetNum_ = AsoUtility::Wrap(targetNum_, 0, max);

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
	}







	return false;
}

