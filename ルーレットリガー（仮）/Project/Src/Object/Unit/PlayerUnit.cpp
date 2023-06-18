#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#include "./UI/PlayerUI.h"
#include "PlayerUnit.h"

PlayerUnit::PlayerUnit()
{
}

PlayerUnit::PlayerUnit(std::string unitFile,int unitNum)
{
	unitFile_ = unitFile;
	unitNum_ = unitNum;

	type_ = UNIT_TYPE::PLAYER;
}

PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::Init(void)
{
	//���j�b�g�f�[�^�̃��[�h
	LoadData(unitFile_.c_str());

	//���W������
	SetDrawingPos(DRAWING_OFFSET_X);


	//UI���̏�����
	unitUi_ = new PlayerUI(pos_, name_, hp_ ,nowHp_, maxHp_);
	unitUi_->Init();

	//������
	UnitBase::Init();
	
}

void PlayerUnit::Update(void)
{
	//if (CheckHitKey(KEY_INPUT_UP))pos_.y -= 1;
	//if (CheckHitKey(KEY_INPUT_DOWN))pos_.y += 1;
	//if (CheckHitKey(KEY_INPUT_LEFT))pos_.x -= 1;
	//if (CheckHitKey(KEY_INPUT_RIGHT))pos_.x += 1;
	//
	//_dbgDrawFormatString(0.0f, 150.0f, 0xff00ff, "{%d,%d}", pos_.x, pos_.y);


}

void PlayerUnit::Draw(void)
{

	//���j�b�g�摜�`��
	DrawUnitShader(1.0f);


	//UI�`��
	unitUi_->Draw();

	//�x�[�X���j�b�g�̕`��֐�
	UnitBase::Draw();

}


