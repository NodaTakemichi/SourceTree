#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/DrawShader.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	//�摜�̓o�^
	titleImg_ = LoadGraph("./Data/Image/UI/title.png");
	backImg_ = LoadGraph("./Data/Image/bg/title_bg.jpg");

	//�V�F�[�_�[�o�^

	//�t�H���g�n���h��
	fontHandle_ = CreateFontToHandle("", 20, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

	fontColor_ = GetColor(150, 150, 0);

}

void TitleScene::Update(void)
{
	//�V�[���J��
	auto& ins = InputManager::GetInstance();
	if (ins.IsClickMouseLeft())
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	}

	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;


}

void TitleScene::Draw(void)
{
	auto& draw = DrawShader::GetInstance();

	//�w�i�`��
	DrawGraph(0, 0, backImg_, true);
	//�����X�^�[�`��

	//�^�C�g���`��
	draw.DrawGraphToShader({ 0,0 }, titleImg_, psTitle_);
	//�w���`��
	DrawStringToHandle(
		100, 600,
		"�N���b�N�ŃX�^�[�g�I",
		0xffffff, fontColor_);

}

void TitleScene::Release(void)
{
	DeleteGraph(titleImg_);
	DeleteGraph(backImg_);

	monsters_.clear();

	DeleteFontToHandle(fontHandle_);

	DeleteShader(psTitle_);
	DeleteShader(psMon_);
}
