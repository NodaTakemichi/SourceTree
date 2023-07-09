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

	//���[���b�g
	roulette_ = new Roulette();
	roulette_->Init();

	//UI
	GameUi_ = new GameUI();
	GameUi_->Init();

	//�o�g���V�X�e��
	battleSys_ = new BattleSystem();
	battleSys_->Init();

	//���j�b�g�}�l�[�W���[
	unitMng_ = new UnitManager();
	unitMng_->Init();
	//���j�b�g�̐���
	auto& bd = BattleDataManager::GetInstance().GetBattleData();
	unitMng_->CreateUnit(bd.pDeck, bd.eDeck);



	//�w�i�摜�̓o�^
	bgImg_ = LoadGraph("./Data/Image/bg/blue_bg.png");
	frameImg_ = LoadGraph("./Data/Image/UI/frame_full.png");
	topFrameImg_= LoadGraph("./Data/Image/UI/Turn.png");


	//�t�F�[�Y�̕ύX
	ChangeGamePhase(GAME_PHASE::RULLET_TIME);

	//�T�E���h�̓o�^
	auto& sMng = SoundManager::GetInstance();
	bgmHandle_ = sMng.LoadSound(SoundManager::SOUND_TYPE::BATTLE1_BGN);

	//BGM�̍Đ�
	//sMng.PlaySoundBGM(bgmHandle_);



} 

void GameScene::Update(void)
{
	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//����
	auto& ins = InputManager::GetInstance();
	// �V�[���J��
#ifdef DEBUG
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}
#endif // _DEBUG


	return;

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
	case GameScene::GAME_PHASE::EFFECT:
		UpdateEffect();
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
	DrawGraph(-20, 110, frameImg_, true);
	DrawGraph(0, 0, topFrameImg_, true);

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
	case GameScene::GAME_PHASE::EFFECT:
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

	//���S���o
	DeathStaging::GetInstance().Draw();

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

	//���[���b�g�̒�~����i���j�b�g�ɂ���Ď������蓮�����߂�j
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
	//�Ώۂ�I��������A�G�t�F�N�g�Đ��ɐi��
	if (battleSys_->SelectUnit(actUnitAoutm_))
	{
		ChangeGamePhase(GAME_PHASE::EFFECT);
	}
}

void GameScene::UpdateEffect(void)
{

	//�G�t�F�N�g�Đ����I���������ǂ������f
	bool next = EffectManager::GetInstance().FinishEffect();

	//�G�t�F�N�g�A�j���[�V�������I��������A�o�g���t�F�[�Y�ɐi��
	if (next)ChangeGamePhase(GAME_PHASE::BATTLE);

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

	//�S�łȂ�΃Q�[���I���A
	//�����łȂ����A�K�v�����I����Ȃ烋�[���b�g�t�F�[�Y�ɐi�ށB
	if (next) 
	{
		if (unitMng_->IsAnniUnit())ChangeGamePhase(GAME_PHASE::GAME_END);
		else					   ChangeGamePhase(GAME_PHASE::RULLET_TIME);
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
		bool turn = unitMng_->GetActivUnit()->GetUnitType() == UnitBase::UNIT_TYPE::PLAYER;
		auto color = turn ? 0x00ff00 : 0xff0000;		//�΁F��
		auto name = unitMng_->GetActivUnit()->GetUnitName();
		GameUi_->SetTurnString(name, color);

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
	case GameScene::GAME_PHASE::EFFECT: {

		//�R�}���h����G�t�F�N�g�ԍ��̎擾
		int num = roulette_->GetCmd()->GetEffectNum();

		//�^�[�Q�b�g�̍��W�擾(�^�[�Q�b�g�����݂��Ȃ��ꍇ�A�������W)
		Vector2 pos = unitMng_->GetActivUnit()->GetUnitPos();
		auto target = battleSys_->GetTargetUnit();

		if (target.size() <= 0)
		{
			//�G�t�F�N�g�Đ�(�^�[�Q�b�g�����݂��Ȃ��ꍇ)
			EffectManager::GetInstance().PlayEffect(num, pos);
			return;
		}

		for (auto& unit : target)
		{
			//���j�b�g�̍��W���擾
			pos=unit->GetUnitPos();
			//�G�t�F�N�g�Đ�
			EffectManager::GetInstance().PlayEffect(num, pos);
		}

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

