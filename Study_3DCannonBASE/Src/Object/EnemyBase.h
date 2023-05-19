#pragma once
#include <string>
#include <DxLib.h>
#include"../Common/Vector2.h"
class EnemyBase
{
public:
	//敵の種類
	enum class ENEMY_TYPE
	{
		SMALL,
		MEDIUM,
		BAT,
		BIG,
		MAX
	};

	//キャラパラメータ
	struct Par
	{
		float speed;	//移動速度
		float scale;	//大きさ
		int maxHp;		//HP
		int animNo;		//アニメーション番号
	}; 


	// コンストラクタ
	EnemyBase();
	// デストラクタ
	virtual ~EnemyBase(void);

	// 初期処理(最初の１回のみ実行)
	virtual void Init(void);
	// パラメータ設定(純粋仮想関数)
	virtual void SetParam(void);
	// 更新処理(毎フレーム実行)
	virtual void Update(void);
	// 描画処理(毎フレーム実行)
	virtual void Draw(void);
	// 解放処理(最後の１回のみ実行)
	virtual void Release(void);

	//エネミータイプのセット
	void SetEnemyType(ENEMY_TYPE type);

	// 座標の取得
	VECTOR GetPos(void);
	// 座標の設定
	void SetPos(VECTOR pos);
	// 生存判定
	bool IsAlive(void);
	// 生存判定
	void SetAlive(bool alive);
	// ダメージを与える
	void Damage(int damage);

	// 衝突用の中心座標の取得
	VECTOR GetCollisionPos(void);
	// 衝突用の球体半径の取得
	float GetCollisionRadius(void) {return collisionRadius_;}


protected:

	// 元となる弾のモデルID
	int baseModelId_;
	// 弾のモデルID
	int modelId_;
	// 大きさ
	VECTOR scl_;
	// 角度
	VECTOR rot_;
	// 表示座標
	VECTOR pos_;
	// 移動速度
	float speed_;
	// 移動方向
	VECTOR dir_;

	// 体力
	int hp_;
	// 体力最大値
	int hpMax_;
	// 体力の現在表示値
	float hpNow_;
	// 体力の過去値
	int hpBefore_;
	// 生存判定
	bool isAlive_;
	//HPの線形補間に使用するタイム
	float hpLerpTime_;

	//合計時間
	float totalTime_;

	// アニメーションをアタッチ番号
	int animAttachNo_;
	// アニメーションの総再生時間
	float animTotalTime_;
	// 再生中のアニメーション時間
	float stepAnim_;
	// アニメーション速度
	float speedAnim_;

	// 衝突判定用の球体半径
	float collisionRadius_;
	// 衝突判定用の球体中心の調整座標
	VECTOR collisionLocalPos_;

	//キャラの種類
	ENEMY_TYPE type_;

	//頂点情報
	VERTEX2DSHADER mVertex[4];
	WORD mIndex[6];
	//シェーダー
	int psHpShader_;
	int psHpShaderConstBuf_;
	//描画用の四角頂点のの作成
	void MakeSquereVertex(Vector2 pos);

};