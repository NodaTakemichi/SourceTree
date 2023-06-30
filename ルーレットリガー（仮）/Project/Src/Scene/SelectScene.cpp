#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/InputManager.h"
#include "../Common/Vector2.h"
#include "../Utility/DrawShader.h"
#include "../Utility/ButtonUI.h"

#include"../_debug/_DebugDispOut.h"

#include "SelectScene.h"

SelectScene::SelectScene(void)
{
}

SelectScene::~SelectScene(void)
{
}

void SelectScene::Init(void)
{
	//初期化
	totalTime_ = 0.0f;

	//画像の登録
	bgImg_ = LoadGraph("./Data/Image/bg/select.jpg");

	//シェーダー登録
	psTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");

	//フォントハンドル
	//fontHandle_ = CreateFontToHandle("", 20, -1,
	//	DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);
	//fontColor_ = GetColor(150, 150, 0);

	//つかいま
	devilImg_ = LoadGraph("./Data/Image/UI/つかいま_口開き.png");
	devilPos_ = { 0,100 };
	shakeY_ = 0;

	//ボタンUI生成
	CerateBtnUI();

}

void SelectScene::Update(void)
{
	//シーン遷移
	//auto& ins = InputManager::GetInstance();
	//if (ins.IsClickMouseLeft())
	//{
	//	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	//}

	//デルタタイム
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//つかいま座標
	shakeY_ = sinf(totalTime_) * 30.0f;

	for  (auto& btn:buttons_)
	{
		btn->Draw();
	}

}

void SelectScene::Draw(void)
{
	auto& sx = Application::SCREEN_SIZE_X;
	auto& sy = Application::SCREEN_SIZE_Y;
	auto& ds = DrawShader::GetInstance();

	//背景
	ds.DrawExtendGraphToShader(
		{ 0,0 }, { sx,sy }, bgImg_, psTex_, COLOR_F{}
	);

	//つかいま描画
	ds.DrawGraphToShader(
		{devilPos_.x ,devilPos_.y + shakeY_ }, devilImg_, psTex_
	);


#ifdef DEBUG
	auto span = 20;
	for (size_t i = 0; i < 60; i++)
	{
		//X
		DrawLine(0, i * span, sx, i * span, 0xff0000);

		//Y
		DrawLine(i * span, 0, i * span, sy, 0x0000ff);
	}
#endif // _DEBUG

}

void SelectScene::Release(void)
{
}

void SelectScene::CerateBtnUI(void)
{

	backBtnImg_ = LoadGraph("./Data/Image/UI/BackBtnImg.png");

	int handle = LoadGraph("");

	//作成
	ButtonUI* b = new ButtonUI();
	b->Create({ 500,500 }, { 0,0 }, backBtnImg_, -1);
	buttons_.emplace_back(b);

}
