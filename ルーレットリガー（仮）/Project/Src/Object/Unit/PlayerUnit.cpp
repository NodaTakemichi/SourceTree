#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#include "./UI/PlayerUI.h"
#include "PlayerUnit.h"


PlayerUnit::PlayerUnit(const int& dataNum, const int& unitNum) :
	UnitBase(dataNum, unitNum)
{
	type_ = UNIT_TYPE::PLAYER;
}


PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::Init(void)
{
	//���W������
	SetDrawingPos(DRAWING_OFFSET_X);


	//UI���̏�����
	unitUi_ = new PlayerUI(pos_, name_, hp_ ,changeHp_, maxHp_, isAct_);
	unitUi_->Init();

	//������
	UnitBase::Init();
	
}

void PlayerUnit::Update(void)
{

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


