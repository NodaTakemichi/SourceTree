#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/DeckManager.h"
#include "../Utility/AsoUtility.h"
#include "../Utility/Button/CircleButton.h"
#include "../Utility/Button/UnitButton.h"
#include "../Utility/Button/CmdButton.h"

#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"
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
	//�w�i
	bgImg_ = LoadGraph("Data/Image/bg/EditScene_bg.png");

	//���j�b�g�J�[�h��
	unitBack_ = LoadGraph("Data/Image/UI/UnitBack.png");


	//�{�^���摜
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");

	//�o�b�N�{�^���̐���
	int sy = Application::SCREEN_SIZE_Y;
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);



	//���j�b�g
	auto& deckMng = DeckManager::GetInstance();
	auto& dataMng = UnitDataManager::GetInstance();

	//�f�b�L���j�b�g�̎擾
	for (auto& num : deckMng.GetDeck())
	{
		auto u = dataMng.GetUnitData(num);
		deck_.emplace_back(u);
	}


	//�������j�b�g�̎擾
	int no = 0;
	for (auto& num : deckMng.GetUnitPool())
	{
		//���j�b�g�f�[�^
		auto u = dataMng.GetUnitData(num);	
		//�\�����W
		Vector2 cardPos = FIRST_UNIT_POOL_POS;
		if (no < 5)
		{
			cardPos.x += OFFSET_UNIT_POOL_POS.x * no;
		}else
		{
			cardPos.x += OFFSET_UNIT_POOL_POS.x * (no - 5);
			cardPos.y += OFFSET_UNIT_POOL_POS.y;
		}
		//�{�^������
		UnitButton* ub = new UnitButton();
		ub->Create(cardPos, unitBack_, u);
		unitCards_.emplace(std::make_pair(num, ub));

		no++;
	}


	//�s�b�N�A�b�v���j�b�g
	pickUpUnit_ = -1;

	//�X�e�[�^�X���
	sFontHandle_= CreateFontToHandle("������", 20, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);
	//sFontHandle_= CreateFontToHandle("������", 22, 20,
	//	DX_FONTTYPE_ANTIALIASING_4X4);
	sFontColor_ = GetColor(230, 230, 230);

	//�A�C�R���摜
	hpIcon_ = LoadGraph("Data/Image/Icon/HP.png");
	attackIcon_ = LoadGraph("Data/Image/Icon/Attack.png");
	speedIcon_ = LoadGraph("Data/Image/Icon/Speed.png");
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

	//�{�^���X�V
	for (auto& card : unitCards_)
	{
		card.second->Update();
	}


	//���������j�b�g�J�[�h���Z�b�g
	SelectPickUpUnit();




	//���W
	if (CheckHitKey(KEY_INPUT_RIGHT))testPos.x++;
	if (CheckHitKey(KEY_INPUT_LEFT))testPos.x--;
	if (CheckHitKey(KEY_INPUT_DOWN))testPos.y++;
	if (CheckHitKey(KEY_INPUT_UP))testPos.y--;
	_dbgDrawFormatString(0, 0, 0xffffff, "���W�F{%d,%d}", testPos.x, testPos.y);
}

void EditScene::Draw(void)
{
	//�w�i
	DrawGraph(0, 0, bgImg_, true);


	//�{�^��UI
	//�}�C�f�b�L


	//���j�b�g�v�[��
	for (auto& card : unitCards_)
	{
		card.second->Draw();
	}

	//���j�b�g���
	DrawUnitStatus();

	//�ǉ��{�^��

	//�o�b�N�{�^��
	backBtn_->Draw();

#ifdef _DEBUG
	auto cx = Application::SCREEN_SIZE_X;
	auto cy = Application::SCREEN_SIZE_Y;
	auto span = 20;
	for (size_t i = 0; i < 60; i++)
	{
		//X
		DrawLine(0, i * span, cx, i * span, 0xff0000);

		//Y
		DrawLine(i * span, 0, i * span, cy, 0x0000ff);
	}
#endif // _DEBUG



}

void EditScene::Release(void)
{
	backBtn_->Release();
	delete backBtn_;
}


void EditScene::DrawUnitStatus(void)
{
	if (pickUpUnit_ == -1)return;


	//������́i�����́j�������擾
	auto l = AsoUtility::StringLength(pickUpUnitData_.name, sFontHandle_) / 2;
	//���O
	DrawStringToHandle(
		1080 - l , 80,
		pickUpUnitData_.name.c_str(), sFontColor_, sFontHandle_);

	//���j�b�g�摜
	DrawGraph(950, 120, pickUpUnitData_.imgHandle, true);

	//�X�e�[�^�X
	int noX = 0;
	int noY = 0;
	int offsetX = 140;
	int offsetY = 50;

	auto drawIcon = [&](int icon,int value) {

		Vector2 iconPos = { 960 + (offsetX * noX), 390 + (offsetY * noY) };

		DrawGraph(iconPos.x, iconPos.y, icon, true);
		DrawFormatStringToHandle(iconPos.x + 40, iconPos.y+5,
			sFontColor_, sFontHandle_, "%d", value);

		noX++;
		if (noX >= 2)
		{
			noX = 0;
			noY++;
		}

		return;
	};

	drawIcon(hpIcon_, pickUpUnitData_.hp);
	drawIcon(attackIcon_, pickUpUnitData_.attack);
	drawIcon(speedIcon_, pickUpUnitData_.speed);


	//�Z�ꗗ
	for (auto& cmdBtn : cmdBtns_)
	{
		cmdBtn->Draw();
	}

	DrawBox(testPos.x, testPos.y, 
		testPos.x+40, testPos.y+40, 0xffffff, true);

}

void EditScene::SelectPickUpUnit(void)
{
	if (pickUpUnit_ == -1)
	{
		for (auto& card : unitCards_)
		{
			if (!card.second->ButtonDecision())continue;

			pickUpUnit_ = card.first;


			//�e�f�[�^�̎擾
			auto& dataMng = UnitDataManager::GetInstance();
			pickUpUnitData_ = dataMng.GetUnitData(pickUpUnit_);
			//�R�}���h�{�^���̐���
			int noX, noY;
			noX = noY = 0;
			Vector2 size = { 160,40 };
			for (auto& cmd : pickUpUnitData_.cmdNum)
			{
				CmdButton* b = new CmdButton();

				//���W����
				Vector2 pos = { testPos.x + size.x * noX, testPos.y + size.y * noY };
				b->Create(pos, size, cmd);
				cmdBtns_.push_back(b);

				//���W���炵
				noY++;
				if (noY >= 4)
				{
					noY = 0;
					noX++;
				}
			}
			return;
		}
	}

	for (auto& card : unitCards_)
	{
		if (!card.second->ButtonDecision())continue;
		
		pickUpUnit_ = card.first;


		//�e�f�[�^�̎擾
		auto& dataMng = UnitDataManager::GetInstance();
		pickUpUnitData_ = dataMng.GetUnitData(pickUpUnit_);
		//�R�}���h�̃Z�b�g
		int n = 0;
		for (auto& cmd : pickUpUnitData_.cmdNum)
		{
			cmdBtns_[n]->SetCmd(cmd);
			n++;
		}


		return;
	}
}
