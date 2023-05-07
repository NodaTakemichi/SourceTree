#pragma once
#include <vector>
#include "SceneBase.h"

class UnitManager;
class Roulette;
class GameUI;

class BattleSystem;

class GameScene : public SceneBase
{

public:
	enum class GAME_PHASE
	{
		BATTLE_START,
		RULLET_TIME,
		AIM,
		BATTLE,
		TURN_END,
		GAME_END

	};


	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void UpdateRouTime(void);
	void UpdateAIM(void);
	void UpdateBattle(void);
	void UpdateTurnEnd(void);


private:
	//ユニットマネージャー
	UnitManager* unitMng_;
	//ルーレット
	Roulette* roulette_;
	//UI
	GameUI* GameUi_;

	//ゲームフェーズ
	GAME_PHASE phase_;

	//ユニットのバトルシステム
	BattleSystem* battleSys_;


	//背景画像
	int bgImg_;
	//フレーム
	int frameImg_;


	//経過総時間
	float mTotalTime;

	//フェーズ変更
	void ChangeGamePhase(GAME_PHASE phase);

	//行動ユニットの操作が自動か手動か判断
	bool actUnitAoutm_;


};
