#include <DxLib.h>
#include <cstdlib>
#include "../Application.h"
#include "../Manager/DataManager/BattleDataManager.h"
#include "../Manager/DeckManager.h"
#include "../Manager/DataManager/SoundManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Common/Vector2.h"

#include "../Utility/AsoUtility.h"
#include "../Utility/DrawShader.h"
#include "../Utility/Button/RectButton.h"

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
	bgImg_ = LoadGraph("Data/Image/bg/select.jpg");

	modeBox_ = LoadGraph("Data/Image/UI/ModeBox.png");
	cmtBox_ = LoadGraph("Data/Image/UI/CommentBox.png");


	//���[�h�{�b�N�X
	modePos_ = { 0,0 };
	nowMode_ = "MODE SELECT";
	modeFontHandle_ = CreateFontToHandle("������", 50, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);

	//�R�����g�{�b�N�X
	cmtPos_ = { 0, 470 };
	SetDevilCmt("���[�h��I�����Ă����ȁI");
	cmtFontHandle_ = CreateFontToHandle("������", 20, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);


	//������
	devilImg_ = LoadGraph("Data/Image/UI/������_���J��.png");
	devilPos_ = { 0,100 };
	shakeY_ = 0;

	//�V�F�[�_�[�o�^
	//���]�L��`��
	psTex_ = LoadPixelShader("x64/Debug/ReverseTexture.cso");

	//�{�^��UI����
	CerateBtnUI();

}

void SelectScene::Update(void)
{

	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//�����܍��W
	shakeY_ = sinf(totalTime_) * 30.0f;

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

	//���[�h�{�^��
	for (auto& btn : buttons_)
	{
		btn->Draw();
	}

	//���[�h�{�b�N�X�`��
	DrawModeBox();

	//�R�����g�{�b�N�X
	DrawCmtBox();


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

	if (buttons_[1]->ButtonDecision())
	{
		EditBtnProcess();
	}

	if (buttons_[4]->ButtonDecision())
	{
		TitleBtnProcess();
	}

}

void SelectScene::CerateBtnUI(void)
{
	//�X�N���[���T�C�Y
	auto& sx = Application::SCREEN_SIZE_X;
	auto& sy = Application::SCREEN_SIZE_Y;

	//���[�h�{�^���̔w�ʉ摜
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
		RectButton* b = new RectButton();

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
	//�f�b�L�̃Z�b�g
	auto deck = DeckManager::GetInstance().GetDeck();
	std::array<int, 3> enemys = { 1,2,3 };
	BattleDataManager::GetInstance().SetBattleData({
		deck,enemys,0,0 });


	//�V�[���J��
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME, true);
}

void SelectScene::EditBtnProcess(void)
{
	//�V�[���J��
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::DECK_EDIT, true);
}

void SelectScene::RuleBtnProcess(void)
{
}

void SelectScene::CreditBtnProcess(void)
{
}

void SelectScene::TitleBtnProcess(void)
{
	//�V�[���J��
	SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE, true);
}

void SelectScene::DrawModeBox(void)
{
	DrawGraph(modePos_.x, modePos_.y, modeBox_, true);
	int x, y;
	GetGraphSize(modeBox_, &x, &y);

	auto len = AsoUtility::StringLength(nowMode_, modeFontHandle_) / 2;
	DrawFormatStringToHandle(
		modePos_.x + (x / 2) - len, 
		modePos_.y + 60, 
		0xdddddd,modeFontHandle_, nowMode_.c_str());
}

void SelectScene::DrawCmtBox(void)
{
	DrawGraph(cmtPos_.x, cmtPos_.y, cmtBox_, true);

	Vector2 offset = { cmtPos_.x + 40,cmtPos_.y + 40 };
	DrawFormatStringToHandle(
		offset.x, offset.y,
		0xdddddd, cmtFontHandle_, devilCmt_.c_str());

}

void SelectScene::SetDevilCmt(const std::string& cmt)
{
	devilCmt_ = cmt;
}
