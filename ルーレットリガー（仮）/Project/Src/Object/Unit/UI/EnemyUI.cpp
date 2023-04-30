#include "EnemyUI.h"

EnemyUI::EnemyUI(Vector2 pos, std::string* name):
unitPos_(pos), name_(name)
{
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::Init(void)
{
	//������
	UnitUI::Init();

	//HP���W
	Vector2 pos;
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);

	hpFrameImg_ = LoadGraph("./Data/Image/UI/HP_E.png");
	pos = { unitPos_.x + unitSize - 10, unitPos_.y + 20 };


	//�l�p�`�|���S���̐���(HP�p)
	MakeSquereVertex(pos);

}

void EnemyUI::Draw(void)
{
	//���j�b�g�̃T�C�Y
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);

	//HP�̕\��
	Vector2 pos = { unitPos_.x + unitSize - 10,unitPos_.y + 20 };
	//HP�̘g
	auto frame = 2;
	DrawBox(pos.x - frame, pos.y - frame,
		pos.x + HP_GAUGE_X + frame, pos.y + HP_GAUGE_Y + frame,
		0xffffff, true);


#pragma region HP�V�F�[�_�[
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psHpColor_);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psHpColorConstBuf_;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 0.7f;
	cbBuf->g = 0.3f;
	cbBuf->b = 0.3f;
	cbBuf->a = 1.0f;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�`��
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
#pragma endregion

#pragma region ���O
	//���O�̕\��
	pos = { unitPos_.x - 10,unitPos_.y + 140 };
	DrawTurnGraph(pos.x, pos.y, nameFrameImg_, true);

	//���O�@������
	auto name = name_->c_str();
	//������̕������̎擾
	int len = strlen(name);
	//������́i�����́j�������擾
	auto fx = GetDrawStringWidth(name, len) / 2;
	pos = { unitPos_.x + unitSize / 2,unitPos_.y + 152 };
	//���O�`��
	DrawString(pos.x - fx, pos.y, name, 0xffffff);
#pragma endregion

}

void EnemyUI::Release(void)
{
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
