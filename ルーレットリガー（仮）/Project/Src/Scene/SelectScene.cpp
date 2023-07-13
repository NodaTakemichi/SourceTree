#include <DxLib.h>
#include <cstdlib>
#include "../Application.h"
#include "../Manager/DataManager/UnitDataManager.h"
#include "../Manager/DataManager/BattleDataManager.h"
#include "../Manager/DeckManager.h"
#include "../Manager/DataManager/SoundManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Common/Vector2.h"

#include "../Utility/AsoUtility.h"
#include "../Utility/DrawShader.h"
#include "../Utility/Button/RectButton.h"
#include "../Utility/Button/CircleButton.h"


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
	//ボタン画像
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");
	//バックボタンの生成
	int sy = Application::SCREEN_SIZE_Y + 20;
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);

	//決定ボタン画像
	deciBtnImg_ = LoadGraph("Data/Image/UI/Select/DeciBtnBack.png");
	//決定ボタンの生成
	deciBtn_ = new RectButton();
	deciBtn_->Create({ 820,610 },{ 120,80 }, deciBtnImg_, -1);


	//初期化
	totalTime_ = 0.0f;

	//画像の登録
	bgImg_ = LoadGraph("Data/Image/bg/select.jpg");

	modeBox_ = LoadGraph("Data/Image/UI/ModeBox.png");
	cmtBox_ = LoadGraph("Data/Image/UI/CommentBox.png");

	enemysBackImg_ = LoadGraph("Data/Image/UI/Select/EnemysBack.png");


	//モードボックス
	modePos_ = { 0,0 };
	nowMode_ = "MODE SELECT";
	modeFontHandle_ = CreateFontToHandle("游明朝", 50, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);

	//コメントボックス
	cmtPos_ = { 0, 470 };
	SetDevilCmt("モードを選択してくれよな！");
	cmtFontHandle_ = CreateFontToHandle("游明朝", 20, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);


	//つかいま
	devilImg_ = LoadGraph("Data/Image/UI/つかいま_口開き.png");
	devilPos_ = { 0,100 };
	shakeY_ = 0;

	//シェーダー登録
	//反転有り描画
	psTex_ = LoadPixelShader("x64/Debug/ReverseTexture.cso");

	//ボタンUI生成
	CreateModeBtn();

	//モード
	ChangeSelectMode(SELECT_MODE::MAX);

	//バトル相手情報の登録
	BattleEnemyInit();

	//ホイール初期化
	GetMouseWheelRotVol();
	enemysNum_ = 0;

	page = 1;

}

void SelectScene::Update(void)
{

	//デルタタイム
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//つかいま座標
	shakeY_ = sinf(totalTime_) * 30.0f;

	if (page == 1)
	{

		//各モードボタン更新
		BtnProcess();
	}
	else
	{

		//対戦相手選択
		SelectEnemy();

		//バックボタン
		backBtn_->Update();
		if (backBtn_->ButtonDecision())
		{
			//前フェーズに戻る
			page--;
		}

		//決定ボタン
		deciBtn_->Update();
		if (deciBtn_->ButtonDecision())
		{
			//デッキのセット
			auto deck = DeckManager::GetInstance().GetDeck();
			std::array<int, 3> enemys =enemys_[enemysNum_];
			BattleDataManager::GetInstance().SetBattleData({
				deck,enemys,0,0 });


			//シーン遷移
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);

		}

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
		{ devilPos_.x ,devilPos_.y + shakeY_ }, devilImg_, psTex_
	);

	//モードボックス描画
	DrawModeBox();

	//コメントボックス
	DrawCmtBox();


	if (page == 1)
	{
		//モードボタン
		for (auto& btn : modeBtn_)
		{
			btn.second.btn->Draw();
		}

		//セレクトモード画像
		if (mode_ != SELECT_MODE::MAX)DrawGraph(700, 300, modeBtn_.at(mode_).modeImg, true);

	}
	else
	{

		//バックボタン
		backBtn_->Draw();

		//
		DrawGraph(580, 80, enemysBackImg_, true);

		//バトルエネミー
		auto& uMng = UnitDataManager::GetInstance();

		//決定ボタン
		deciBtn_->Draw();
		 

		auto drawEu = [&](int num,int posX,int posY) {
			int i = enemys_[enemysNum_][num];
			if (i == -1)return;
			int uImg = uMng.GetUnitImg(i);
			DrawGraph(posX, posY, uImg, true);
		};

		drawEu(1, 600, 250);
		drawEu(0, 800, 150);
		drawEu(2, 1000, 250);

	}

#ifdef DEBUG
	auto span = 50;
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
	DeleteGraph(modeBackBtnImg_);
	DeleteGraph(enemysBackImg_);

	backBtn_->Release();
	delete backBtn_;
}

void SelectScene::DrawModeBox(void)
{
	DrawGraph(modePos_.x, modePos_.y, modeBox_, true);
	int x, y;
	GetGraphSize(modeBox_, &x, &y);

	auto len = AsoUtility::StringLength(nowMode_, modeFontHandle_) / 2;
	DrawFormatStringToHandle(
		modePos_.x + (x / 2) - len,
		modePos_.y + 60,
		0xdddddd, modeFontHandle_, nowMode_.c_str());
}

void SelectScene::DrawCmtBox(void)
{
	DrawGraph(cmtPos_.x, cmtPos_.y, cmtBox_, true);

	Vector2 offset = { cmtPos_.x + 40,cmtPos_.y + 40 };
	DrawFormatStringToHandle(
		offset.x, offset.y,
		0xdddddd, cmtFontHandle_, devilCmt_.c_str());

}

void SelectScene::BtnProcess()
{

	//ボタン更新
	for (auto& btn : modeBtn_)
	{
		btn.second.btn->Update();
	}

	//ボタン：マウスがボタン上にあるか判断
	for (auto& btn : modeBtn_)
	{
		if (btn.second.btn->MouseOnButton())
		{
			ChangeSelectMode(btn.first);
		}
	}

	//ボタン：クリック判定
	for (auto& btn : modeBtn_)
	{
		if (!btn.second.btn->ButtonDecision())continue;

		//ボタンが押された場合、そのボタン処理を行う
		SelectBtnProcess();
	}
}

void SelectScene::BattleBtnProcess(void)
{
	SetDevilCmt("ホイールで相手を選べるぜ！");


	page++;

	////デッキのセット
	//auto deck = DeckManager::GetInstance().GetDeck();
	//std::array<int, 3> enemys =enemys_[enemysNum_];
	//BattleDataManager::GetInstance().SetBattleData({
	//	deck,enemys,0,0 });


	////シーン遷移
	//SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
}

void SelectScene::EditBtnProcess(void)
{
	//シーン遷移
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::DECK_EDIT, true);
}

void SelectScene::RuleBtnProcess(void)
{
}

void SelectScene::CreditBtnProcess(void)
{
}

void SelectScene::TitleBtnProcess(void)
{
	//シーン遷移
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);
}

void SelectScene::CreateModeBtn(void)
{
	//スクリーンサイズ
	auto& sx = Application::SCREEN_SIZE_X;
	auto& sy = Application::SCREEN_SIZE_Y;

	//モードボタンの背面画像
	modeBackBtnImg_ = LoadGraph("./Data/Image/UI/ModeBtnImg.png");
	int btnSizeX, btnSizeY;
	GetGraphSize(modeBackBtnImg_, &btnSizeX, &btnSizeY);


	std::string path = "Data/Image/UI/";
	int n = 0;
	// ボタン生成ラムダ
	auto createBtn = [&](SELECT_MODE mode, std::string btnImgPath, std::string modeImgPath) {

		//モード画像
		std::string fileName = path + modeImgPath;
		int modeImg = LoadGraph(fileName.c_str());

		//座標
		Vector2 pos = {
			(sx / 2) - (btnSizeX * 2) - (btnSizeX / 2) + (btnSizeX * n)  ,
			sy - btnSizeY };
		//ボタン画像
		fileName = path + btnImgPath;
		int btnImg = LoadGraph(fileName.c_str());

		//ボタン生成
		RectButton* b = new RectButton();
		b->Create(pos, { 0,0 }, modeBackBtnImg_, btnImg);

		//挿入
		ModeData md = { modeImg,b };
		modeBtn_.emplace(std::make_pair(mode, md));

		n++;
	};


	createBtn(SELECT_MODE::BATTLE,		"バトル.png",		"Select/Mode_Battle.png");
	createBtn(SELECT_MODE::DECK_EDIT,	"デッキ編集.png",	"Select/Mode_DeckEdit.png");
	createBtn(SELECT_MODE::RULE_BOOK,	"ルールブック.png", "");
	createBtn(SELECT_MODE::CREDIT,		"クレジット.png",	"");
	createBtn(SELECT_MODE::TITLE,		"退出.png",			"Select/Mode_Title.png");
}

void SelectScene::SelectBtnProcess(void)
{
	switch (mode_)
	{
	case SelectScene::SELECT_MODE::BATTLE:
		BattleBtnProcess();
		break;
	case SelectScene::SELECT_MODE::DECK_EDIT:
		EditBtnProcess();
		break;
	case SelectScene::SELECT_MODE::RULE_BOOK:
		RuleBtnProcess();
		break;
	case SelectScene::SELECT_MODE::CREDIT:
		CreditBtnProcess();
		break;
	case SelectScene::SELECT_MODE::TITLE:
		TitleBtnProcess();
		break;
	case SelectScene::SELECT_MODE::MAX:
		break;
	default:
		break;
	}
}

void SelectScene::ChangeSelectMode(const SELECT_MODE& mode)
{
	//同じだった場合、何もしない
	if (mode_ == mode)return;

	mode_ = mode;

	//音声を鳴らす

	switch (mode_)
	{
	case SelectScene::SELECT_MODE::BATTLE:
		SetDevilCmt("モンスター同士を戦わせるモードだぞ\n勝てる相手を選ぶんだぜ");

		break;
	case SelectScene::SELECT_MODE::DECK_EDIT:
		SetDevilCmt("戦わせるユニットを選べるぜ");

		break;
	case SelectScene::SELECT_MODE::RULE_BOOK:
		SetDevilCmt("現在、開発中です");

		break;
	case SelectScene::SELECT_MODE::CREDIT:
		SetDevilCmt("現在、開発中です");

		break;
	case SelectScene::SELECT_MODE::TITLE:
		SetDevilCmt("タイトルに戻るぜ");

		break;
	case SelectScene::SELECT_MODE::MAX:
		break;
	default:
		break;
	}
}

void SelectScene::SetDevilCmt(const std::string& cmt)
{
	devilCmt_ = cmt;
}

void SelectScene::BattleEnemyInit(void)
{
	//エネミーの登録
	//auto regEnemys = [&](SELECT_STAGE stage, std::array<int, 3> nums) {
	//	enemys_.emplace(std::make_pair(stage, nums));
	//};

	enemys_.push_back({ 0,1,2 });
	enemys_.push_back({ 3,4,5 });
	enemys_.push_back({ 6,7,8 });
	enemys_.push_back({ 9,-1,-1 });

	enemys_.push_back({ 10,11,12 });
	enemys_.push_back({ 13,14,15 });
	enemys_.push_back({ 16,17,18 });
	enemys_.push_back({ 19,-1,-1 });
}

void SelectScene::SelectEnemy(void)
{
	enemysNum_ -= GetMouseWheelRotVol();
	enemysNum_ = AsoUtility::Wrap(enemysNum_, 0, enemys_.size());
	//_dbgDrawFormatString(0, 0, 0xffffff, "NUM:%d", enemysNum_);

	enemys_[enemysNum_];
}


