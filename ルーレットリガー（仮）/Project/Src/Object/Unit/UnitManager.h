#pragma once
#include<vector>
#include<array>
#include<map>

class UnitBase;
class PlayerUnit;
class EnemyUnit;
class Command;

using Deck = std::array<int, 3>;

class UnitManager
{
public:
	////インスタンスの生成
	//static void CreateInstance(void);
	////インスタンスの取得
	//static UnitManager& GetInstance(void);


	UnitManager();
	~UnitManager();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//ユニットの生成
	void CreateUnit(const Deck& pDeck, const Deck& eDeck);


	//行動中のユニットのコマンド名を取得
	std::vector<Command*> GetCommand(void);

	//行動ユニットの取得
	UnitBase* GetActivUnit(void);
	//全ユニットの取得
	std::vector <UnitBase*> GetUnits(void) { return units_; }

	//行動ユニットを変更する関数
	void ChangeActivUnit(void);
	
	//ユニットが全滅かどうか判断
	bool IsAnniUnit(void);

private:
	//静的インスタンス
	static UnitManager* mInstance;
	
	//ユニットの配列
	std::vector<UnitBase*> units_;


	//スピードが速い順に並び変える
	void SpeedSort(void);

	//全ユニットを行動中ユニットからはずす
	void NotActUnitAll(void);
};

