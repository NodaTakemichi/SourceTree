#pragma once
#include<string>
#include<vector>
#include"../../../Common/Vector2.h"
#include "../../../Utility/AsoUtility.h"
#include "../Status/Buff.h"
#include"../UnitBase.h"

class UnitUI
{
public:
	const int  HP_GAUGE_X = 20;
	const int  HP_GAUGE_Y = 120;


	UnitUI(Vector2 pos, std::string& name,
		int& hp, int& maxHp, int& beforHp);
	virtual ~UnitUI();


	virtual void Init(void);
	virtual void Draw(void);
	void Release(void);


	//行動中のユニットの表示
	virtual void DrawActUnit(void) = 0;
	//ロックオン
	virtual void DrawRockOn(void) = 0;
	//バフをセットする
	void SetBuff(std::vector<Buff*> buffs);


private:

protected:
	//ユニット座標
	Vector2 unitPos_;
	//ユニットネーム
	std::string& name_;
	//HP
	int& hp_;
	int& maxHp_;
	int& beforHp_;
	
	//ネームフレーム画像
	int nameFrameImg_;

	//HPシェーダー
	//頂点情報
	VERTEX2DSHADER mVertex[4];
	WORD mIndex[6];

	//シェーダーハンドル
	int psHpColor_;
	int psHpColorConstBuf_;

	//合計時間
	float totalTime_;
	//HP変化中
	int nowHp_;

	//描画用の四角頂点のの作成
	void MakeSquereVertex(Vector2 pos);

	//HPのシェーダー描画
	void DrawHpShader(const float& ratio, const COLOR_F& color);

	//HPの減少処理
	void DecHpGauge(void);

	//HP枠の描画
	void DrawHpFrame(const Vector2& pos);

	//名前の描画
	void DrawName(const std::string& name,const Vector2& uPos);
	
	//バフアイコンの描画
	void DrawBuffIcon();
	

	//画像アイコン（テスト）
	int icon_[9];
	//所有バフの取得
	std::vector<Buff*> buffs_;


};

