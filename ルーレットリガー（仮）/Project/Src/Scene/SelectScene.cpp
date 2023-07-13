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
#include "../Utility/Button/CircleButton.h"


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
	//�{�^���摜
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");

	//�o�b�N�{�^���̐���
	int sy = Application::SCREEN_SIZE_Y + 20;
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);


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
	CreateModeBtn();

	//���[�h
	ChangeSelectMode(SELECT_MODE::MAX);

	//�o�g��������̓o�^
	BattleEnemyInit();

}

void SelectScene::Update(void)
{

	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	totalTime_ += delta;

	//�����܍��W
	shakeY_ = sinf(totalTime_) * 30.0f;

	//�e���[�h�{�^���X�V
	BtnProcess();


	//�o�b�N�{�^��
	backBtn_->Update();
	if (backBtn_->ButtonDecision())
	{
		//�O�t�F�[�Y�ɖ߂�

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

	//���[�h�{�^��
	for (auto& btn : modeBtn_)
	{
		btn.second.btn->Draw();
	}

	//�Z���N�g���[�h�摜
	if (mode_ != SELECT_MODE::MAX)DrawGraph(700, 300, modeBtn_.at(mode_).modeImg, true);
	


	//���[�h�{�b�N�X�`��
	DrawModeBox();

	//�R�����g�{�b�N�X
	DrawCmtBox();

	//�o�b�N�{�^��
	backBtn_->Draw();


#ifdef DEBUG
	auto span = 50;
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
	DeleteGraph(modeBtnImg_);

	backBtn_->Release();
	delete backBtn_;
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
		0xdddddd, modeFontHandle_, nowMode_.c_str());
}

void SelectScene::DrawCmtBox(void)
{
	DrawGraph(cmtPos_.x, cmtPos_.y, cmtBox_, true);

	Vector2 offset = { cmtPos_.x + 40,cmtPos_.y + 40 };
	DrawFormatStringToHandle(
		offset.x, offset.y,
		0xdddddd, cmtFontHandle_, devilCmt_.c_str());

}

void SelectScene::BtnProcess()
{

	//�{�^���X�V
	for (auto& btn : modeBtn_)
	{
		btn.second.btn->Update();
	}


	//�{�^���F�}�E�X���{�^����ɂ��邩���f
	for (auto& btn : modeBtn_)
	{
		if (btn.second.btn->MouseOnButton())
		{
			ChangeSelectMode(btn.first);
		}
	}


	//�{�^���F�N���b�N����
	for (auto& btn : modeBtn_)
	{
		if (!btn.second.btn->ButtonDecision())continue;

		//�{�^���������ꂽ�ꍇ�A���̃{�^���������s��
		SelectBtnProcess();
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

void SelectScene::CreateModeBtn(void)
{
	//�X�N���[���T�C�Y
	auto& sx = Application::SCREEN_SIZE_X;
	auto& sy = Application::SCREEN_SIZE_Y;

	//���[�h�{�^���̔w�ʉ摜
	modeBtnImg_ = LoadGraph("./Data/Image/UI/ModeBtnImg.png");
	int btnSizeX, btnSizeY;
	GetGraphSize(modeBtnImg_, &btnSizeX, &btnSizeY);


	std::string path = "Data/Image/UI/";
	int n = 0;
	// �{�^�����������_
	auto createBtn = [&](SELECT_MODE mode, std::string btnImgPath, std::string modeImgPath) {

		//���[�h�摜
		std::string fileName = path + modeImgPath;
		int modeImg = LoadGraph(fileName.c_str());

		//���W
		Vector2 pos = {
			(sx / 2) - (btnSizeX * 2) - (btnSizeX / 2) + (btnSizeX * n)  ,
			sy - btnSizeY };
		//�{�^���摜
		fileName = path + btnImgPath;
		int btnImg = LoadGraph(fileName.c_str());

		//�{�^������
		RectButton* b = new RectButton();
		b->Create(pos, { 0,0 }, modeBtnImg_, btnImg);

		//�}��
		ModeData md = { modeImg,b };
		modeBtn_.emplace(std::make_pair(mode, md));

		n++;
	};


	createBtn(SELECT_MODE::BATTLE,		"�o�g��.png",		"Select/Mode_Battle.png");
	createBtn(SELECT_MODE::DECK_EDIT,	"�f�b�L�ҏW.png",	"Select/Mode_DeckEdit.png");
	createBtn(SELECT_MODE::RULE_BOOK,	"���[���u�b�N.png", "");
	createBtn(SELECT_MODE::CREDIT,		"�N���W�b�g.png",	"");
	createBtn(SELECT_MODE::TITLE,		"�ޏo.png",			"Select/Mode_Title.png");
}

void SelectScene::SelectBtnProcess(void)
{
	switch (mode_)
	{
	case SelectScene::SELECT_MODE::BATTLE:
		BattleBtnProcess();
		break;
	case SelectScene::SELECT_MODE::DECK_EDIT:
		EditBtnProcess();
		break;
	case SelectScene::SELECT_MODE::RULE_BOOK:
		RuleBtnProcess();
		break;
	case SelectScene::SELECT_MODE::CREDIT:
		CreditBtnProcess();
		break;
	case SelectScene::SELECT_MODE::TITLE:
		TitleBtnProcess();
		break;
	case SelectScene::SELECT_MODE::MAX:
		break;
	default:
		break;
	}
}

void SelectScene::ChangeSelectMode(const SELECT_MODE& mode)
{
	//�����������ꍇ�A�������Ȃ�
	if (mode_ == mode)return;

	mode_ = mode;

	//������炷

	switch (mode_)
	{
	case SelectScene::SELECT_MODE::BATTLE:
		SetDevilCmt("�����X�^�[���m���킹�郂�[�h����");

		break;
	case SelectScene::SELECT_MODE::DECK_EDIT:
		SetDevilCmt("��킹�郆�j�b�g��I�ׂ邺");

		break;
	case SelectScene::SELECT_MODE::RULE_BOOK:
		SetDevilCmt("���݁A�J�����ł�");

		break;
	case SelectScene::SELECT_MODE::CREDIT:
		SetDevilCmt("���݁A�J�����ł�");

		break;
	case SelectScene::SELECT_MODE::TITLE:
		SetDevilCmt("�^�C�g���ɖ߂邺�B");

		break;
	case SelectScene::SELECT_MODE::MAX:
		break;
	default:
		break;
	}
}

void SelectScene::SetDevilCmt(const std::string& cmt)
{
	devilCmt_ = cmt;
}

void SelectScene::BattleEnemyInit(void)
{
	//�G�l�~�[�̓o�^
	auto regEnemys = [&](SELECT_STAGE stage, std::array<int, 3> nums) {
		enemys_.emplace(std::make_pair(stage, nums));
	};

	//�X
	regEnemys(SELECT_STAGE::FOREST, { 0,1,2 });
	regEnemys(SELECT_STAGE::FOREST, { 0,1,2 });
	regEnemys(SELECT_STAGE::FOREST, { 0,1,2 });

}


