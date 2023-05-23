#include "EnemyUI.h"

EnemyUI::EnemyUI(
	Vector2 pos, std::string& name,int& nowHp, int& maxHp) :
	UnitUI(pos, name, nowHp, maxHp)
{
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::Init(void)
{
	//������
	UnitUI::Init();


	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	//HP�\�����W
	Vector2 pos = { unitPos_.x + unitSize + 50 , unitPos_.y + 20 };
	//�l�p�`�|���S���̐���(HP�p)
	MakeSquereVertex(pos);
}

void EnemyUI::Draw(void)
{
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);


	//���O�`��
	DrawName(name_, unitPos_);


	//HP��0�ȉ��̎��AHP�Q�[�W��`�悵�Ȃ�
	if (nowHp_ <= 0)return;


	//�o�t�A�C�R���̕`��
	DrawBuffIcon();


	//HP�g�̕\��
	Vector2 pos = { unitPos_.x + unitSize + 50 ,unitPos_.y + 20 };
	DrawHpFrame(pos);
	//HP�̐��l�\��
	DrawFormatString(
		pos.x - HP_GAUGE_X-10, pos.y + HP_GAUGE_Y - 32,
		0xffffff, "HP\n%d", nowHp_);

	//HP�̊���
	float ratio = static_cast<float>(nowHp_) / static_cast<float>(maxHp_);
	//HP�V�F�[�_�[
	COLOR_F color = { 0.8f,0.4f,0.4f,1.0f };
	DrawHpShader(ratio, color);

}

void EnemyUI::DrawActUnit(void)
{
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 pos = { unitPos_.x - 20,unitPos_.y + unitSize / 2 };
	DrawCircle(pos.x, pos.y, 12, 0xff8888, true);
}

void EnemyUI::DrawRockOn(void)
{
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 pos = { unitPos_.x - 20,unitPos_.y + unitSize / 2 + 20 };
	DrawCircle(pos.x, pos.y, 12, 0x8888ff, true);

}
