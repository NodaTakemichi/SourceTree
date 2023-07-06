#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Utility/Button/CircleButton.h"
#include "EditScene.h"

EditScene::EditScene(void)
{
}

EditScene::~EditScene(void)
{
}

void EditScene::Init(void)
{
	//画像の登録
	bgImg_ = LoadGraph("Data/Image/bg/EditScene_bg.png");
	//editFrameImg_ = LoadGraph("");

	//ボタン画像
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");
	int sy = Application::SCREEN_SIZE_Y;

	//バックボタンの生成
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);

}

void EditScene::Update(void)
{
	//バックボタン
	backBtn_->Update();

	if (backBtn_->ButtonDecision())
	{
		//シーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	}
}

void EditScene::Draw(void)
{
	//背景
	DrawGraph(0, 0, bgImg_, true);

	//編集フレーム
	DrawGraph(0, 0, editFrameImg_, true);

	//ボタンUI
	//マイデッキ

	//ユニットプール

	//ユニット情報

	//追加ボタン

	//バックボタン
	backBtn_->Draw();

}

void EditScene::Release(void)
{
	backBtn_->Release();
	delete backBtn_;
}
