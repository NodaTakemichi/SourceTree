#include "../../Application.h"
#include "./UI//EnemyUI.h"
#include "EnemyUnit.h"

EnemyUnit::EnemyUnit()
{
}

EnemyUnit::EnemyUnit(std::string unitFile, int unitNum)
{
	unitFile_ = unitFile;
	unitNum_ = unitNum;

	type_ = UNIT_TYPE::ENEMY;

}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::Init(void)
{
	//���j�b�g�f�[�^�̃��[�h
	LoadData(unitFile_.c_str());

	//���W������
	auto ScreenX = Application::SCREEN_SIZE_X;
	SetDrawingPos(ScreenX - DRAWING_SIZE - DRAWING_OFFSET_X);

	//UI���̏�����
	unitUi_ = new EnemyUI(pos_, name_, nowHp_, maxHp_);
	unitUi_->Init();


	//������
	UnitBase::Init();

}


void EnemyUnit::Update(void)
{
}

void EnemyUnit::Draw(void)
{
	//�o�C���j�A��ԃ��[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//�V�F�[�_�[�`��
	DrawUnitShader(nowPs_, 0.0f);

	//�l�A���X�g�l�C�o�[�@
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//UI�`��
	unitUi_->Draw();

	//�x�[�X���j�b�g�̕`��֐�
	UnitBase::Draw();

}


