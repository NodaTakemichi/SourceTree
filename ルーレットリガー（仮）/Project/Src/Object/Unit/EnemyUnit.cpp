#include "../../Application.h"
#include "./UI//EnemyUI.h"
#include "EnemyUnit.h"



EnemyUnit::EnemyUnit(const int& dataNum, const int& unitNum) :
	UnitBase(dataNum, unitNum)
{
	type_ = UNIT_TYPE::ENEMY;
}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::Init(void)
{
	//���W������
	auto ScreenX = Application::SCREEN_SIZE_X;
	SetDrawingPos(ScreenX - DRAWING_SIZE - DRAWING_OFFSET_X);

	//UI���̏�����
	unitUi_ = new EnemyUI(pos_, name_, hp_ ,changeHp_, maxHp_, isAct_);
	unitUi_->Init();


	//������
	UnitBase::Init();

}


void EnemyUnit::Update(void)
{
}

void EnemyUnit::Draw(void)
{
	//���j�b�g�摜�`��
	DrawUnitShader(0.0f);

	//UI�`��
	unitUi_->Draw();

	//�x�[�X���j�b�g�̕`��֐�
	UnitBase::Draw();

}


