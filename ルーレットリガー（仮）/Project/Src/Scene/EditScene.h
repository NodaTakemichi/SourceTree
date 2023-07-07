#pragma once
#include<vector>
#include<array>
#include<map>
#include "SceneBase.h"

class CircleButton;
class UnitButton;
class UnitData;

class EditScene :
    public SceneBase
{
public:
	const Vector2 FIRST_UNIT_POOL_POS = { 106, 291 };
	const Vector2 OFFSET_UNIT_POOL_POS = { 151, 207 };


	// コンストラクタ
	EditScene(void);

	// デストラクタ
	~EditScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:
	//マイデッキ
	std::vector<UnitData> deck_;

	//所持ユニットカード
	std::map<int, UnitButton*> unitCards_;



	//バックボタン
	CircleButton* backBtn_;
	//ボタン画像
	int backImg_;



	//ステータスフォントハンドル
	int sFontHandle_;
	int sFontColor_;
	//ピックアップユニット
	int pickUpUnit_;


	//ユニットカードの背面画像
	int unitBack_;

	//カードステータスの描画
	void DrawUnitStatus(void);

	//ピックアップユニットの選択
	void SelectPickUpUnit(void);

};

