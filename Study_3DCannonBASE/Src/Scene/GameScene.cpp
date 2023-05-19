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

	//�G�̐���
	enemy_ = new EnemyBase();
	//�t�F�[�Y�J��
	ChangeWave(Wave::FIRST);


	//�J�������[�h�̐ݒ�
	SceneManager::GetInstance().GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

	// �Q�[���I�[�o�[�n�_
	gameoverPoint_ = { 450.0f, 50.0f, 75.0f };
	// �Q�[���I�[�o�[����
	isGameover_ = false;
	// �Q�[���I�[�o�[�摜
	imgGameover_ =
		LoadGraph((Application::PATH_IMAGE + "Gameover.png").c_str());
	// �Q�[���N���A�摜
	imgGameclear_ =
		LoadGraph((Application::PATH_IMAGE + "GameClear.png").c_str());
	// �l�N�X�g�E�F�[�u�摜
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

	// �Q�[���I�[�o�[�Ȃ�A���g���C�����̂ݍs��
	if (isGameover_)
	{
		// �V�[���J��
		if (ins.IsTrgDown(KEY_INPUT_Z))
		{
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
			return;
		}
		return;
	}

	//�G�l�~�[������Ă�����
	if (!enemy_->IsAlive())
	{
		switch (wave_)
		{
		case GameScene::Wave::LAST:
			//�Q�[���N���A
			// �V�[���J��
			if (ins.IsTrgDown(KEY_INPUT_Z))
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
				return;
			}

			break;
		default:
			//���̃t�F�[�Y��
			if (ins.IsTrgDown(KEY_INPUT_Z))
			{
				ChangeWave(Wave::LAST);
			}
			break;
		}
	}

	//�X�V
	stage_->Update();
	cannnon_->Update();
	//�G
	//���S�̏ꍇ�A���������Ȃ�
	if (enemy_->IsAlive())
	{
		enemy_->Update();

		//�Q�[���I�[�o�[����
		//�G�l�~�[�ƃQ�[���I�[�o�[�n�_�̏Փ˔���
		auto dis = AsoUtility::Distance(
			gameoverPoint_, enemy_->GetCollisionPos());
		auto radious =
			OVER_COL_RADIOUS + enemy_->GetCollisionRadius();
		if (dis <= static_cast<float>(radious))
		{
			isGameover_ = true;
		}
	}

	//�X�e�[�W���f��ID
	int stageModelId = stage_->GetModel();
	//�e�̏���
	for (auto& shot : cannnon_->GetShots())
	{
		//�e�X�V
		shot->Update();

		// �������⏈���I����́A�ȍ~�̏����͎��s���Ȃ�
		if (!shot->IsShot())continue;

		//�e�ƃX�e�[�W�̏Փˏ���
		auto info = MV1CollCheck_Sphere(
			stageModelId, -1, shot->GetPos(), ShotBase::COL_RADIOUS);
		if (info.HitNum > 0)
		{
			shot->Blast();
		}
		// �����蔻�茋�ʃ|���S���z��̌�n��������
		MV1CollResultPolyDimTerminate(info);

		//���ƓG�̏Փˏ���
		//�G�����S��Ԃ̏ꍇ�A�����͂��Ȃ�
		if (!enemy_->IsAlive())return;

		//���̓��m�̓����蔻��
		auto dis = AsoUtility::Distance(
			shot->GetPos(), enemy_->GetCollisionPos());
		auto radious =
			ShotBase::COL_RADIOUS + enemy_->GetCollisionRadius();
		if (dis <= static_cast<float>(radious))
		{
			//�Փ˂��Ă���
			// �G�Ƀ_���[�W��^����
			enemy_->Damage(1);
			shot->Blast();
			break;
		}

		//_dbgDrawFormatString(0.0f, 150.0f, 0xff0000, "����:%0.2f",
		//	static_cast<float>(dis));
		//_dbgDrawFormatString(0.0f, 166.0f, 0xff0000, "���v:%0.2f", radious);
	}
}

void GameScene::Draw(void)
{
	//�`��
	stage_->Draw();
	cannnon_->Draw();
	//�G
	enemy_->Draw();

	// �e�̕`�揈��
	for (auto& shot : cannnon_->GetShots())
	{
		shot->Draw();
	}

#ifdef _DEBUG
	DrawSphere3D(gameoverPoint_, OVER_COL_RADIOUS, 5, 0x000ff, 0x000ff, false);

#endif // _DEBUG

	int screenX = Application::SCREEN_SIZE_X / 2;
	int screenY = Application::SCREEN_SIZE_Y / 2;

	//�Q�[���I�[�o�[�摜�̕\��
	if (isGameover_)
	{
		DrawGraph(screenX - 325, 250.0f, imgGameover_, true);
	}

	//�Q�[���N���A�摜�@or�@�l�N�X�g�E�F�[�u�摜�̕\��
	if (!enemy_->IsAlive())
	{
		switch (wave_)
		{
		case GameScene::Wave::LAST:
			//�Q�[���N���A�摜
			DrawGraph(screenX - 325, 250.0f, imgGameclear_, true);
			break;
		default:
			//�l�N�X�g�E�F�[�u�摜
			DrawGraph(screenX - 325, 250.0f, imgNextWave_, true);
			break;
		}
	}

	//���g���C�w��
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

	//�摜�̔j��
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
		//�Z�b�g����G�^�C�v
		eType = EnemyBase::ENEMY_TYPE::SMALL;

		break;
	case GameScene::Wave::LAST:
		//�Z�b�g����G�^�C�v
		eType = EnemyBase::ENEMY_TYPE::BIG;

		break;
	case GameScene::Wave::END:
		break;
	default:
		break;
	}

	//�G�̃Z�b�g
	enemy_->SetEnemyType(eType);
	//�G�l�~�[�̏�����
	enemy_->Init();

}
