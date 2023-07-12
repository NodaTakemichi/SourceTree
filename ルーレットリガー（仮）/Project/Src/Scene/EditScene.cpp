#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/DeckManager.h"
#include "../Utility/AsoUtility.h"
#include "../Utility/Button/CircleButton.h"
#include "../Utility/Button/UnitButton.h"
#include "../Utility/Button/CmdButton.h"

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
	//画像の登録
	//背景
	bgImg_ = LoadGraph("Data/Image/bg/EditScene_bg.png");

	//ユニットカード裏
	unitBackImg_ = LoadGraph("Data/Image/UI/UnitBack.png");

	//ボタン画像
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");

	//バックボタンの生成
	int sy = Application::SCREEN_SIZE_Y;
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);



	//ユニット
	auto& deckMng = DeckManager::GetInstance();
	auto& dataMng = UnitDataManager::GetInstance();

	//デッキユニットの取得
	int noDeck = 0;
	for (auto& num : deckMng.GetDeck())
	{
		//ユニットデータ
		auto u = dataMng.GetUnitData(num);	
		//表示座標
		Vector2 cardPos = FIRST_UNIT_DECK_POS;
		cardPos.x += OFFSET_UNIT_DECK_POS * noDeck;

		//ボタン生成
		UnitButton* ub = new UnitButton();
		ub->Create(cardPos, unitBackImg_, u);
		deck_.emplace(std::make_pair(num, ub));

		noDeck++;
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
		ub->Create(cardPos, unitBackImg_, u);
		unitCards_.emplace(std::make_pair(num, ub));

		no++;
	}


	//ピックアップユニット
	pickUpUnit_ = -1;

	//ステータス画面
	sFontHandle_= CreateFontToHandle("游明朝", 20, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);
	//sFontHandle_= CreateFontToHandle("游明朝", 22, 20,
	//	DX_FONTTYPE_ANTIALIASING_4X4);
	sFontColor_ = GetColor(230, 230, 230);

	//アイコン画像
	hpIcon_ = LoadGraph("Data/Image/Icon/HP.png");
	attackIcon_ = LoadGraph("Data/Image/Icon/Attack.png");
	speedIcon_ = LoadGraph("Data/Image/Icon/Speed.png");
	
	//ページ
	page_ = 1;
}

void EditScene::Update(void)
{
	//バック処理
	if (backBtn_->ButtonDecision())
	{
		//デッキの確定
		DeckDecision();
		//シーン遷移
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	}

	//ボタン更新
	//バックボタン
	backBtn_->Update();
	//デッキ
	for (auto& deck : deck_)
	{
		deck.second->Update();
	}
	//ユニットカードプール
	for (auto& card : unitCards_)
	{
		card.second->Update();
	}


	//デッキ編集処理
	DeckEditProcess();
	//押したユニットカードをセット
	SelectPickUpUnit();

}

void EditScene::Draw(void)
{
	//背景
	DrawGraph(0, 0, bgImg_, true);


	//ボタンUI
	//マイデッキ
	for (auto& deck : deck_)
	{
		deck.second->Draw();
	}
	//ユニットプール
	for (auto& card : unitCards_)
	{
		card.second->Draw();
	}

	//ユニット情報
	DrawUnitStatus();


	//バックボタン
	backBtn_->Draw();

}

void EditScene::Release(void)
{
	//画像の解放
	DeleteGraph(bgImg_);
	DeleteGraph(unitBackImg_);
	DeleteGraph(backImg_);

	DeleteGraph(hpIcon_);
	DeleteGraph(attackIcon_);
	DeleteGraph(speedIcon_);

	DeleteFontToHandle(sFontHandle_);

	for (auto& du : deck_)
	{
		du.second->Release();
		delete du.second;
	}
	deck_.clear();

	for (auto& cu : unitCards_)
	{
		cu.second->Release();
		delete cu.second;
	}
	unitCards_.clear();


	backBtn_->Release();
	delete backBtn_;
}


void EditScene::DrawUnitStatus(void)
{
	if (pickUpUnit_ == -1)return;


	//文字列の（半分の）長さを取得
	auto l = AsoUtility::StringLength(pickUpUnitData_.name, sFontHandle_) / 2;
	//名前
	DrawStringToHandle(
		1080 - l , 80,
		pickUpUnitData_.name.c_str(), sFontColor_, sFontHandle_);

	//ユニット画像
	DrawGraph(950, 120, pickUpUnitData_.imgHandle, true);

	//ステータス
	int noX = 0;
	int noY = 0;
	int offsetX = 140;
	int offsetY = 50;

	auto drawIcon = [&](int icon,int value) {

		Vector2 iconPos = { 960 + (offsetX * noX), 390 + (offsetY * noY) };

		DrawGraph(iconPos.x, iconPos.y, icon, true);
		DrawFormatStringToHandle(iconPos.x + 40, iconPos.y+5,
			sFontColor_, sFontHandle_, "%d", value);

		noX++;
		if (noX >= 2)
		{
			noX = 0;
			noY++;
		}

		return;
	};

	drawIcon(hpIcon_, pickUpUnitData_.hp);
	drawIcon(attackIcon_, pickUpUnitData_.attack);
	drawIcon(speedIcon_, pickUpUnitData_.speed);


	//技一覧
	for (auto& cmdBtn : cmdBtns_)
	{
		cmdBtn->Draw();
	}
}

void EditScene::DeckEditProcess(void)
{
	if (pickUpUnit_ == -1)return;

	//ピックアップユニットをセットする
	for (auto& deck : deck_)
	{
		if (!deck.second->ButtonDecision())continue;

		//デッキに同じユニットが存在したら、スキップ
		auto u = deck_.find(pickUpUnit_);
		if (u != deck_.end())
		{
			return;
		}

		//古いキーの値を取得
		UnitButton* c = deck_[deck.first];
		//削除
		deck_.erase(deck.first);

		//ボタンのデータ更新
		c->ChengeUnitData(pickUpUnitData_);

		//新しいキーで要素を追加
		deck_[pickUpUnit_] = c;

		return;
	}
}

void EditScene::SelectPickUpUnit(void)
{
	if (pickUpUnit_ == -1)
	{
		for (auto& card : unitCards_)
		{
			if (!card.second->ButtonDecision())continue;

			pickUpUnit_ = card.first;


			//各データの取得
			auto& dataMng = UnitDataManager::GetInstance();
			pickUpUnitData_ = dataMng.GetUnitData(pickUpUnit_);
			//コマンドボタンの生成
			int noX, noY;
			noX = noY = 0;
			Vector2 size = { 163,40 };
			Vector2 posBase = { 915, 500 };
			for (auto& cmd : pickUpUnitData_.cmdNum)
			{
				CmdButton* b = new CmdButton();

				//座標決め
				Vector2 pos = { posBase.x + size.x * noX, posBase.y + size.y * noY };
				b->Create(pos, size, cmd);
				cmdBtns_.push_back(b);

				//座標ずらし
				noY++;
				if (noY >= 4)
				{
					noY = 0;
					noX++;
				}
			}
			return;
		}
	}

	for (auto& card : unitCards_)
	{
		if (!card.second->ButtonDecision())continue;
		
		pickUpUnit_ = card.first;


		//各データの取得
		auto& dataMng = UnitDataManager::GetInstance();
		pickUpUnitData_ = dataMng.GetUnitData(pickUpUnit_);
		//コマンドのセット
		int n = 0;
		for (auto& cmd : pickUpUnitData_.cmdNum)
		{
			cmdBtns_[n]->SetCmd(cmd);
			n++;
		}


		return;
	}
}

void EditScene::DeckDecision(void)
{
	auto& dMng = DeckManager::GetInstance();
	std::vector<int>  num;
	for (auto& deck : deck_)
	{
		num.push_back(deck.first);
	}
	dMng.SetDeck({ num[0],num[1],num[2] });
}
