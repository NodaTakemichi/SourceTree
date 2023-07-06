#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Utility/Button/CircleButton.h"
#include "EditScene.h"

EditScene::EditScene(void)
{
}

EditScene::~EditScene(void)
{
}

void EditScene::Init(void)
{
	//�摜�̓o�^
	bgImg_ = LoadGraph("Data/Image/bg/EditScene_bg.png");
	//editFrameImg_ = LoadGraph("");

	//�{�^���摜
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");
	int sy = Application::SCREEN_SIZE_Y;

	//�o�b�N�{�^���̐���
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);

}

void EditScene::Update(void)
{
	//�o�b�N�{�^��
	backBtn_->Update();

	if (backBtn_->ButtonDecision())
	{
		//�V�[���J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	}
}

void EditScene::Draw(void)
{
	//�w�i
	DrawGraph(0, 0, bgImg_, true);

	//�ҏW�t���[��
	DrawGraph(0, 0, editFrameImg_, true);

	//�{�^��UI
	//�}�C�f�b�L

	//���j�b�g�v�[��

	//���j�b�g���

	//�ǉ��{�^��

	//�o�b�N�{�^��
	backBtn_->Draw();

}

void EditScene::Release(void)
{
	backBtn_->Release();
	delete backBtn_;
}
