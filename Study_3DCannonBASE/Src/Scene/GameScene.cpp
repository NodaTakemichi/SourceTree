#include"../Application.h"
#include"../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include"../Manager//Camera.h"
#include"../Utility/AsoUtility.h"
#include"../Object/Stage.h"
#include"../Object/Cannon.h"
#include"../Object/ShotBase.h"
#include"../Object/EnemyBase.h"


#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"

#include "GameScene.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	stage_ = new Stage();
	stage_->Init();

	cannnon_ = new Cannon();
	cannnon_->Init();

	//敵の生成
	enemy_ = new EnemyBase();
	//フェーズ遷移
	ChangeWave(Wave::FIRST);


	//カメラモードの設定
	SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

	// ゲームオーバー地点
	gameoverPoint_ = { 450.0f, 50.0f, 75.0f };
	// ゲームオーバー判定
	isGameover_ = false;
	// ゲームオーバー画像
	imgGameover_ =
		LoadGraph((Application::PATH_IMAGE + "Gameover.png").c_str());
	// ゲームクリア画像
	imgGameclear_ =
		LoadGraph((Application::PATH_IMAGE + "GameClear.png").c_str());
	// ネクストウェーブ画像
	imgNextWave_ =
		LoadGraph((Application::PATH_IMAGE + "NextWave.png").c_str());

}

void GameScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
		return;
	}

	// ゲームオーバーなら、リトライ処理のみ行う
	if (isGameover_)
	{
		// シーン遷移
		if (ins.IsTrgDown(KEY_INPUT_Z))
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
			return;
		}
		return;
	}

	//エネミーがやられていたら
	if (!enemy_->IsAlive())
	{
		switch (wave_)
		{
		case GameScene::Wave::LAST:
			//ゲームクリア
			// シーン遷移
			if (ins.IsTrgDown(KEY_INPUT_Z))
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
				return;
			}

			break;
		default:
			//次のフェーズへ
			if (ins.IsTrgDown(KEY_INPUT_Z))
			{
				ChangeWave(Wave::LAST);
			}
			break;
		}
	}

	//更新
	stage_->Update();
	cannnon_->Update();
	//敵
	//死亡の場合、処理をしない
	if (enemy_->IsAlive())
	{
		enemy_->Update();

		//ゲームオーバー判定
		//エネミーとゲームオーバー地点の衝突判定
		auto dis = AsoUtility::Distance(
			gameoverPoint_, enemy_->GetCollisionPos());
		auto radious =
			OVER_COL_RADIOUS + enemy_->GetCollisionRadius();
		if (dis <= static_cast<float>(radious))
		{
			isGameover_ = true;
		}
	}

	//ステージモデルID
	int stageModelId = stage_->GetModel();
	//弾の処理
	for (auto& shot : cannnon_->GetShots())
	{
		//弾更新
		shot->Update();

		// 爆発中や処理終了後は、以降の処理は実行しない
		if (!shot->IsShot())continue;

		//弾とステージの衝突処理
		auto info = MV1CollCheck_Sphere(
			stageModelId, -1, shot->GetPos(), ShotBase::COL_RADIOUS);
		if (info.HitNum > 0)
		{
			shot->Blast();
		}
		// 当たり判定結果ポリゴン配列の後始末をする
		MV1CollResultPolyDimTerminate(info);

		//球と敵の衝突処理
		//敵が死亡状態の場合、処理はしない
		if (!enemy_->IsAlive())return;

		//球体同士の当たり判定
		auto dis = AsoUtility::Distance(
			shot->GetPos(), enemy_->GetCollisionPos());
		auto radious =
			ShotBase::COL_RADIOUS + enemy_->GetCollisionRadius();
		if (dis <= static_cast<float>(radious))
		{
			//衝突している
			// 敵にダメージを与える
			enemy_->Damage(1);
			shot->Blast();
			break;
		}

		//_dbgDrawFormatString(0.0f, 150.0f, 0xff0000, "距離:%0.2f",
		//	static_cast<float>(dis));
		//_dbgDrawFormatString(0.0f, 166.0f, 0xff0000, "合計:%0.2f", radious);
	}
}

void GameScene::Draw(void)
{
	//描画
	stage_->Draw();
	cannnon_->Draw();
	//敵
	enemy_->Draw();

	// 弾の描画処理
	for (auto& shot : cannnon_->GetShots())
	{
		shot->Draw();
	}

#ifdef _DEBUG
	DrawSphere3D(gameoverPoint_, OVER_COL_RADIOUS, 5, 0x000ff, 0x000ff, false);

#endif // _DEBUG

	int screenX = Application::SCREEN_SIZE_X / 2;
	int screenY = Application::SCREEN_SIZE_Y / 2;

	//ゲームオーバー画像の表示
	if (isGameover_)
	{
		DrawGraph(screenX - 325, 250.0f, imgGameover_, true);
	}

	//ゲームクリア画像　or　ネクストウェーブ画像の表示
	if (!enemy_->IsAlive())
	{
		switch (wave_)
		{
		case GameScene::Wave::LAST:
			//ゲームクリア画像
			DrawGraph(screenX - 325, 250.0f, imgGameclear_, true);
			break;
		default:
			//ネクストウェーブ画像
			DrawGraph(screenX - 325, 250.0f, imgNextWave_, true);
			break;
		}
	}

	//リトライ指示
	SetFontSize(48);
	if (isGameover_ || !enemy_->IsAlive())
	{
		DrawString(20, 550.0f, "Please 'Z' Button", 0x0);
	}
	SetFontSize(16);

}

void GameScene::Release(void)
{
	stage_->Release();
	cannnon_->Release();
	enemy_->Release();

	//画像の破棄
	DeleteGraph(imgGameclear_);
	DeleteGraph(imgGameover_);
	DeleteGraph(imgNextWave_);


}

void GameScene::ChangeWave(Wave phase)
{
	wave_=phase;
	EnemyBase::ENEMY_TYPE eType;

	switch (wave_)
	{
	case GameScene::Wave::FIRST:
		//セットする敵タイプ
		eType = EnemyBase::ENEMY_TYPE::SMALL;

		break;
	case GameScene::Wave::LAST:
		//セットする敵タイプ
		eType = EnemyBase::ENEMY_TYPE::BIG;

		break;
	case GameScene::Wave::END:
		break;
	default:
		break;
	}

	//敵のセット
	enemy_->SetEnemyType(eType);
	//エネミーの初期化
	enemy_->Init();

}
