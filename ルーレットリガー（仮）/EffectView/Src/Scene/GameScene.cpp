#include <cmath>
#include <DxLib.h>
#include "../Application.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"

#include "../Manager/EffectManager.h"

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

	//エフェクトマネージャー
	efMng_ = new EffectManager();
	efMng_->Init();



	//テスト
	testNum = 0;
	testPos = {0,0};
	testScale = 20.0f; 
	path = "";


} 

void GameScene::Update(void)
{
	//デルタタイム
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//入力
	auto& ins = InputManager::GetInstance();

	//エフェクトの停止
	efMng_->FinishEffect();

	//エフェクトの調査
	//オフセット値を調べる
	if (CheckHitKey(KEY_INPUT_UP))   testPos.y -= 1;
	if (CheckHitKey(KEY_INPUT_DOWN)) testPos.y += 1;
	if (CheckHitKey(KEY_INPUT_LEFT)) testPos.x -= 1;
	if (CheckHitKey(KEY_INPUT_RIGHT))testPos.x += 1;
	if(ins.IsTrgDown(KEY_INPUT_V))testScale+=5;
	if(ins.IsTrgDown(KEY_INPUT_C))testScale-=5;


	if (ins.IsTrgDown(KEY_INPUT_Z)) {
		testNum--;
		path = efMng_->GetPathName(testNum);
	}
	if (ins.IsTrgDown(KEY_INPUT_X)) {
		testNum++;
		path = efMng_->GetPathName(testNum);
	}


	testNum = AsoUtility::Wrap(testNum, 0, 160);
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		efMng_->FinishEffect();
		//再生
		efMng_->PlayEffect(testNum, { testPos.x + 250, testPos.y + 250 });
		//efMng_->PlayEffect(testNum, { testPos.x + 250, testPos.y + 250 }, testScale);
	}
	_dbgDrawFormatString(
		0, 5, 0xffffff, "番号：%d＿大きさ：%d＿座標：｛%d,%d｝", 
		testNum, (int)testScale, testPos.x, testPos.y);
	_dbgDrawFormatString(
		0, 21, 0xffffff, path.c_str());
	return;

}

void GameScene::Draw(void)
{
	int sPos = 100;
	for (int i = 0; i <= 5; i++)
	{
		DrawLine(sPos + i * 100, sPos, sPos + i * 100, sPos + 400,
			GetColor(200, 200, 200));
		DrawLine(sPos, sPos + i * 100, sPos + 400, sPos + i * 100,
			GetColor(200, 200, 200));
	}
}

void GameScene::Release(void)
{

}



