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


	UnitUI(Vector2 pos, std::string& name,int& hp,int& nowHp, int& maxHp);
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


	//ダメージ表記
	void SetDmg(const bool& drawing, const int& dmg);

private:

protected:
	//ユニット座標
	Vector2 unitPos_;
	//ユニットネーム
	std::string& name_;
	//最大HP,減少中HP
	int& hp_;
	int& maxHp_;
	int& nowHp_;

	//ネームフレーム画像
	int nameFrameImg_;
	//ターゲット画像
	int targetImg_;


	//ダメージフレーム画像
	int dmgFrameImg_;
	//ダメージ描画
	bool dmgNumDrawing_;	//ダメージを true:表示 , false:非表示
	//ダメージ値
	int dmg_;

	//ダメージフォント
	int dmgFontHandle_;
	//回復フォント
	int healFontHandle_;
	//ユニットフォント
	int unitFontHandle_;

	//シェーダーハンドル
	//HPシェーダー
	int psHpColor_;
	//通常シェーダー
	int psTextrue_;
	//枠強調シェーダー
	int psIumiFrame_;

	//HPのシェーダー描画
	void DrawHpShader(const Vector2& pos ,const COLOR_F& color);

	//HP枠の描画
	void DrawHpFrame(const Vector2& pos);

	//名前の描画
	void DrawName(const std::string& name,const Vector2& uPos);
	
	//バフアイコンの描画
	void DrawBuffIcon();
	

	//画像アイコン（テスト）
	int icon_[10];
	//所有バフの取得
	std::vector<Buff*> buffs_;


};

