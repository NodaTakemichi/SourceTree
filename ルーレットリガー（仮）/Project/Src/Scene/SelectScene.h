#pragma once
#include<vector>
#include<array>
#include "../Common/Vector2.h"
#include "SceneBase.h"

//class Vector2;
class RectButton;
class CircleButton;

struct ModeData {
	int modeImg;		//モード選択画像
	RectButton* btn;	//モードボタン
};

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
		TITLE	  = 4,
		MAX		  
	};


	enum class SELECT_STAGE
	{
		FOREST,
		SEE,
		MAX
	};

	enum class SELECT_ENEMYS
	{
		EASY,
		NORMAL,
		HARD,
		LUNATIC,
		MAX
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
	//バックボタン
	//BackButton* backBtn_;
	CircleButton* backBtn_;
	//ボタン画像
	int backImg_;

	//決定ボタン
	RectButton* deciBtn_;
	//ボタン画像
	int deciBtnImg_;

	//選択画面の進行
	int page;

	//バトル相手情報
	//std::map < SELECT_STAGE, std::vector<std::array<int, 3>>>enemys_;
	std::vector<std::array<int, 3>>enemys_;
	//現enemys番号
	int enemysNum_;
	
	//エネミーズ背景
	int enemysBackImg_;


	//現在モード
	SELECT_MODE mode_;
	//モードボタン
	std::map<SELECT_MODE, ModeData>modeBtn_;
	//モードボタン画像
	int modeBackBtnImg_;



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

	//シェーダーハンドル
	//反転有りシェーダー
	int psTex_;


	//モードボックス描画
	void DrawModeBox(void);
	//コメントボックス描画
	void DrawCmtBox(void);


	//ボタン処理
	void BtnProcess();
	//各ボタン処理
	void BattleBtnProcess(void);
	void EditBtnProcess(void);
	void RuleBtnProcess(void);
	void CreditBtnProcess(void);
	void TitleBtnProcess(void);

	//モードボタン生成
	void CreateModeBtn(void);

	//モードの変更
	void ChangeSelectMode(const SELECT_MODE& mode);

	//クリックしたボタンの処理
	void SelectBtnProcess(void);

	//マスコットのコメントセット
	void SetDevilCmt(const std::string& cmt);

	//バトル相手情報の登録
	void BattleEnemyInit(void);

	//エネミーの選択
	void SelectEnemy(void);


};

