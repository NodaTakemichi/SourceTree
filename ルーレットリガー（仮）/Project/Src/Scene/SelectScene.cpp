#include <DxLib.h>
#include <cstdlib>
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

	//デルタタイム
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//つかいま座標
	shakeY_ = sinf(totalTime_) * 20.0f;

	//各ボタン更新
	BtnProcess();




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

	//ボタン
	for (auto& btn : buttons_)
	{
		btn->Draw();
	}



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

void SelectScene::BtnProcess()
{
	for (auto& btn : buttons_)
	{
		btn->Update();
	}

	//ボタンの上にマウスが乗っているか確認
	for (auto& btn : buttons_)
	{
	}


	//ボタンクリック処理
	for (auto& btn : buttons_)
	{
		btn->PushButton();
	}


	//ボタン決定処理
	if (buttons_[0]->ButtonDecision())
	{
		BattleBtnProcess();
	}
	if (buttons_[4]->ButtonDecision())
	{
		ExitBtnProcess();
	}

}

void SelectScene::CerateBtnUI(void)
{
	//スクリーンサイズ
	auto& sx = Application::SCREEN_SIZE_X;
	auto& sy = Application::SCREEN_SIZE_Y;

	//背面画像
	backBtnImg_ = LoadGraph("./Data/Image/UI/BackBtnImg.png");
	int x, y;
	GetGraphSize(backBtnImg_, &x, &y);

	//手前画像
	std::vector<int> handle;
	handle.push_back(LoadGraph("./Data/Image/UI/バトル.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/デッキ編集.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/ルールブック.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/クレジット.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/退出.png"));

	//作成
	int cout = 5;
	for (int i = 0; i < cout; i++)
	{
		ButtonUI* b = new ButtonUI();

		int r = i % 2;
		//座標
		Vector2 pos = {
			(sx / 2) - (x * 2) - (x / 2) + (x * i)  ,
			sy - y };

		b->Create(pos, { 0,0 }, backBtnImg_, handle[i]);
		buttons_.emplace_back(b);
	}


}

void SelectScene::BattleBtnProcess(void)
{
	//シーン遷移
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
}

void SelectScene::EditBtnProcess(void)
{
}

void SelectScene::RuleBtnProcess(void)
{
}

void SelectScene::CreditBtnProcess(void)
{
}

void SelectScene::ExitBtnProcess(void)
{
	exit(0);
}
