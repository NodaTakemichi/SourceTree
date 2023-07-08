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
	unitBack_ = LoadGraph("Data/Image/UI/UnitBack.png");


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


	//押したユニットカードをセット
	SelectPickUpUnit();




	//座標
	if (CheckHitKey(KEY_INPUT_RIGHT))testPos.x++;
	if (CheckHitKey(KEY_INPUT_LEFT))testPos.x--;
	if (CheckHitKey(KEY_INPUT_DOWN))testPos.y++;
	if (CheckHitKey(KEY_INPUT_UP))testPos.y--;
	_dbgDrawFormatString(0, 0, 0xffffff, "座標：{%d,%d}", testPos.x, testPos.y);
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

#ifdef _DEBUG
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

	DrawBox(testPos.x, testPos.y, 
		testPos.x+40, testPos.y+40, 0xffffff, true);

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
			Vector2 size = { 160,40 };
			for (auto& cmd : pickUpUnitData_.cmdNum)
			{
				CmdButton* b = new CmdButton();

				//座標決め
				Vector2 pos = { testPos.x + size.x * noX, testPos.y + size.y * noY };
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
