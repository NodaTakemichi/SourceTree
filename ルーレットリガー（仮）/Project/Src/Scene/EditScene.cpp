#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/DeckManager.h"
#include "../Manager/DataManager/UnitDataManager.h"
#include "../Utility/Button/CircleButton.h"

#include "../Utility/Button/UnitButton.h"
#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"
#include "EditScene.h"

EditScene::EditScene(void)
{
}

EditScene::~EditScene(void)
{
}

void EditScene::Init(void)
{

	//ユニットカード裏
	unitBack_ = LoadGraph("Data/Image/UI/UnitBack.png");

	auto& deckMng = DeckManager::GetInstance();
	auto& dataMng = UnitDataManager::GetInstance();

	//デッキユニットの取得
	for (auto& num : deckMng.GetDeck())
	{
		auto u = dataMng.GetUnitData(num);
		deck_.emplace_back(u);
	}


	//所持ユニットの取得
	int no = 0;
	for (auto& num : deckMng.GetUnitPool())
	{
		//ユニットデータ
		auto u = dataMng.GetUnitData(num);	
		//表示座標
		Vector2 cardPos = FIRST_UNIT_POOL_POS;
		if (no < 5)
		{
			cardPos.x += OFFSET_UNIT_POOL_POS.x * no;
		}else
		{
			cardPos.x += OFFSET_UNIT_POOL_POS.x * (no - 5);
			cardPos.y += OFFSET_UNIT_POOL_POS.y;
		}
		//ボタン生成
		UnitButton* ub = new UnitButton();
		ub->Create(cardPos, unitBack_, u);
		unitCards_.emplace(std::make_pair(num, ub));

		no++;
	}

	//画像の登録
	bgImg_ = LoadGraph("Data/Image/bg/EditScene_bg.png");
	//editFrameImg_ = LoadGraph("");

	//ボタン画像
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");
	int sy = Application::SCREEN_SIZE_Y;

	//バックボタンの生成
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);

	//ピックアップユニット
	pickUpUnit_ = -1;

	
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

	//ボタン更新
	for (auto& card : unitCards_)
	{
		card.second->Update();
	}


	//押したカード番号をセット
	SelectPickUpUnit();



}

void EditScene::Draw(void)
{
	//背景
	DrawGraph(0, 0, bgImg_, true);


	//ボタンUI
	//マイデッキ


	//ユニットプール
	for (auto& card : unitCards_)
	{
		card.second->Draw();
	}

	//ユニット情報
	DrawUnitStatus();

	//追加ボタン

	//バックボタン
	backBtn_->Draw();

#ifdef DEBUG
	auto cx = Application::SCREEN_SIZE_X;
	auto cy = Application::SCREEN_SIZE_Y;
	auto span = 20;
	for (size_t i = 0; i < 60; i++)
	{
		//X
		DrawLine(0, i * span, cx, i * span, 0xff0000);

		//Y
		DrawLine(i * span, 0, i * span, cy, 0x0000ff);
	}
#endif // _DEBUG



}

void EditScene::Release(void)
{
	backBtn_->Release();
	delete backBtn_;
}

void EditScene::DrawUnitStatus(void)
{
	if (pickUpUnit_ == -1)return;

	//ユニット情報の取得
	auto& dataMng = UnitDataManager::GetInstance();
	auto& unit = dataMng.GetUnitData(pickUpUnit_);

	//名前
	DrawString(900, 100, unit.name.c_str(), 0xffffff);

	//ユニット画像
	DrawGraph(900, 250, unit.imgHandle, true);

	//ステータス
	DrawFormatString(900, 530, 0xffffff,"HP:%d",unit.hp);
	DrawFormatString(900, 546, 0xffffff,"P :%d",unit.attack);
	DrawFormatString(900, 562, 0xffffff,"D :%d",unit.speed);

	//技一覧

}

void EditScene::SelectPickUpUnit(void)
{
	for (auto& card : unitCards_)
	{
		if (!card.second->ButtonDecision())continue;
		
		pickUpUnit_ = card.first;
	}
}
