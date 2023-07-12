#pragma once
#include<vector>
#include "../Common/Vector2.h"
#include "SceneBase.h"

//class Vector2;
class RectButton;

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
		Title	  = 4,
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


private:

	//バトル相手情報
	//std::array<int, 3> enemys_;
	//デッキ情報


	//モードボックス画像
	Vector2 modePos_;
	std::string nowMode_;
	int modeBox_;
	int modeFontHandle_;


	//コメントボックス
	Vector2 cmtPos_;
	std::string devilCmt_;
	int cmtBox_;
	int cmtFontHandle_;

	//マスコット画像
	int devilImg_;
	Vector2 devilPos_;
	int shakeY_;

	//選択ボタン
	std::vector<RectButton*>buttons_;
	//ボタンUI画像
	int backBtnImg_;
	std::map<SELECT_MODE, int>btnImg_;


	//シェーダーハンドル
	//反転有りシェーダー
	int psTex_;




	//各ボタン処理
	void BtnProcess();

	//ボタンUI生成
	void CerateBtnUI(void);

	//各ボタン処理
	void BattleBtnProcess(void);
	void EditBtnProcess(void);
	void RuleBtnProcess(void);
	void CreditBtnProcess(void);
	void TitleBtnProcess(void);

	//モードボックス描画
	void DrawModeBox(void);
	//コメントボックス描画
	void DrawCmtBox(void);

	//デビルのコメントセット
	void SetDevilCmt(const std::string& cmt);

};

