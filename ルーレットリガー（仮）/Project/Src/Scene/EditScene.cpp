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
	unitBackImg_ = LoadGraph("Data/Image/UI/UnitBack.png");

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
	int noDeck = 0;
	for (auto& num : deckMng.GetDeck())
	{
		//���j�b�g�f�[�^
		auto u = dataMng.GetUnitData(num);	
		//�\�����W
		Vector2 cardPos = FIRST_UNIT_DECK_POS;
		cardPos.x += OFFSET_UNIT_DECK_POS * noDeck;

		//�{�^������
		UnitButton* ub = new UnitButton();
		ub->Create(cardPos, unitBackImg_, u);
		deck_.emplace(std::make_pair(num, ub));

		noDeck++;
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
		ub->Create(cardPos, unitBackImg_, u);
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
	
	//�y�[�W
	page_ = 1;
}

void EditScene::Update(void)
{
	//�o�b�N����
	if (backBtn_->ButtonDecision())
	{
		//�f�b�L�̊m��
		DeckDecision();
		//�V�[���J��
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::SELECT, true);
	}

	//�{�^���X�V
	//�o�b�N�{�^��
	backBtn_->Update();
	//�f�b�L
	for (auto& deck : deck_)
	{
		deck.second->Update();
	}
	//���j�b�g�J�[�h�v�[��
	for (auto& card : unitCards_)
	{
		card.second->Update();
	}


	//�f�b�L�ҏW����
	DeckEditProcess();
	//���������j�b�g�J�[�h���Z�b�g
	SelectPickUpUnit();

}

void EditScene::Draw(void)
{
	//�w�i
	DrawGraph(0, 0, bgImg_, true);


	//�{�^��UI
	//�}�C�f�b�L
	for (auto& deck : deck_)
	{
		deck.second->Draw();
	}
	//���j�b�g�v�[��
	for (auto& card : unitCards_)
	{
		card.second->Draw();
	}

	//���j�b�g���
	DrawUnitStatus();


	//�o�b�N�{�^��
	backBtn_->Draw();

}

void EditScene::Release(void)
{
	//�摜�̉��
	DeleteGraph(bgImg_);
	DeleteGraph(unitBackImg_);
	DeleteGraph(backImg_);

	DeleteGraph(hpIcon_);
	DeleteGraph(attackIcon_);
	DeleteGraph(speedIcon_);

	DeleteFontToHandle(sFontHandle_);

	for (auto& du : deck_)
	{
		du.second->Release();
		delete du.second;
	}
	deck_.clear();

	for (auto& cu : unitCards_)
	{
		cu.second->Release();
		delete cu.second;
	}
	unitCards_.clear();


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
}

void EditScene::DeckEditProcess(void)
{
	if (pickUpUnit_ == -1)return;

	//�s�b�N�A�b�v���j�b�g���Z�b�g����
	for (auto& deck : deck_)
	{
		if (!deck.second->ButtonDecision())continue;

		//�f�b�L�ɓ������j�b�g�����݂�����A�X�L�b�v
		auto u = deck_.find(pickUpUnit_);
		if (u != deck_.end())
		{
			return;
		}

		//�Â��L�[�̒l���擾
		UnitButton* c = deck_[deck.first];
		//�폜
		deck_.erase(deck.first);

		//�{�^���̃f�[�^�X�V
		c->ChengeUnitData(pickUpUnitData_);

		//�V�����L�[�ŗv�f��ǉ�
		deck_[pickUpUnit_] = c;

		return;
	}
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
			Vector2 size = { 163,40 };
			Vector2 posBase = { 915, 500 };
			for (auto& cmd : pickUpUnitData_.cmdNum)
			{
				CmdButton* b = new CmdButton();

				//���W����
				Vector2 pos = { posBase.x + size.x * noX, posBase.y + size.y * noY };
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

void EditScene::DeckDecision(void)
{
	auto& dMng = DeckManager::GetInstance();
	std::vector<int>  num;
	for (auto& deck : deck_)
	{
		num.push_back(deck.first);
	}
	dMng.SetDeck({ num[0],num[1],num[2] });
}
