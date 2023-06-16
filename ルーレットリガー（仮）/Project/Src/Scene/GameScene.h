#pragma once
#include <vector>
#include "SceneBase.h"
#include "../Common/Vector2.h"

class UnitManager;
class Roulette;
class GameUI;

class BattleSystem;
class EffectManager;

class GameScene : public SceneBase
{

public:
	enum class GAME_PHASE
	{
		BATTLE_START,
		RULLET_TIME,
		AIM,
		EFFECT,
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
	void UpdateEffect(void);
	void UpdateBattle(void);
	void UpdateTurnEnd(void);


private:
	//ユニットマネージャー
	UnitManager* unitMng_;
	//ルーレット
	Roulette* roulette_;
	//UI
	GameUI* GameUi_;
	//エフェクトマネージャー
	EffectManager* efMng_;

	//ゲームフェーズ
	GAME_PHASE phase_;

	//ユニットのバトルシステム
	BattleSystem* battleSys_;

	//マウス
	int mouseImg_;
	//背景画像
	int bgImg_;
	//フレーム
	int frameImg_;

	//ターン文字、色
	std::string turnString_;
	int turnCol_;

	//経過総時間
	float mTotalTime;

	//行動ユニットの操作が自動か手動か判断
	bool actUnitAoutm_;

	//フェーズ変更
	void ChangeGamePhase(GAME_PHASE phase);

	///テスト
	Vector2 testPos;
	int testNum;
	float testScale;

};
