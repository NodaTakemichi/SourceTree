#pragma once
#include<vector>
#include<DxLib.h>
class ShotBase;

class Cannon
{
public:
	//砲身のX回転制限（最大）
	static constexpr float MAX_ANGLE_X = 15.0f * DX_PI_F / 180.0f;
	//砲身のX回転制限（最低）
	static constexpr float MN_ANGLE_X = -30.0f * DX_PI_F / 180.0f;

	//弾発射後の硬直時間
	static constexpr float SHOT_DELAY = 1.0f;

	//爆発のサイズ
	static constexpr float BLAST_SIZE_X = 32;
	static constexpr float BLAST_SIZE_Y = 32;
	//爆発のアニメーション数
	static constexpr int BLAST_ANIM_NUM = 16;


	Cannon();
	~Cannon();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//弾の取得
	std::vector<ShotBase*> GetShots(void);

private:
	//3D基本情報
	//土台
	VECTOR standScl_;
	VECTOR standRot_;
	VECTOR standPos_;
	int standModelId_;

	//砲身
	VECTOR barrelScl_;
	VECTOR barrelRot_;
	VECTOR barrelPos_;
	int barrelModelId_;

	//相対座標
	VECTOR barrelLocalos_;

	//爆発の画像
	int blastImgs_[BLAST_ANIM_NUM];

	// ショット(ポインタ)
	std::vector<ShotBase*> shots_;
	// 弾のモデルID
	int shotModelId_;
	// 弾発射後の硬直時間計算用
	float stepShotDelay_;
	// 回転操作
	void ProcessRot(void);
	// 発射操作
	void ProcessShot(void);
	// 有効な弾を取得する
	ShotBase* GetValidShot(void);
};

