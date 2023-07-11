#include<DxLib.h>
#include"../../../_debug/_DebugConOut.h"
#include"../../../Manager/SceneManager.h"
#include"../../../Utility/AsoUtility.h"
#include"../../../Utility/DrawShader.h"

#include "UnitUI.h"

UnitUI::UnitUI(
	Vector2 pos, std::string& name, int& hp, int& nowHp, int& maxHp) :
	unitPos_(pos), name_(name), hp_(hp), nowHp_(nowHp), maxHp_(maxHp)
{
}

UnitUI::~UnitUI()
{
}

void UnitUI::Init(void)
{
	//���O�g,�^�[�Q�b�g�摜�̓o�^
	nameFrameImg_ = LoadGraph("./Data/Image/UI/NameFrame.png");
	targetImg_ = LoadGraph("./Data/Image/UI/target.png");

	//�V�F�[�_�[�̓o�^
	psTextrue_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");
	psHpColor_ = LoadPixelShader("./x64/Debug/HpShader.cso");
	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psHpColorConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 8);

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

	//�_���[�W�t���[���摜
	dmgFrameImg_= LoadGraph("./Data/Image/UI/DmgNum2.png");
	//�_���[�W�`��
	dmgNumDrawing_ = false;	//�_���[�W�� true:�\�� , false:��\��

	//�_���[�W�t�H���g
	dmgFontHandle_ = CreateFontToHandle("��S�V�b�N", 40, 20, -1,
		DX_FONTTYPE_ANTIALIASING_4X4);
	//�񕜃t�H���g
	healFontHandle_ = CreateFontToHandle("Noto Serif JP Medium", 40, 20, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);
	//���j�b�g�t�H���g
	unitFontHandle_ = CreateFontToHandle("Noto Serif JP Medium", 18, 20, -1,
		DX_FONTTYPE_ANTIALIASING_4X4);

}

void UnitUI::Draw(void)
{
	//�_���[�W���l�̕\��
	if (dmgNumDrawing_)
	{
		DrawGraph(unitPos_.x - 50, unitPos_.y, dmgFrameImg_, true);
		//���l
		DrawFormatStringToHandle(
			unitPos_.x ,
			unitPos_.y + 25,
			0xff0000, dmgFontHandle_,
			"%d", dmg_);
	}
}

void UnitUI::Release(void)
{
	DeleteGraph(nameFrameImg_);
	DeleteGraph(targetImg_);
	DeleteGraph(dmgFrameImg_);

	//�V�F�[�_�[�̉��
	DeleteShader(psHpColor_);
	DeleteShaderConstantBuffer(psHpColorConstBuf_);
}

void UnitUI::SetBuff(std::vector<Buff*> buffs)
{
	buffs_ = buffs;
}

void UnitUI::SetDmg(const bool& drawing, const int& dmg)
{
	dmgNumDrawing_ = drawing;
	dmg_ = dmg;

	return;
}

void UnitUI::DrawHpShader(const Vector2& pos , const COLOR_F& color)
{
	//HP�̊���
	float nowRatio = static_cast<float>(nowHp_) / static_cast<float>(maxHp_);
	float hpRatio = static_cast<float>(hp_) / static_cast<float>(maxHp_);
	COLOR_F subBuf = COLOR_F{
		nowRatio,
		hpRatio
	};

	//�`��
	DrawShader::GetInstance().DrawExtendGraphToShader(
		pos, { HP_GAUGE_X ,HP_GAUGE_Y }, -1, psHpColor_, color, subBuf
	);

}

void UnitUI::DrawHpFrame(const Vector2& pos)
{
	//HP�t���[���̕`��
	auto frame = 1;
	DrawBox(pos.x - frame, pos.y - frame,
		pos.x + HP_GAUGE_X + frame, pos.y + HP_GAUGE_Y + frame,
		0xffffff, true);

	//HP�̐��l�\��
	DrawFormatStringToHandle(
		pos.x, pos.y + HP_GAUGE_Y + frame,
		0xffffff, unitFontHandle_, "HP\n%d", nowHp_);

}

void UnitUI::DrawName(const std::string& name, const Vector2& uPos)
{
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 fPos = { uPos.x - 25,uPos.y + 150 };
	Vector2 nPos = { uPos.x + unitSize / 2,uPos.y + 155 };

	//���O�g�̕\��
	DrawGraph(fPos.x, fPos.y, nameFrameImg_, true);

	//������́i�����́j�������擾
	auto fx = AsoUtility::StringLength(name, unitFontHandle_)/2;
	//���O�`��
	DrawStringToHandle(
		nPos.x - fx, nPos.y, name.c_str(), 0xffffff, unitFontHandle_);

}

void UnitUI::DrawBuffIcon()
{
	//�o�t�A�C�R���̕`��
	int i = 0;
	int s = 34;

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


		Vector2 iPos = { unitPos_.x + (i * 36) + 10, unitPos_.y + 120 };
		DrawShader::GetInstance().DrawExtendGraphToShader
		(iPos, { s,s }, icon_[num], psTextrue_, COLOR_F{});
		i++;

	}
}


