#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/DataManager/EffectManager.h"
#include "../Manager/DataManager/SoundManager.h"
#include "../Manager/DataManager/BattleDataManager.h"

#include "../Utility/AsoUtility.h"
#include "../Utility/DrawShader.h"
#include "../Battle/BattleSystem.h"
#include "../Battle/DeathStaging.h"

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

	// 死亡演出初期化
	DeathStaging::CreateInstance();

	//ルーレット
	roulette_ = new Roulette();
	roulette_->Init();

	//UI
	GameUi_ = new GameUI();
	GameUi_->Init();

	//バトルシステム
	battleSys_ = new BattleSystem();
	battleSys_->Init();

	//ユニットマネージャー
	unitMng_ = new UnitManager();
	unitMng_->Init();
	//ユニットの生成
	auto& bd = BattleDataManager::GetInstance().GetBattleData();
	unitMng_->CreateUnit(bd.pDeck, bd.eDeck);



	//背景画像の登録
	bgImg_ = LoadGraph("./Data/Image/bg/blue_bg.png");
	frameImg_ = LoadGraph("./Data/Image/UI/frame_full.png");
	topFrameImg_= LoadGraph("./Data/Image/UI/Turn.png");


	//フェーズの変更
	ChangeGamePhase(GAME_PHASE::RULLET_TIME);

	//サウンドの登録
	auto& sMng = SoundManager::GetInstance();
	bgmHandle_ = sMng.LoadSound(SoundManager::SOUND_TYPE::BATTLE1_BGN);

	//BGMの再生
	//sMng.PlaySoundBGM(bgmHandle_);



} 

void GameScene::Update(void)
{
	//デルタタイム
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;


	//入力
	auto& ins = InputManager::GetInstance();
	// シーン遷移
#ifdef _DEBUG
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	}
#endif // _DEBUG


	//更新
	unitMng_->Update();
	GameUi_->Update();

	//死亡演出の更新
	DeathStaging::GetInstance().Update();



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
	case GameScene::GAME_PHASE::EFFECT:
		UpdateEffect();
		break;
	case GameScene::GAME_PHASE::BATTLE:
		UpdateBattle();
		break;
	case GameScene::GAME_PHASE::BUFF_EFFECT :
		UpdateBuffEffect();
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
	DrawGraph(-20, 110, frameImg_, true);
	DrawGraph(0, 0, topFrameImg_, true);

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
	case GameScene::GAME_PHASE::EFFECT:
		GameUi_->DrawActivSkill();
		break;
	case GameScene::GAME_PHASE::BATTLE:
		break;
	case GameScene::GAME_PHASE::BUFF_EFFECT:
		break;
	case GameScene::GAME_PHASE::TURN_END:
		break;
	case GameScene::GAME_PHASE::GAME_END:
		//結果の表示
		_dbgDrawFormatString(0, 0, 0xffffff, "ゲーム終了");
		break;
	}

	//死亡演出
	DeathStaging::GetInstance().PlayDeathStaging();

#ifdef DEBUG
	auto cx = Application::SCREEN_SIZE_X;
	auto cy = Application::SCREEN_SIZE_Y;
	auto span = 20;
	for (size_t i = 0; i < 100; i++)
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
	//死亡演習クラスの開放
	DeathStaging::GetInstance().Release();

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
	DeleteGraph(topFrameImg_);

}

void GameScene::UpdateRouTime(void)
{
	//ルーレットの更新
	roulette_->Update();

	//ルーレットの停止操作（ユニットによって自動か手動か決める）
	roulette_->StopRoulette(actUnitAoutm_);

	//バフ判断
	//行動ユニット
	if (unitMng_->GetActivUnit()->CheckOwnBuff(Buff::BUFF_TYPE::PALALYSIS))
	{
		TRACE(unitMng_->GetActivUnit()->GetUnitName().c_str());
		TRACE("はマヒしている\n\n");

		//麻痺状態の場合、バフエフェクト再生後ターンエンドする
		nextPhase_ = GAME_PHASE::TURN_END;
		ChangeGamePhase(GAME_PHASE::BUFF_EFFECT);
		return;
	}

	//ルーレットが停止したら、フェーズ移動
	bool next = roulette_->GetRouStop();
	if(next)ChangeGamePhase(GAME_PHASE::AIM);
	
}

void GameScene::UpdateAIM(void)
{	
	//対象を選択したら、エフェクト再生に進む
	bool next = battleSys_->SelectUnit(actUnitAoutm_);
	if(next)ChangeGamePhase(GAME_PHASE::EFFECT);
}

void GameScene::UpdateEffect(void)
{
	//エフェクト再生が終了したかどうか判断
	bool next = EffectManager::GetInstance().FinishEffect();

	//コマンドタイプによって、フェーズ先を変更
	if (next) {
		//エフェクトアニメーションが終了したら
		if (roulette_->GetCmd()->GetCmdType() == Command::CMD_TYPE::BUFF)
		{
			//バフエフェクトフェーズに進む
			nextPhase_ = GAME_PHASE::NONE;
			ChangeGamePhase(GAME_PHASE::BUFF_EFFECT);
		}
		else
		{
			//バトルフェーズに進む
			ChangeGamePhase(GAME_PHASE::BATTLE);
		}
	}
}

void GameScene::UpdateBattle(void)
{
	//ダメージ減少が終了したかどうか判断
	bool next = battleSys_->FinishedDecHP();

	//死亡演出中の場合、進行しない
	if(DeathStaging::GetInstance().PlayingStaging())return;

	//バトル（ダメージ減少）が終了したら、ターン終了に進む
	if (next)ChangeGamePhase(GAME_PHASE::TURN_END);
}

void GameScene::UpdateBuffEffect(void)
{
	//(行動時)バフエフェクト処理
	//if (!unitMng_->GetActivUnit()->PlayBuffEffect())return;

	//(付与時)バフエフェクト処理
	bool next = battleSys_->FinishedBuffEffect();

	//状態異常シェーダー観測地点ーーーーーーーーーーーーーーーーーーーーーーーーーー
	nextPhase_ = GAME_PHASE::TURN_END;



	//バフエフェクト終了時、次のフェーズに進む
	if(next)ChangeGamePhase(nextPhase_);
}

void GameScene::UpdateTurnEnd(void)
{
	//ダメージ減少が終了したかどうか判断（毒ダメージ）
	bool next = unitMng_->GetActivUnit()->DecHpProcess();


	//全滅ならばゲーム終了、
	//そうでない且、必要処理終了後ならルーレットフェーズに進む。
	if (next) 
	{
		if (unitMng_->IsAnniUnit())ChangeGamePhase(GAME_PHASE::GAME_END);
		else					   ChangeGamePhase(GAME_PHASE::RULLET_TIME);
	}
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
	case GameScene::GAME_PHASE::RULLET_TIME: {
		//選択ユニットのリセット
		battleSys_->ResetSelectUnits();

		//行動ユニットの整理
		unitMng_->ChangeActivUnit();

		//行動ユニット
		//ルーレットの停止が手動か自動か判断
		actUnitAoutm_ = (unitMng_->GetActivUnit()->GetUnitType() == UnitBase::UNIT_TYPE::ENEMY);

		//ルーレットにコマンド技をセット
		roulette_->SetCommand(unitMng_->GetCommand());
		//ルーレット状況のリセット
		roulette_->ResetRouSpin();


		//現在の行動ユニットのターン文字 
		bool turn = unitMng_->GetActivUnit()->GetUnitType() == UnitBase::UNIT_TYPE::PLAYER;
		int color = turn ? 0x00ff00 : 0xff0000;		//緑：赤
		auto& name = unitMng_->GetActivUnit()->GetUnitName();
		GameUi_->SetTurnString(name, color);

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
	case GameScene::GAME_PHASE::EFFECT: {

		//コマンドからエフェクト番号の取得
		int num = roulette_->GetCmd()->GetEffectNum();

		//ターゲットの座標取得(ターゲットが存在しない場合、自分座標)
		Vector2 pos = unitMng_->GetActivUnit()->GetUnitPos();
		auto& target = battleSys_->GetTargetUnit();

		if (target.size() <= 0)
		{
			//エフェクト再生(ターゲットが存在しない場合)
			EffectManager::GetInstance().PlayEffect(num, pos);
			return;
		}

		for (auto& unit : target)
		{
			//ユニットの座標を取得
			pos=unit->GetUnitPos();
			//エフェクト再生
			EffectManager::GetInstance().PlayEffect(num, pos);
		}

		break;
	}
	case GameScene::GAME_PHASE::BATTLE: {
		//コマンド処理
		battleSys_->CmdProcess();

		break;
	}
	case GameScene::GAME_PHASE::BUFF_EFFECT: {
		//コマンド処理をしない
		if (nextPhase_ == GameScene::GAME_PHASE::TURN_END)return;

		//コマンド処理
		battleSys_->CmdProcess();
		break;
	}
	case GameScene::GAME_PHASE::TURN_END: {
		//行動ユニットのエンド処理
		unitMng_->GetActivUnit()->TurnEndProcess();

		break;
	}
	case GameScene::GAME_PHASE::GAME_END: {
		break;
	}
	}
}

