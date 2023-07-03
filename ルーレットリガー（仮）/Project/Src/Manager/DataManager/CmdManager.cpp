#include "../../Common/GetAttr.h"

#include "CmdManager.h"

CmdManager* CmdManager::instance_ = nullptr;

void CmdManager::CreateInstance(void)
{
}

CmdManager& CmdManager::GetInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new CmdManager();
	}
	instance_->Init();
}

void CmdManager::Init(void)
{
	fileName_ = "./Data/UnitData/SmdData.xml";
	LoadCmdData();
}

void CmdManager::Release(void)
{
}

void CmdManager::LoadCmdData(void)
{
	//�h�L�������g��ۑ�����ϐ�
	rapidxml::xml_document<> actDoc;
	//�t�@�C���̃I�[�v��
	rapidxml::file<>xmlFile = fileName_.c_str();
	//��͍\�����āA�ϐ��Ƀf�[�^���i�[
	actDoc.parse<0>(xmlFile.data());

	//tmx�̏����擾�i���g�ɃA�N�Z�X�j
	auto cmd = actDoc.first_node("Cmd");
	if (cmd == nullptr)return;

	//�A�g���r���[�g�擾�֐�
	auto getAttr = GetAttr();


	//���j�b�g�̃R�}���h�Z�擾
	std::string name, type, target, buff;
	double times = 0.0;
	int num,efNum;

	for (auto skill = cmd->first_node("Skill");
		skill != nullptr;
		skill = skill->next_sibling())
	{
		//�Z�̔ԍ��擾
		if (!getAttr(skill, "num", num))num = 0;
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

		//�G�t�F�N�g�ԍ��擾
		if (!getAttr(skill, "efNum", efNum))efNum = 0;


		//�R�}���h�̐���
		Par par = {
			name,
			type,
			target,
			static_cast<float>(times),
			buff,
			efNum
		};
		cmdDataMap_.emplace(std::make_pair(num, par));
	}

}

const Par& CmdManager::GetCmdData(const int& num)
{
    // TODO: return �X�e�[�g�����g�������ɑ}�����܂�
}

CmdManager::CmdManager(void)
{
}

CmdManager::~CmdManager(void)
{
}
