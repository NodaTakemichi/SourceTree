#include<DxLib.h>
#include "../../../Manager/SceneManager.h"

#include"../../../_debug/_DebugConOut.h"

#include "UnitUI.h"

UnitUI::UnitUI(Vector2 pos, std::string& name,
	int& hp, int& maxHp, int& beforHp) :
	unitPos_(pos), name_(name), hp_(hp), maxHp_(maxHp), beforHp_(beforHp)
{
}

UnitUI::~UnitUI()
{
}

void UnitUI::Init(void)
{
	//���O�g�̓o�^
	nameFrameImg_ = LoadGraph("./Data/Image/UI/NameFrame.png");

	//�V�F�[�_�[�̓o�^
	//psHpColor_ = LoadPixelShader("./Data/Shader/HpShader.cso");
	psHpColor_ = LoadPixelShader("./x64/Debug/HpShader.cso");
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psHpColorConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 8);

	//���v����
	totalTime_ = 0.0f;

	//�e�X�g
	icon_[0] = LoadGraph("./Data/Image/Icon/���.png");
	icon_[1] = LoadGraph("./Data/Image/Icon/��.png");
	icon_[2] = LoadGraph("./Data/Image/Icon/����.png");
	icon_[3] = LoadGraph("./Data/Image/Icon/Avoidance.png");
	icon_[4] = LoadGraph("./Data/Image/Icon/A_UP.png");
	icon_[5] = LoadGraph("./Data/Image/Icon/A_DOWN.png");
	icon_[6] = LoadGraph("./Data/Image/Icon/S_UP.png");
	icon_[7] = LoadGraph("./Data/Image/Icon/S_DOWN.png");
	icon_[8] = LoadGraph("./Data/Image/Icon/D_UP.png");
	icon_[9] = LoadGraph("./Data/Image/Icon/D_DOWN.png");

}

void UnitUI::Draw(void)
{

}

void UnitUI::Release(void)
{
	DeleteGraph(nameFrameImg_);

	//�V�F�[�_�[�̉��
	DeleteShader(psHpColor_);
	DeleteShaderConstantBuffer(psHpColorConstBuf_);
}

void UnitUI::SetBuff(std::vector<Buff*> buffs)
{
	buffs_ = buffs;
}

void UnitUI::DrawHpShader(const float& ratio, const COLOR_F& color)
{
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(psHpColor_);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psHpColorConstBuf_;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = color.r;
	cbBuf->g = color.g;
	cbBuf->b = color.b;
	cbBuf->a = color.a;
	cbBuf++;
	cbBuf->r = ratio;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�`��
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

}

void UnitUI::DecHpGauge(void)
{
	auto changeTime = 1.0f;		//��������

	//HP�ω�������Ƃ��̂�
	if (nowHp_ != hp_)
	{
		//�o�ߎ���
		totalTime_ += SceneManager::GetInstance().GetDeltaTime();
		//�o�߁@���i�������鎞�ԁ[�o�ߎ��ԁj/�������鎞��
		auto progress = 1.0f - (changeTime - totalTime_) / changeTime;

		//�_���[�W��ƃ_���[�W�O�̐��`��Ԃ��s��
		nowHp_ = AsoUtility::Lerp(beforHp_, hp_, progress);

		//���߂��Ă���A��������HP������HP�ɒǂ�������
		if (progress >= 1.0f || nowHp_ == hp_)
		{
			totalTime_ = 0.0f;
		}
	}
}

void UnitUI::DrawHpFrame(const Vector2& pos)
{
	//HP�t���[���̕`��
	auto frame = 2;
	DrawBox(pos.x - frame, pos.y - frame,
		pos.x + HP_GAUGE_X + frame, pos.y + HP_GAUGE_Y + frame,
		0xffffff, true);
}

void UnitUI::DrawName(const std::string& name, const Vector2& uPos)
{
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 fPos = { uPos.x - 10,uPos.y + 140 };
	Vector2 nPos = { uPos.x + unitSize / 2,uPos.y + 152 };

	//���O�g�̕\��
	DrawGraph(fPos.x, fPos.y, nameFrameImg_, true);

	//���O�@������
	auto n = name.c_str();
	//������̕������̎擾
	int len = strlen(n);
	//������́i�����́j�������擾
	auto fx = GetDrawStringWidth(n, len) / 2;
	//���O�`��
	DrawString(nPos.x - fx, nPos.y, n, 0xffffff);

}

void UnitUI::DrawBuffIcon()
{
	//�o�t�A�C�R���̕`��
	int i = 0;
	for (auto& buff : buffs_)
	{
		if(!buff->IsAlive())continue;

		int num = 0;
		switch (buff->GetBuff())
		{
		case Buff::BUFF_TYPE::PALALYSIS:
			num = 0;
			break;
		case Buff::BUFF_TYPE::POISON:
			num = 1;
			break;
		case Buff::BUFF_TYPE::CONFUSION:
			num = 2;
			break;
		case Buff::BUFF_TYPE::AVOIDANCE:
			num = 3;
			break;

		case Buff::BUFF_TYPE::A_UP:
			num = 4;
			break;
		case Buff::BUFF_TYPE::A_DOWN:
			num = 5;
			break;
		case Buff::BUFF_TYPE::S_UP:
			num = 6;
			break;
		case Buff::BUFF_TYPE::S_DOWN:
			num = 7;
			break;
		case Buff::BUFF_TYPE::D_UP:
			num = 8;
			break;
		case Buff::BUFF_TYPE::D_DOWN:
			num = 9;
			break;

		default:
			return;
		}

		//�o�C���j�A��ԃ��[�h
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		int s = 32;
		Vector2 iPos = { unitPos_.x + (i * 36) + 10, unitPos_.y + 130 };
		DrawExtendGraph(iPos.x, iPos.y, iPos.x + s, iPos.y + s, icon_[num], true);
		i++;

		//�l�A���X�g�l�C�o�[�@
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
}

void UnitUI::MakeSquereVertex(Vector2 pos)
{
	//�O�p�`�̃|���S����2����āA�������Ă���

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + HP_GAUGE_X - 1);
	float eY = static_cast<float>(pos.y + HP_GAUGE_Y - 1);

	// �S���_�̏�����
	for (int i = 0; i < 4; i++)
	{
		mVertex[i].rhw = 1.0f;
		mVertex[i].dif = GetColorU8(255, 255, 255, 255);
		mVertex[i].spc = GetColorU8(255, 255, 255, 255);
		mVertex[i].su = 0.0f;
		mVertex[i].sv = 0.0f;
	}

	// ����
	mVertex[cnt].pos = VGet(sX, sY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// �E��
	mVertex[cnt].pos = VGet(eX, sY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// �E��
	mVertex[cnt].pos = VGet(eX, eY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 1.0f;
	cnt++;

	// ����
	mVertex[cnt].pos = VGet(sX, eY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 1.0f;

	/*
	�@�`�`�`�`�`�`
		0-----1
		|     |
		|     |
		3-----2
	�@�`�`�`�`�`�`
		0-----1
		|  �^
		|�^
		3
	�@�`�`�`�`�`�`
			  1
		   �^ |
		 �^   |
		3-----2
	�@�`�`�`�`�`�`
	*/


	// ���_�C���f�b�N�X
	cnt = 0;
	mIndex[cnt++] = 0;
	mIndex[cnt++] = 1;
	mIndex[cnt++] = 3;

	mIndex[cnt++] = 1;
	mIndex[cnt++] = 2;
	mIndex[cnt++] = 3;

}


