#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/SoundManager.h"
#include "../Manager/InputManager.h"
#include "../Common/Vector2.h"
#include "../Utility/DrawShader.h"
#include "../Utility/ButtonUI.h"

#include"../_debug/_DebugDispOut.h"

#include "SelectScene.h"

SelectScene::SelectScene(void)
{
}

SelectScene::~SelectScene(void)
{
}

void SelectScene::Init(void)
{
	//������
	totalTime_ = 0.0f;

	//�摜�̓o�^
	bgImg_ = LoadGraph("./Data/Image/bg/select.jpg");

	//�V�F�[�_�[�o�^
	psTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");

	//�t�H���g�n���h��
	//fontHandle_ = CreateFontToHandle("", 20, -1,
	//	DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);
	//fontColor_ = GetColor(150, 150, 0);

	//������
	devilImg_ = LoadGraph("./Data/Image/UI/������_���J��.png");
	devilPos_ = { 0,100 };
	shakeY_ = 0;

	//�{�^��UI����
	CerateBtnUI();

}

void SelectScene::Update(void)
{
	//�V�[���J��
	//auto& ins = InputManager::GetInstance();
	//if (ins.IsClickMouseLeft())
	//{
	//	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	//}

	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//�����܍��W
	shakeY_ = sinf(totalTime_) * 30.0f;

	for  (auto& btn:buttons_)
	{
		btn->Draw();
	}

}

void SelectScene::Draw(void)
{
	auto& sx = Application::SCREEN_SIZE_X;
	auto& sy = Application::SCREEN_SIZE_Y;
	auto& ds = DrawShader::GetInstance();

	//�w�i
	ds.DrawExtendGraphToShader(
		{ 0,0 }, { sx,sy }, bgImg_, psTex_, COLOR_F{}
	);

	//�����ܕ`��
	ds.DrawGraphToShader(
		{devilPos_.x ,devilPos_.y + shakeY_ }, devilImg_, psTex_
	);


#ifdef DEBUG
	auto span = 20;
	for (size_t i = 0; i < 60; i++)
	{
		//X
		DrawLine(0, i * span, sx, i * span, 0xff0000);

		//Y
		DrawLine(i * span, 0, i * span, sy, 0x0000ff);
	}
#endif // _DEBUG

}

void SelectScene::Release(void)
{
}

void SelectScene::CerateBtnUI(void)
{

	backBtnImg_ = LoadGraph("./Data/Image/UI/BackBtnImg.png");

	int handle = LoadGraph("");

	//�쐬
	ButtonUI* b = new ButtonUI();
	b->Create({ 500,500 }, { 0,0 }, backBtnImg_, -1);
	buttons_.emplace_back(b);

}
