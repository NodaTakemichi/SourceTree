#pragma once
class DeathStaging
{
public:

	DeathStaging();
	~DeathStaging();

	void Init(void);
	void Draw(void);
	void Release(void);

	void DrawStaging(void);
	void DrawShader(void);

private:

	//マスク画像
	int maskImg_;
	//死亡フレーム画像
	int frameImg_;
	//死亡ユニット画像
	int unitImg_;


	//死亡ユニット用シェーダー
		//シェーダー関連
	//頂点情報
	VERTEX2DSHADER vertex_[4];
	WORD index_[6];

	//シェーダーハンドル
	//マスク描画
	int psTex_;
	int psTexConstBuf_;


	//描画用の四角頂点の作成
	void MakeSquereVertex(Vector2 pos);



};

