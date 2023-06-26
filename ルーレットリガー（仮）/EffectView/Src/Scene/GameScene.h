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

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;



private:
	//エフェクトマネージャー
	EffectManager* efMng_;



	///テスト
	Vector2 testPos;
	int testNum;
	float testScale;
	std::string path;

};
