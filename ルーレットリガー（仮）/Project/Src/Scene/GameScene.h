#pragma once
#include <vector>
#include "SceneBase.h"
#include "../Common/Vector2.h"

class UnitManager;
class Roulette;
class GameUI;

class BattleSystem;
class DeathStaging;
class EffectManager;

class GameScene : public SceneBase
{

public:
	enum class GAME_PHASE
	{
		NONE,
		BATTLE_START,
		RULLET_TIME,
		AIM,
		EFFECT,
		BATTLE,
		BUFF_EFFECT,
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
	void UpdateEffect(void);
	void UpdateBattle(void);
	void UpdateBuffEffect(void);
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
	//ネクストフェーズ
	GAME_PHASE nextPhase_;

	//ユニットのバトルシステム
	BattleSystem* battleSys_;


	//フレーム
	int frameImg_;
	int topFrameImg_;

	//行動ユニットの操作が自動か手動か判断
	bool actUnitAoutm_;

	//フェーズ変更
	void ChangeGamePhase(GAME_PHASE phase);


};
