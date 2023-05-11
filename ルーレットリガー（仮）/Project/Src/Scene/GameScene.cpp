#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"

#include "../System/BattleSystem.h"

#include "../Object/Unit/UnitManager.h"
#include "../Object/Unit/UnitBase.h"
#include "../Object/Roulette.h"
#include "../Object/GameUI.h"
#include "../Object/Unit/Status/Command.h"
#include "../Object/Unit/Status/Buff.h"

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
	case GameScene::GAME_PHASE::GAME_END:
		//決着：ゲームシーン終了

		break;
	default:
		break;
	}
}

void GameScene::Draw(void)
{
	//背景
	DrawGraph(0, 0, bgImg_, true);
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
	case GameScene::GAME_PHASE::GAME_END:
		//結果の表示
		_dbgDrawFormatString(0, 0, 0xffffff, "ゲーム終了");
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
	battleSys_->Release();
	delete battleSys_;

	//画像解放
	DeleteGraph(bgImg_);
	DeleteGraph(frameImg_);

}

void GameScene::UpdateRouTime(void)
{
	//ルーレットの更新
	roulette_->Update();

	//ルーレットの停止走査（ユニットによって自動か手動か決める）
	roulette_->StopRoulette(actUnitAoutm_);

	//バフ判断
	//行動ユニット
	auto actUnit = unitMng_->GetActivUnit();
	for(auto& buff : actUnit->GetBuffs())
	{
		if (!buff->IsAlive())continue;

		//麻痺状態の場合、ターンエンドする
		if(buff->CheckOwnBuff(Buff::BUFF_TYPE::PALALYSIS))
		{
			ChangeGamePhase(GAME_PHASE::TURN_END);
		}
	}


	//ルーレットが停止したら、フェーズ移動
	if (roulette_->GetRouStop())
	{
		ChangeGamePhase(GAME_PHASE::AIM);
	}
}

void GameScene::UpdateAIM(void)
{	
	//対象を選択したら、バトルフェーズに進む
	if (battleSys_->SelectUnit(actUnitAoutm_))
	{
		ChangeGamePhase(GAME_PHASE::BATTLE);
	}
}

void GameScene::UpdateBattle(void)
{
	//ダメージ処理
	battleSys_->CmdProcess();

	//バトルが終了したら、ターン終了に進む
	if (true)ChangeGamePhase(GAME_PHASE::TURN_END);
}

void GameScene::UpdateTurnEnd(void)
{
	//全滅か判断
	//全滅ならばゲーム終了、そうでないならばルーレットフェーズに進む。
	if (unitMng_->IsAnniUnit())ChangeGamePhase(GAME_PHASE::GAME_END);
	else ChangeGamePhase(GAME_PHASE::RULLET_TIME);
}

void GameScene::ChangeGamePhase(GAME_PHASE phase)
{
	//フェーズ
	phase_ = phase;

	switch (phase_)
	{
	case GameScene::GAME_PHASE::BATTLE_START: {
		break;
	}
	case GameScene::GAME_PHASE::RULLET_TIME:{
		//行動ユニット
		auto actUnit = unitMng_->GetActivUnit();
		//ルーレットの停止が手動か自動か判断
		actUnitAoutm_ = (actUnit->GetUnitType() == UnitBase::UNIT_TYPE::ENEMY);

		//ルーレットにコマンド技をセット
		roulette_->SetCommand(unitMng_->GetCommand());
		//ルーレット状況のリセット
		roulette_->ResetRouSpin();

		//選択ユニットのリセット
		battleSys_->ResetSelectUnits();

		break;
	}
	case GameScene::GAME_PHASE::AIM: {
		//決定したコマンドをゲームUIに受け渡す
		std::string cmd = roulette_->GetCmd()->GetName();
		GameUi_->SetCmdName(cmd);

		//バトルデータに各情報を渡す
		battleSys_->SetBattleData(unitMng_->GetActivUnit(),
			roulette_->GetCmd(), unitMng_->GetUnits());

		//ホイールのリセット
		GetMouseWheelRotVol();

		//コマンドの選択対象を判断する
		battleSys_->CheckSelectTarget();

		//操作が自動の場合、ユニットをランダムに決める
		if (actUnitAoutm_)battleSys_->SetRandUnit();

		break;
	}
	case GameScene::GAME_PHASE::BATTLE: {
		break;
	}
	case GameScene::GAME_PHASE::TURN_END: {
		//ターンエンド時のユニットの処理
		//行動ユニット
		auto actUnit = unitMng_->GetActivUnit();
		actUnit->TurnEndProcess();


		//行動ユニットの整理
		unitMng_->ChangeActivUnit();
		break;
	}
	case GameScene::GAME_PHASE::GAME_END: {
		break;
	}
	default:
		break;
	}
}

