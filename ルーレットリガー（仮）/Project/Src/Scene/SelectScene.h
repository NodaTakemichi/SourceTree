#pragma once
#include<vector>
#include "../Common/Vector2.h"
#include "SceneBase.h"

//class Vector2;
class ButtonUI;

class SelectScene :
    public SceneBase
{
public:

	enum class SELECT_MODE
	{
		BATTLE	  = 0,
		DECK_EDIT = 1,
		RULE_BOOK = 2,
		CREDIT	  = 3,
		EXIT	  = 4,
		MAX		  = 5
	};

	// コンストラクタ
	SelectScene(void);

	// デストラクタ
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	//各ボタン処理
	void BtnProcess();

	//ボタンUI生成
	void CerateBtnUI(void);

	//各ボタン処理
	void BattleBtnProcess(void);
	void EditBtnProcess(void);
	void RuleBtnProcess(void);
	void CreditBtnProcess(void);
	void ExitBtnProcess(void);

private:

	//敵情報配列

	//デッキ情報



	//選択ボタン
	std::vector<ButtonUI*>buttons_;
	//ボタンUI画像
	int backBtnImg_;
	std::map<SELECT_MODE, int>btnImg_;


	//つかいま画像
	int devilImg_;
	Vector2 devilPos_;
	int shakeY_;


	//シェーダー
	int psTex_;
};

