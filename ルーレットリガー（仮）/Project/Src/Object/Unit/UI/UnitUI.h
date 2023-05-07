#pragma once
#include<string>
#include"../../../Common/Vector2.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Manager/SceneManager.h"
#include"../UnitBase.h"

class UnitUI
{
public:
	const int  HP_GAUGE_X = 20;
	const int  HP_GAUGE_Y = 120;


	UnitUI();
	virtual ~UnitUI();


	virtual void Init(void);
	virtual void Draw(void) = 0;
	void Release(void);


	//行動中のユニットの表示
	virtual void DrawActUnit(void) = 0;
	//ロックオン
	virtual void DrawRockOn(void) = 0;


private:

protected:
	////ユニット座標
	//Vector2 unitPos_;
	////ユニットネーム
	//std::string* name_;


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
	float nowHp_;

	//描画用の四角頂点のの作成
	void MakeSquereVertex(Vector2 pos);

	//HPのシェーダー描画
	void DrawHpShader(const float& ratio, const COLOR_F& color);

	//名前の描画
	void DrawName(const std::string& name,const Vector2& uPos);


};

