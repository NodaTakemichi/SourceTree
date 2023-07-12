#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/DrawShader.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"

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
	titleImg_ = LoadGraph("Data/Image/UI/�^�C�g��.png");
	titleImgNor_ = LoadGraph("Data/Image/UI/�^�C�g��_n.png");
	titleBackImg_ = LoadGraph("Data/Image/UI/�^�C�g���o�b�N.png");
	bgImg_ = LoadGraph("Data/Image/bg/title_bg.jpg");


	unitsImg_.push_back(LoadGraph("Data/Image/UI/Units_3.png"));
	unitsImg_.push_back(LoadGraph("Data/Image/UI/Units_2.png"));
	unitsImg_.push_back(LoadGraph("Data/Image/UI/Units_1.png"));

	//�V�F�[�_�[�o�^
	psIumi_ = LoadPixelShader("");
	psTitle_ = LoadPixelShader("./x64/Debug/NormalMap.cso");

	//�t�H���g�n���h��
	fontHandle_ = CreateFontToHandle("HGS�n�p�p�޼��UB", 40, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

	fontColor_ = GetColor(230, 230, 250);
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
	auto& ds = DrawShader::GetInstance();
	auto cx = Application::SCREEN_SIZE_X;
	auto cy = Application::SCREEN_SIZE_Y;

	//�w�i�`��
	DrawGraph(0, 0, bgImg_, true);
	//�����X�^�[�`��
	for (auto& unitImg : unitsImg_)
	{
		DrawGraph(0, 0, unitImg, true);
	}

	//�^�C�g�����S�`��
	int posY = 60;
	DrawGraph(0, posY,titleBackImg_, true);

	COLOR_F buf = COLOR_F{
		totalTime_
	};
	ds.GetInstance().DrawGraphAndSubToShader(
		{ 0,posY }, titleImg_, titleImgNor_, psTitle_, buf);
	

	//�w���`��
	std::string s = "�N���b�N�ŃX�^�[�g�I";
	auto len = AsoUtility::StringLength(s, fontHandle_) / 2;
	DrawStringToHandle(
		cx / 2 - len, 600,
		"�N���b�N�ŃX�^�[�g�I",
		fontColor_, fontHandle_);

#ifdef DEBUG
	auto span = 20;
	for (size_t i = 0; i < 100; i++)
	{
		//X
		DrawLine(0, i * span, cx, i * span, 0xff0000);

		//Y
		DrawLine(i * span, 0, i * span, cy, 0x0000ff);
	}
#endif // _DEBUG
}

void TitleScene::Release(void)
{
	DeleteGraph(titleImg_);
	DeleteGraph(titleImgNor_);
	DeleteGraph(titleBackImg_);
	DeleteGraph(bgImg_);
	for (auto& img : unitsImg_)
	{
		DeleteGraph(img);
	}
	unitsImg_.clear();

	DeleteFontToHandle(fontHandle_);

	DeleteShader(psTitle_);
	DeleteShader(psIumi_);
}
