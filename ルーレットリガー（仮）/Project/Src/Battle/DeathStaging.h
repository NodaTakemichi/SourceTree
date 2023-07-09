#pragma once
class DeathStaging
{
public:
	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static DeathStaging& GetInstance(void);


	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void DrawDeathUnit(void);

	//死亡ユニットのセット
	void SetDeathUnit(const int& unitNum);

	//死亡演出の再生
	void PlayDeathStaging(void);

	//死亡演出の終了
	bool FinishStaging(void);


private:
	// 静的インスタンス
	static DeathStaging* instance_;


	//ユニット画像
	int duImg_;

	//死亡ユニット画像
	int unitImg_;

	//再生中か判断
	bool isPlaying_;


	//マスク画像
	int maskImg_;
	//死亡フレーム画像
	int frameImg_;
	//死亡背景
	int backImg_;

	//通常シェーダー
	int psReverTex_;
	//死亡ユニット用シェーダー
	int psDeathShader_;


	//マスクシェーダーハンドル
	int psMask_;

	//マスクスクリーン
	int maskScreen_;


	DeathStaging();
	~DeathStaging();


};

