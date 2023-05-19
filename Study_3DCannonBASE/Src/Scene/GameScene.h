#pragma once
#include <vector>
#include "SceneBase.h"
class Stage;
class Cannon;
class EnemyBase;

class GameScene :
	public SceneBase
{
public:
	//ゲームオーバー地点衝突判定用球体半径
	static constexpr float OVER_COL_RADIOUS = 35.0f;

	//ウェーブ
	enum class Wave
	{
		FIRST,
		LAST,
		END
	};

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	Stage* stage_;
	Cannon* cannnon_;

	//敵のモデル
	EnemyBase*  enemy_;

	// ゲームオーバー地点
	VECTOR gameoverPoint_;
	// ゲームオーバー判定
	bool isGameover_;
	// ゲームオーバー画像
	int imgGameover_;

	// ゲームクリア画像
	int imgGameclear_;
	// ネクストウェーブ画像
	int imgNextWave_;

	//生成する敵の数
	int enemyCount;
	//敵生成の時間間隔
	float stepCreateDis;

	//ウェーブ管理
	Wave wave_;
	void ChangeWave(Wave wave);

};

