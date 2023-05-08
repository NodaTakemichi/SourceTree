#include <algorithm>
#include "../../Common/GetAttr.h"
#include "./UI/UnitUI.h"

#include"../../_debug/_DebugConOut.h"

#include "UnitBase.h"

UnitBase::UnitBase()
{
}

UnitBase::~UnitBase()
{
}

void UnitBase::Init(void)
{
	//�o�t
	buff_ = new Buff();
	buff_->Init();

	//������ԁA�s����ԁA���ݍs����Ԃ��Z�b�g����
	SetAlive(true);
	SetActed(false);
	SetAct(false);
	SetTargeted(false);

	//�e�N�X�`���\�V�F�[�_�[�̓o�^
	//psHpColor_ = LoadPixelShader("./Data/Shader/HpShader.cso");
	psTex_ = LoadPixelShader("./x64/Debug/Texture.cso");
	psMonotone_ = LoadPixelShader("./x64/Debug/Monotone.cso");

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̍쐬
	psTexConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);

	//���݂̃V�F�[�_�[
	nowPs_ = psTex_;
}

void UnitBase::Update(void)
{
}

void UnitBase::Draw(void)
{
	//�s�������j�b�g
	if (IsAct())unitUi_->DrawActUnit();

	//�_���Ă��郆�j�b�g
	if (IsTargeted())unitUi_->DrawRockOn();

}

void UnitBase::Release(void)
{
	//�|�C���^
	unitUi_->Release();
	buff_->Release();

	//���
	DeleteGraph(unitImg_);
}

void UnitBase::Damage(const int& dmg)
{
	//���OHP�̋L��
	beforHp_ = hp_;

	//�_���[�W�v�Z
	hp_ -= dmg;

	//���S����
	if (CheckDead())
	{
		TRACE("���S���܂���\n");

		//�V�F�[�_�[�̕ύX
		nowPs_ = psMonotone_;

		//���S��Ԃɂ���
		SetAlive(false);
	}
}

void UnitBase::Heal(const int& heal)
{
	//���OHP�̋L��
	beforHp_ = hp_;

	//HP�v�Z(HP�������)
	hp_ += heal;
	hp_ = (std::min)(hp_, maxHp_);
}

void UnitBase::GiveBuff(const Buff::BUFF_TYPE& type)
{
	buff_->SetBuff(type);
}

bool UnitBase::CheckDead(void)
{
	//���S����
	if (hp_ <= 0)
	{
		return true;
	}
	return false;
}

std::string UnitBase::LoadData(std::string fileName)
{
	//�h�L�������g��ۑ�����ϐ�
	rapidxml::xml_document<> actDoc;
	//�t�@�C���̃I�[�v��
	rapidxml::file<>xmlFile = fileName.c_str();
	//��͍\�����āA�ϐ��Ƀf�[�^���i�[
	actDoc.parse<0>(xmlFile.data());

	//tmx�̏����擾�i���g�ɃA�N�Z�X�j
	auto unit = actDoc.first_node("Unit");
	if (unit == nullptr)return std::string();

	//�A�g���r���[�g�擾�֐�
	auto getAttr = GetAttr();
	
	//�摜�̃\�[�X�p�X
	std::string source;

	//���j�b�g�̃f�[�^�̎擾
#pragma region ���j�b�g�̊�{���
	auto data = unit->first_node();
	if (data == nullptr)return std::string();
	//���j�b�g�̖��O�擾
	if (!getAttr(data, "name", name_))return std::string();
	//���j�b�g�̉摜�p�X�擾
	if (!getAttr(data, "source", source))return std::string();
	//���j�b�g��HP�擾
	if (!getAttr(data, "hp", hp_))return std::string();
	//���j�b�g�̍U���͎擾
	if (!getAttr(data, "attack", attack_))return std::string();
	//���j�b�g�̃X�s�[�h�擾
	if (!getAttr(data, "speed", speed_))return std::string();
	//���j�b�g�̃X�s�[�h�擾
	if (!getAttr(data, "speed", speed_))return std::string();
#pragma endregion

	

	//���j�b�g�̃R�}���h�Z�擾
	std::string name, type, target,buff;
	double times = 0.0;

	auto cmd = unit->first_node("Cmd");
	if (cmd == nullptr)return std::string();
	for (auto skill = cmd->first_node();
		skill != nullptr;
		skill = skill->next_sibling())
	{
		//�Z�̖��O�擾
		if (!getAttr(skill, "name", name))name = std::string();
		//�Z�̃^�C�v�擾
		if (!getAttr(skill, "type", type))type = std::string();
		//�Z�̋Z�Ώێ擾
		if (!getAttr(skill, "target", target))target = std::string();
		//�Z�̔{���擾
		if (!getAttr(skill, "times", times))times = 0.0;

		//�o�t�̎�ގ擾
		if (!getAttr(skill, "buff", buff))buff = "NONE";


		//�R�}���h�̐���
		Command::Par par = {
			name,
			type,
			target,
			static_cast<float>(times),
			buff
		};
		CreateCommand(&par);
	}


	//�ő�HP
	maxHp_ = beforHp_= hp_;

	//�摜�̓o�^
	unitImg_ = LoadGraph(source.c_str());
	return std::string();

}

void UnitBase::DrawUnitShader(const int& shader, const float& revers)
{
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(shader);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, unitImg_);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psTexConstBuf_;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = revers;


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}

void UnitBase::CreateCommand(Command::Par* par)
{
	//�R�}���h�̐���
	auto cmd = new Command(par);
	cmd->Init();
	commands_.push_back(cmd);
}

void UnitBase::MakeSquereVertex(Vector2 pos)
{
	//�O�p�`�̃|���S����2����āA�������Ă���

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + DRAWING_SIZE - 1);
	float eY = static_cast<float>(pos.y + DRAWING_SIZE - 1);

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

void UnitBase::SetDrawingPos(int x)
{
	
	auto topY = 40;
	auto spanY = 180;

	if (unitNum_ == 1)pos_ = { x, topY + spanY };
	else if (unitNum_ == 2)pos_ = { x,topY };
	else if (unitNum_ == 3)pos_ = { x,topY + spanY * 2 };

	MakeSquereVertex(pos_);
	
	return;
}
