#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/DrawShader.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"

#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	//画像の登録
	titleImg_ = LoadGraph("Data/Image/UI/タイトル.png");
	titleImgNor_ = LoadGraph("Data/Image/UI/タイトル_n.png");
	titleBackImg_ = LoadGraph("Data/Image/UI/タイトルバック.png");
	bgImg_ = LoadGraph("Data/Image/bg/title_bg.jpg");


	unitsImg_.push_back(LoadGraph("Data/Image/UI/Units_3.png"));
	unitsImg_.push_back(LoadGraph("Data/Image/UI/Units_2.png"));
	unitsImg_.push_back(LoadGraph("Data/Image/UI/Units_1.png"));

	//シェーダー登録
	psIumi_ = LoadPixelShader("");
	psTitle_ = LoadPixelShader("./x64/Debug/NormalMap.cso");

	//フォントハンドル
	fontHandle_ = CreateFontToHandle("HGS創英角ｺﾞｼｯｸUB", 40, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

	fontColor_ = GetColor(230, 230, 250);
}

void TitleScene::Update(void)
{
	//シーン遷移
	auto& ins = InputManager::GetInstance();
	if (ins.IsClickMouseLeft())
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	}

	//デルタタイム
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;


}

void TitleScene::Draw(void)
{
	auto& ds = DrawShader::GetInstance();
	auto cx = Application::SCREEN_SIZE_X;
	auto cy = Application::SCREEN_SIZE_Y;

	//背景描画
	DrawGraph(0, 0, bgImg_, true);
	//モンスター描画
	for (auto& unitImg : unitsImg_)
	{
		DrawGraph(0, 0, unitImg, true);
	}

	//タイトルロゴ描画
	int posY = 60;
	DrawGraph(0, posY,titleBackImg_, true);

	COLOR_F buf = COLOR_F{
		totalTime_
	};
	ds.GetInstance().DrawGraphAndSubToShader(
		{ 0,posY }, titleImg_, titleImgNor_, psTitle_, buf);
	

	//指示描画
	std::string s = "クリックでスタート！";
	auto len = AsoUtility::StringLength(s, fontHandle_) / 2;
	DrawStringToHandle(
		cx / 2 - len, 600,
		"クリックでスタート！",
		fontColor_, fontHandle_);

#ifdef DEBUG
	auto span = 20;
	for (size_t i = 0; i < 100; i++)
	{
		//X
		DrawLine(0, i * span, cx, i * span, 0xff0000);

		//Y
		DrawLine(i * span, 0, i * span, cy, 0x0000ff);
	}
#endif // _DEBUG
}

void TitleScene::Release(void)
{
	DeleteGraph(titleImg_);
	DeleteGraph(titleImgNor_);
	DeleteGraph(titleBackImg_);
	DeleteGraph(bgImg_);
	for (auto& img : unitsImg_)
	{
		DeleteGraph(img);
	}
	unitsImg_.clear();

	DeleteFontToHandle(fontHandle_);

	DeleteShader(psTitle_);
	DeleteShader(psIumi_);
}
