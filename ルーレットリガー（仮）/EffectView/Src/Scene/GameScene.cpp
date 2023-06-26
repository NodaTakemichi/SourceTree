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

	//�G�t�F�N�g�}�l�[�W���[
	efMng_ = new EffectManager();
	efMng_->Init();



	//�e�X�g
	testNum = 0;
	testPos = {0,0};
	testScale = 20.0f; 
	path = "";


} 

void GameScene::Update(void)
{
	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//����
	auto& ins = InputManager::GetInstance();

	//�G�t�F�N�g�̒�~
	efMng_->FinishEffect();

	//�G�t�F�N�g�̒���
	//�I�t�Z�b�g�l�𒲂ׂ�
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
		//�Đ�
		efMng_->PlayEffect(testNum, { testPos.x + 250, testPos.y + 250 });
		//efMng_->PlayEffect(testNum, { testPos.x + 250, testPos.y + 250 }, testScale);
	}
	_dbgDrawFormatString(
		0, 5, 0xffffff, "�ԍ��F%d�Q�傫���F%d�Q���W�F�o%d,%d�p", 
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



