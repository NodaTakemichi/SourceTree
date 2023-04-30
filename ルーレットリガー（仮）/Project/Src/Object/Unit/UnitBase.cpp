#include "../../Common/GetAttr.h"
#include "./UI/UnitUI.h"
#include "UnitBase.h"

UnitBase::UnitBase()
{
}

UnitBase::~UnitBase()
{
}

void UnitBase::Init(void)
{
	//������ԁA�s����ԁA���ݍs����Ԃ��Z�b�g����
	SetAlive(true);
	SetActed(false);
	SetAct(false);
	SetTargeted(false);
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
	//���
	DeleteGraph(img_);
}

void UnitBase::SetActed(bool acted)
{
	isActed_ = acted;
}

void UnitBase::SetAlive(bool alive)
{
	isAlive_ = alive;
}

void UnitBase::SetAct(bool act)
{
	isAct_ = act;
}

void UnitBase::SetTargeted(bool target)
{
	isTargeted_ = target;
}

void UnitBase::Damage(int dmg)
{
	//�_���[�W�v�Z
	hp_ -= dmg;

	//���S����
	if (CheckDead())
	{
		//���S��Ԃɂ���
		SetAlive(false);
	}
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
#pragma endregion

	

	//���j�b�g�̃R�}���h�Z�擾
	std::string name, type, target;
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

		//�R�}���h�̐���
		Command::Par par = {
			name,
			type,
			target,
			static_cast<float>(times)
		};
		CreateCommand(&par);
	}


	//�ő�HP
	maxHp_ = hp_;

	//�摜�̓o�^
	img_ = LoadGraph(source.c_str());
	return std::string();

}

void UnitBase::CreateCommand(Command::Par* par)
{
	//�R�}���h�̐���
	auto cmd = new Command(par);
	cmd->Init();
	commands_.push_back(cmd);
}

void UnitBase::SetDrawingPos(int x)
{
	
	auto topY = 40;
	auto spanY = 180;

	if (unitNum_ == 1)pos_ = { x, topY + spanY };
	else if (unitNum_ == 2)pos_ = { x,topY };
	else if (unitNum_ == 3)pos_ = { x,topY + spanY * 2 };
	
	return;
}
