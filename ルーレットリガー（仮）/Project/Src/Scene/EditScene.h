#pragma once
#include<vector>
#include<array>
#include "SceneBase.h"
class CircleButton;

class EditScene :
    public SceneBase
{
public:

	// コンストラクタ
	EditScene(void);

	// デストラクタ
	~EditScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:


	//編集枠画像
	int editFrameImg_;

	//マイデッキ
	std::array<int,3> deck_;

	//所持ユニット番号
	std::vector<int>units_;

	//バックボタン
	CircleButton* backBtn_;
	//ボタン画像
	int backImg_;


	//シェーダー
	int psMon_;

	//フォントハンドル
	int fontHandle_;
	int fontColor_;

};

