#pragma once
#include<vector>
#include<array>
#include<map>
#include "SceneBase.h"
#include "../Manager/DataManager/UnitDataManager.h"

class CircleButton;
class UnitButton;
class CmdButton;

class EditScene :
    public SceneBase
{
public:
	const Vector2 FIRST_UNIT_POOL_POS = { 106, 291 };
	const Vector2 OFFSET_UNIT_POOL_POS = { 151, 207 };

	const Vector2 FIRST_UNIT_DECK_POS = { 336, 47 };
	const int OFFSET_UNIT_DECK_POS = 148;


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
	std::map<int, UnitButton*> deck_;

	//所持ユニットカード
	std::map<int, UnitButton*> unitCards_;



	//バックボタン
	CircleButton* backBtn_;
	//ボタン画像
	int backImg_;


	//ピックアップユニット
	int pickUpUnit_;
	//ステータスフォントハンドル
	int sFontHandle_;
	int sFontColor_;

	//ピックアップユニットデータ
	UnitData pickUpUnitData_;

	//HP、攻撃力、スピードアイコン
	int hpIcon_;
	int attackIcon_;
	int speedIcon_;

	//コマンドボタン
	std::vector<CmdButton*> cmdBtns_;

	//ページ数
	int page_;




	//ユニットカードの背面画像
	int unitBack_;

	//カードステータスの描画
	void DrawUnitStatus(void);

	//デッキ編集
	void DeckEditProcess(void);

	//ピックアップユニットの選択
	void SelectPickUpUnit(void);

	//デッキの確定
	void DeckDecision(void);

};

