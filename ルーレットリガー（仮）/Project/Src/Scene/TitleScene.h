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
	int titleImgNor_;
	//タイトルバック画像
	int titleBackImg_;

	//モンスター画像
	std::vector<int> unitsImg_;

	//モンスター画像表示シェーダー
	int psIumi_;
	//タイトル画像シェーダー
	int psTitle_;

	//フォントハンドル
	int fontHandle_;
	int fontColor_;

};

