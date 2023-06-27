#pragma once
#include <vector>
#include "SceneBase.h"
class TitleScene :
    public SceneBase
{
public:

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:


	//タイトル画像
	int titleImg_;
	//背景画像
	int backImg_;

	//モンスター画像
	std::vector<int> monsters_;

	//モンスター画像表示シェーダー
	int psMon_;
	//タイトル画像シェーダー
	int psTitle_;

	//フォントハンドル
	int fontHandle_;
	int fontColor_;
};

