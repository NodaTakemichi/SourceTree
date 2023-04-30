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
	//���j�b�g�}�l�[�W���[
	unitMng_ = new UnitManager();
	unitMng_->Init();

	//���[���b�g
	roulette_ = new Roulette();
	roulette_->Init();

	//UI
	GameUi_ = new GameUI();
	GameUi_->Init();

	//�o�g���V�X�e��
	battleSys_ = new BattleSystem();
	battleSys_->Init();


	//�摜�̓o�^
	bgImg_ = LoadGraph("./Data/Image/bg/blue_bg.png");
	//�t���[��
	frameImg_ = LoadGraph("./Data/Image/UI/Frame.png");

	//�t�F�[�Y�̕ύX
	ChangeGamePhase(GAME_PHASE::RULLET_TIME);

} 

void GameScene::Update(void)
{


	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	mTotalTime += delta;

	//����
	auto& ins = InputManager::GetInstance();
	// �V�[���J��
#ifdef _DEBUG
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}
#endif // _DEBUG

	//�X�V
	unitMng_->Update();
	roulette_->Update();
	GameUi_->Update();

	//�t�F�[�Y�ʍX�V
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
	//�w�i
	//DrawGraph(0, 0, bgImg_, true);
	//�t���[��
	DrawGraph(0, 0, frameImg_, true);

	//�I�u�W�F�N�g
	unitMng_->Draw();
	roulette_->Draw();

	//UI�֘A
	GameUi_->Draw();

	//�t�F�[�Y�ʕ`��
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
	//�j��
	unitMng_->Release();
	delete unitMng_;
	roulette_->Release();
	delete roulette_;
	GameUi_->Release();
	delete GameUi_;

	//�摜���
	DeleteGraph(bgImg_);
	DeleteGraph(frameImg_);

}

void GameScene::UpdateRouTime(void)
{
	//���[���b�g����~������A�t�F�[�Y�ړ�
	if (roulette_->GetRouStop())
	{

		//���肵���R�}���h���Q�[��UI�Ɏ󂯓n��
		std::string cmd = roulette_->GetCmd()->GetName();
		GameUi_->SetCmdName(cmd);

		//�o�g���f�[�^�ɏ���n��
		battleSys_->SetBattleData(unitMng_->GetActivUnit(), 
			roulette_->GetCmd(), unitMng_->GetUnits());

		ChangeGamePhase(GAME_PHASE::AIM);
	}
}

void GameScene::UpdateAIM(void)
{	

	//�Ώۂ�I��������A�o�g���t�F�[�Y�ɐi��
	if (battleSys_->SelectUnit())
	{
		ChangeGamePhase(GAME_PHASE::BATTLE);
	}
}

void GameScene::UpdateBattle(void)
{
	//�o�g�����I��������A�^�[���I���ɐi��
	if (true)ChangeGamePhase(GAME_PHASE::TURN_END);

}

void GameScene::UpdateTurnEnd(void)
{
	//�^�[���I�����ɏ�ʐ������s���A���[���b�g�t�F�[�Y�ɐi��
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

		//���[���b�g�ɃR�}���h�Z���Z�b�g
		roulette_->SetCommand(unitMng_->GetCommand());
		//���[���b�g�󋵂̃��Z�b�g
		roulette_->ResetRouSpin();

		break;
	case GameScene::GAME_PHASE::AIM:
		//�R�}���h�̑I��Ώۂ𔻒f����
		battleSys_->CheckSelectTarget();

		//�z�C�[���̏�����
		GetMouseWheelRotVol();

		break;
	case GameScene::GAME_PHASE::BATTLE:
		break;
	case GameScene::GAME_PHASE::TURN_END:
		//�s�����j�b�g�̐���
		unitMng_->ChangeActivUnit();
		break;
	default:
		break;
	}
}

