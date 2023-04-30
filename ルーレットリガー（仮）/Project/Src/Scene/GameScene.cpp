#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"

#include "../System/BattleSystem.h"

#include "../Object/Unit/UnitManager.h"
#include "../Object/Roulette.h"
#include "../Object/GameUI.h"
#include "../Object/Unit/Command.h"

#include "../_debug/_DebugConOut.h"
#include "../_debug/_DebugDispOut.h"

#include "GameScene.h"

GameScene::GameScene(void)
{

}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	//ユニットマネージャー
	unitMng_ = new UnitManager();
	unitMng_->Init();

	//ルーレット
	roulette_ = new Roulette();
	roulette_->Init();

	//UI
	GameUi_ = new GameUI();
	GameUi_->Init();

	//バトルシステム
	battleSys_ = new BattleSystem();
	battleSys_->Init();


	//画像の登録
	bgImg_ = LoadGraph("./Data/Image/bg/blue_bg.png");
	//フレーム
	frameImg_ = LoadGraph("./Data/Image/UI/Frame.png");

	//フェーズの変更
	ChangeGamePhase(GAME_PHASE::RULLET_TIME);

} 

void GameScene::Update(void)
{


	//デルタタイム
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	mTotalTime += delta;

	//入力
	auto& ins = InputManager::GetInstance();
	// シーン遷移
#ifdef _DEBUG
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}
#endif // _DEBUG

	//更新
	unitMng_->Update();
	roulette_->Update();
	GameUi_->Update();

	//フェーズ別更新
	switch (phase_)
	{
	case GameScene::GAME_PHASE::BATTLE_START:
		break;
	case GameScene::GAME_PHASE::RULLET_TIME:
		UpdateRouTime();
		break;
	case GameScene::GAME_PHASE::AIM:
		UpdateAIM();
		break;
	case GameScene::GAME_PHASE::BATTLE:
		UpdateBattle();
		break;
	case GameScene::GAME_PHASE::TURN_END:
		UpdateTurnEnd();
		break;
	default:
		break;
	}
}

void GameScene::Draw(void)
{
	//背景
	//DrawGraph(0, 0, bgImg_, true);
	//フレーム
	DrawGraph(0, 0, frameImg_, true);

	//オブジェクト
	unitMng_->Draw();
	roulette_->Draw();

	//UI関連
	GameUi_->Draw();

	//フェーズ別描画
	switch (phase_)
	{
	case GameScene::GAME_PHASE::RULLET_TIME:
		break;
	case GameScene::GAME_PHASE::AIM:
		GameUi_->DrawActivSkill();
		break;
	case GameScene::GAME_PHASE::BATTLE:
		break;
	case GameScene::GAME_PHASE::TURN_END:
		break;
}


#ifdef DEBUG
	auto cx = Application::SCREEN_SIZE_X;
	auto cy = Application::SCREEN_SIZE_Y;

	auto span = 20;
	for (size_t i = 0; i < 60; i++)
	{
		//X
		DrawLine(0, i * span, cx, i * span, 0xff0000);

		//Y
		DrawLine(i * span,0, i * span, cy, 0x0000ff);
	}

#endif // _DEBUG

}

void GameScene::Release(void)
{
	//破棄
	unitMng_->Release();
	delete unitMng_;
	roulette_->Release();
	delete roulette_;
	GameUi_->Release();
	delete GameUi_;

	//画像解放
	DeleteGraph(bgImg_);
	DeleteGraph(frameImg_);

}

void GameScene::UpdateRouTime(void)
{
	//ルーレットが停止したら、フェーズ移動
	if (roulette_->GetRouStop())
	{

		//決定したコマンドをゲームUIに受け渡す
		std::string cmd = roulette_->GetCmd()->GetName();
		GameUi_->SetCmdName(cmd);

		//バトルデータに情報を渡す
		battleSys_->SetBattleData(unitMng_->GetActivUnit(), 
			roulette_->GetCmd(), unitMng_->GetUnits());

		ChangeGamePhase(GAME_PHASE::AIM);
	}
}

void GameScene::UpdateAIM(void)
{	

	//対象を選択したら、バトルフェーズに進む
	if (battleSys_->SelectUnit())
	{
		ChangeGamePhase(GAME_PHASE::BATTLE);
	}
}

void GameScene::UpdateBattle(void)
{
	//バトルが終了したら、ターン終了に進む
	if (true)ChangeGamePhase(GAME_PHASE::TURN_END);

}

void GameScene::UpdateTurnEnd(void)
{
	//ターン終了時に場面整理を行い、ルーレットフェーズに進む
	if (true)ChangeGamePhase(GAME_PHASE::RULLET_TIME);
}

void GameScene::ChangeGamePhase(GAME_PHASE phase)
{

	phase_ = phase;

	switch (phase_)
	{
	case GameScene::GAME_PHASE::BATTLE_START:
		break;
	case GameScene::GAME_PHASE::RULLET_TIME:

		//ルーレットにコマンド技をセット
		roulette_->SetCommand(unitMng_->GetCommand());
		//ルーレット状況のリセット
		roulette_->ResetRouSpin();

		break;
	case GameScene::GAME_PHASE::AIM:
		//コマンドの選択対象を判断する
		battleSys_->CheckSelectTarget();

		//ホイールの初期化
		GetMouseWheelRotVol();

		break;
	case GameScene::GAME_PHASE::BATTLE:
		break;
	case GameScene::GAME_PHASE::TURN_END:
		//行動ユニットの整理
		unitMng_->ChangeActivUnit();
		break;
	default:
		break;
	}
}

