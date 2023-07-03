#include <DxLib.h>
#include <cstdlib>
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

	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//�����܍��W
	shakeY_ = sinf(totalTime_) * 20.0f;

	//�e�{�^���X�V
	BtnProcess();




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

	//�{�^��
	for (auto& btn : buttons_)
	{
		btn->Draw();
	}



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

void SelectScene::BtnProcess()
{
	for (auto& btn : buttons_)
	{
		btn->Update();
	}

	//�{�^���̏�Ƀ}�E�X������Ă��邩�m�F
	for (auto& btn : buttons_)
	{
	}


	//�{�^���N���b�N����
	for (auto& btn : buttons_)
	{
		btn->PushButton();
	}


	//�{�^�����菈��
	if (buttons_[0]->ButtonDecision())
	{
		BattleBtnProcess();
	}
	if (buttons_[4]->ButtonDecision())
	{
		ExitBtnProcess();
	}

}

void SelectScene::CerateBtnUI(void)
{
	//�X�N���[���T�C�Y
	auto& sx = Application::SCREEN_SIZE_X;
	auto& sy = Application::SCREEN_SIZE_Y;

	//�w�ʉ摜
	backBtnImg_ = LoadGraph("./Data/Image/UI/BackBtnImg.png");
	int x, y;
	GetGraphSize(backBtnImg_, &x, &y);

	//��O�摜
	std::vector<int> handle;
	handle.push_back(LoadGraph("./Data/Image/UI/�o�g��.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/�f�b�L�ҏW.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/���[���u�b�N.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/�N���W�b�g.png"));
	handle.push_back(LoadGraph("./Data/Image/UI/�ޏo.png"));

	//�쐬
	int cout = 5;
	for (int i = 0; i < cout; i++)
	{
		ButtonUI* b = new ButtonUI();

		int r = i % 2;
		//���W
		Vector2 pos = {
			(sx / 2) - (x * 2) - (x / 2) + (x * i)  ,
			sy - y };

		b->Create(pos, { 0,0 }, backBtnImg_, handle[i]);
		buttons_.emplace_back(b);
	}


}

void SelectScene::BattleBtnProcess(void)
{
	//�V�[���J��
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
}

void SelectScene::EditBtnProcess(void)
{
}

void SelectScene::RuleBtnProcess(void)
{
}

void SelectScene::CreditBtnProcess(void)
{
}

void SelectScene::ExitBtnProcess(void)
{
	exit(0);
}
