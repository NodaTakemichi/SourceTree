#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/DrawShader.h"
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
	titleImg_ = LoadGraph("./Data/Image/UI/title.png");
	backImg_ = LoadGraph("./Data/Image/bg/title_bg.jpg");

	//シェーダー登録

	//フォントハンドル
	fontHandle_ = CreateFontToHandle("", 20, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

	fontColor_ = GetColor(150, 150, 0);

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
	auto& draw = DrawShader::GetInstance();

	//背景描画
	DrawGraph(0, 0, backImg_, true);
	//モンスター描画

	//タイトル描画
	draw.DrawGraphToShader({ 0,0 }, titleImg_, psTitle_);
	//指示描画
	DrawStringToHandle(
		100, 600,
		"クリックでスタート！",
		0xffffff, fontColor_);

}

void TitleScene::Release(void)
{
	DeleteGraph(titleImg_);
	DeleteGraph(backImg_);

	monsters_.clear();

	DeleteFontToHandle(fontHandle_);

	DeleteShader(psTitle_);
	DeleteShader(psMon_);
}
