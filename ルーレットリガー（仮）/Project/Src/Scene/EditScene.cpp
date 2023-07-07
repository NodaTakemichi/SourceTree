#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/DeckManager.h"
#include "../Manager/DataManager/UnitDataManager.h"
#include "../Utility/Button/CircleButton.h"

#include "../Utility/Button/UnitButton.h"
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

	//���j�b�g�J�[�h��
	unitBack_ = LoadGraph("Data/Image/UI/UnitBack.png");

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

	//�摜�̓o�^
	bgImg_ = LoadGraph("Data/Image/bg/EditScene_bg.png");
	//editFrameImg_ = LoadGraph("");

	//�{�^���摜
	backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");
	int sy = Application::SCREEN_SIZE_Y;

	//�o�b�N�{�^���̐���
	backBtn_ = new CircleButton();
	backBtn_->Create({ 0,sy }, backImg_, -1);

	//�s�b�N�A�b�v���j�b�g
	pickUpUnit_ = -1;

	
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


	//�������J�[�h�ԍ����Z�b�g
	SelectPickUpUnit();



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

#ifdef DEBUG
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

	//���j�b�g���̎擾
	auto& dataMng = UnitDataManager::GetInstance();
	auto& unit = dataMng.GetUnitData(pickUpUnit_);

	//���O
	DrawString(900, 100, unit.name.c_str(), 0xffffff);

	//���j�b�g�摜
	DrawGraph(900, 250, unit.imgHandle, true);

	//�X�e�[�^�X
	DrawFormatString(900, 530, 0xffffff,"HP:%d",unit.hp);
	DrawFormatString(900, 546, 0xffffff,"P :%d",unit.attack);
	DrawFormatString(900, 562, 0xffffff,"D :%d",unit.speed);

	//�Z�ꗗ

}

void EditScene::SelectPickUpUnit(void)
{
	for (auto& card : unitCards_)
	{
		if (!card.second->ButtonDecision())continue;
		
		pickUpUnit_ = card.first;
	}
}
