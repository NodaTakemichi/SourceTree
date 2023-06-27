#pragma once
class DeathStaging
{
public:

	DeathStaging();
	~DeathStaging();

	void Init(void);
	void Draw(void);
	void Release(void);

	void DrawDeathUnit(void);

private:

	//マスク画像
	int maskImg_;
	//死亡フレーム画像
	int frameImg_;
	//死亡ユニット画像
	int unitImg_;
	//死亡背景
	int backImg_;

	//通常シェーダー
	int psReverTex_;
	//死亡ユニット用シェーダー
	int deathShader_;


	//マスクシェーダーハンドル
	int psMask_;

	//マスクスクリーン
	int maskScreen_;




};

