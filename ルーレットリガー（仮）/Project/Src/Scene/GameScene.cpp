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

	//�^�[������
	turnString_ = "";
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
	case GameScene::GAME_PHASE::GAME_END:
		//�����F�Q�[���V�[���I��

		break;
	default:
		break;
	}
}

void GameScene::Draw(void)
{
	//�w�i
	DrawGraph(0, 0, bgImg_, true);
	//�t���[��
	DrawGraph(0, 0, frameImg_, true);

	//�I�u�W�F�N�g
	unitMng_->Draw();
	roulette_->Draw();

	//UI�֘A
	DrawString(580, 40, turnString_.c_str(), 0xffffff);

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
	case GameScene::GAME_PHASE::GAME_END:
		//���ʂ̕\��
		_dbgDrawFormatString(0, 0, 0xffffff, "�Q�[���I��");
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
	battleSys_->Release();
	delete battleSys_;

	//�摜���
	DeleteGraph(bgImg_);
	DeleteGraph(frameImg_);

}

void GameScene::UpdateRouTime(void)
{
	//���[���b�g�̍X�V
	roulette_->Update();

	//���[���b�g�̒�~�����i���j�b�g�ɂ���Ď������蓮�����߂�j
	roulette_->StopRoulette(actUnitAoutm_);

	//�o�t���f
	//�s�����j�b�g
	if (unitMng_->GetActivUnit()->CheckOwnBuff(Buff::BUFF_TYPE::PALALYSIS))
	{
		TRACE(unitMng_->GetActivUnit()->GetUnitName().c_str());
		TRACE("�̓}�q���Ă���\n\n");

		//��჏�Ԃ̏ꍇ�A�^�[���G���h����
		ChangeGamePhase(GAME_PHASE::TURN_END);
	}

	//���[���b�g����~������A�t�F�[�Y�ړ�
	if (roulette_->GetRouStop())
	{
		ChangeGamePhase(GAME_PHASE::AIM);
	}
}

void GameScene::UpdateAIM(void)
{	
	//�Ώۂ�I��������A�o�g���t�F�[�Y�ɐi��
	if (battleSys_->SelectUnit(actUnitAoutm_))
	{
		ChangeGamePhase(GAME_PHASE::BATTLE);
	}
}

void GameScene::UpdateBattle(void)
{
	//�_���[�W�������I���������ǂ������f
	bool next = battleSys_->FinishedDecHP();

	//�o�g���i�_���[�W�����j���I��������A�^�[���I���ɐi��
	if (next)ChangeGamePhase(GAME_PHASE::TURN_END);
}

void GameScene::UpdateTurnEnd(void)
{
	//�_���[�W�������I���������ǂ������f�i�Ń_���[�W�j
	bool next = unitMng_->GetActivUnit()->DecHpProcess();

	//�S�ł����f
	//�S�łȂ�΃Q�[���I���A
	//�����łȂ����A�K�v�����I����Ȃ烋�[���b�g�t�F�[�Y�ɐi�ށB
	if (next) {
		if (unitMng_->IsAnniUnit())ChangeGamePhase(GAME_PHASE::GAME_END);
		else ChangeGamePhase(GAME_PHASE::RULLET_TIME);
	}
}

void GameScene::ChangeGamePhase(GAME_PHASE phase)
{
	//�t�F�[�Y
	phase_ = phase;

	switch (phase_)
	{
	case GameScene::GAME_PHASE::BATTLE_START: {
		break;
	}
	case GameScene::GAME_PHASE::RULLET_TIME: {
		//�I�����j�b�g�̃��Z�b�g
		battleSys_->ResetSelectUnits();

		//�s�����j�b�g�̐���
		unitMng_->ChangeActivUnit();

		//�s�����j�b�g
		//���[���b�g�̒�~���蓮�����������f
		actUnitAoutm_ = (unitMng_->GetActivUnit()->GetUnitType() == UnitBase::UNIT_TYPE::ENEMY);

		//���[���b�g�ɃR�}���h�Z���Z�b�g
		roulette_->SetCommand(unitMng_->GetCommand());
		//���[���b�g�󋵂̃��Z�b�g
		roulette_->ResetRouSpin();


		//���݂̍s�����j�b�g�̃^�[������
		if (unitMng_->GetActivUnit()->GetUnitType() == UnitBase::UNIT_TYPE::ENEMY) {
			turnString_ = "�����Ẵ^�[��";
		}
		else {
			turnString_ = "���܂��̃^�[��";
		}

		break;
	}
	case GameScene::GAME_PHASE::AIM: {
		//���肵���R�}���h���Q�[��UI�Ɏ󂯓n��
		std::string cmd = roulette_->GetCmd()->GetName();
		GameUi_->SetCmdName(cmd);

		//�o�g���f�[�^�Ɋe����n��
		battleSys_->SetBattleData(unitMng_->GetActivUnit(),
			roulette_->GetCmd(), unitMng_->GetUnits());

		//�z�C�[���̃��Z�b�g
		GetMouseWheelRotVol();

		//�R�}���h�̑I��Ώۂ𔻒f����
		battleSys_->CheckSelectTarget();

		//���삪�����̏ꍇ�A���j�b�g�������_���Ɍ��߂�
		if (actUnitAoutm_)battleSys_->SetRandUnit();

		break;
	}
	case GameScene::GAME_PHASE::BATTLE: {
		//�_���[�W����
		battleSys_->CmdProcess();

		break;
	}
	case GameScene::GAME_PHASE::TURN_END: {
		//�s�����j�b�g�̃G���h����
		unitMng_->GetActivUnit()->TurnEndProcess();

		break;
	}
	case GameScene::GAME_PHASE::GAME_END: {
		break;
	}
	}
}

