#include "EnemyUI.h"

EnemyUI::EnemyUI(
	Vector2 pos, std::string& name, int& hp, int& nowHp, int& maxHp, bool& active) :
	UnitUI(pos, name, hp, nowHp, maxHp,active)
{
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::Init(void)
{
	//������
	UnitUI::Init();

}

void EnemyUI::Draw(void)
{
	COLOR_F color = { 0.8f,0.4f,0.4f,1.0f };	//��

	//���O�`��
	DrawName(name_, unitPos_, color);


	//HP��0�ȉ��̎��AHP�Q�[�W��`�悵�Ȃ�
	if (nowHp_ <= 0)return;


	//�o�t�A�C�R���̕`��
	DrawBuffIcon();


	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	//HP�g�̕\��
	Vector2 pos = { unitPos_.x + unitSize + 50 ,unitPos_.y + 20 };
	DrawHpFrame(pos);

	//HP�V�F�[�_�[
	pos = { unitPos_.x + unitSize + 50 , unitPos_.y + 20 };
	DrawHpShader(pos,color);

	//�`��
	UnitUI::Draw();

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
	Vector2 pos = { unitPos_.x - 100,unitPos_.y + unitSize / 4 };
	DrawGraph(pos.x, pos.y, targetImg_, true);
}
