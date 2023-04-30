#pragma once
#include<vector>

class UnitBase;
class Command;

class BattleSystem
{
public:

	BattleSystem();
	~BattleSystem();

	void Init(void);
	void Release(void);


	//バトルに必要な情報をセットする
	void SetBattleData(UnitBase* unit, Command* cmd, 
		std::vector<UnitBase*> units);

	//コマンドの効果対象によって、対象を判断する
	void CheckSelectTarget(void);

	//実際にアクションをする対象を選択する
	bool SelectUnit(void);

private:

	UnitBase* actUnit_;				//行動ユニット
	Command* actCmd_;				//発動コマンド
	std::vector<UnitBase*> units_;	//全ユニット

	//対象ナンバー
	int targetNum_;


	//選択できるユニット情報を格納
	std::vector<UnitBase*> selectedUnits_;	

	//選択ユニットから、実際に対象とするユニットを格納
	std::vector<UnitBase*> targetUnits_;

	/// 対象のユニット情報を取得する
	/// <param name="equal">true:味方、false:相手</param>
	void SetTargetUnits(bool equal);

	//対象がいる中から、選択する
	bool SelectInTarget(void);

	//対象別Update
	void None(void);
	void Self(void);
	void Enemy(void);
};

