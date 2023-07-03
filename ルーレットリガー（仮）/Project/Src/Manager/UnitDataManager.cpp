#include<DxLib.h>
#include<sstream>
#include "../Common/GetAttr.h"

#include "UnitDataManager.h"

UnitDataManager* UnitDataManager::instance_ = nullptr;

void UnitDataManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new UnitDataManager();
	}
	instance_->Init();
}

UnitDataManager& UnitDataManager::GetInstance(void)
{
	return *instance_;
}

void UnitDataManager::Init(void)
{
	//�t�@�C����
	failName_ = "./Data/UnitData/UnitTable.xml";

	//�f�[�^�̃��[�h
	LoadUnitData();
}

void UnitDataManager::Release(void)
{
	unitDataMap_.clear();
}

void UnitDataManager::LoadUnitData(void)
{ 
	//�h�L�������g��ۑ�����ϐ�
	rapidxml::xml_document<> actDoc;
	//�t�@�C���̃I�[�v��
	rapidxml::file<>xmlFile = failName_.c_str();
	//��͍\�����āA�ϐ��Ƀf�[�^���i�[
	actDoc.parse<0>(xmlFile.data());

	//tmx�̏����擾�i���g�ɃA�N�Z�X�j
	auto data = actDoc.first_node("Data");
	if (data == nullptr)return;

	//�A�g���r���[�g�擾�֐�
	auto getAttr = GetAttr();

	//�f�[�^�ێ�
	std::string name, source;
	int num,hp, attack, speed;
	//�R�}���h�ԍ��z��
	std::vector<int> cmds;


	//�e���j�b�g�̃f�[�^�̎擾
	for (auto unit = data->first_node("Unit");
		unit != nullptr;
		unit = unit->next_sibling())
	{

#pragma region ���j�b�g�̊�{���
		auto par = unit->first_node();
		if (par == nullptr)return;
		//���j�b�g�̔ԍ��擾
		if (!getAttr(par, "num", num))return;
		//���j�b�g�̖��O�擾
		if (!getAttr(par, "name", name))return;
		//���j�b�g�̉摜�p�X�擾
		if (!getAttr(par, "source", source))return;
		//���j�b�g��HP�擾
		if (!getAttr(par, "hp", hp))return;
		//���j�b�g�̍U���͎擾
		if (!getAttr(par, "attack", attack))return;
		//���j�b�g�̃X�s�[�h�擾
		if (!getAttr(par, "speed", speed))return;
#pragma endregion


#pragma region �R�}���h�ԍ�(csv)�̎擾
		auto csvNode = unit->first_node("Cmd");
		if (csvNode == nullptr)return;

		//csv�f�[�^�̎擾
		//csv�f�[�^�i�[�p�̕ϐ��錾
		std::stringstream dataStream;
		//csv�̒��g���i�[
		dataStream << csvNode->value();			//���Ɍ������f�[�^�𗬂����ށidataStream�̒��g�͂Ȃ�����������Ȃ��ăR�s�[�j
		//1���������o���āA�i�[���Ă���
		std::string numStr;
		while (std::getline(dataStream, numStr, ','))
		{
			int cmd = std::stoi(numStr, nullptr, 10);
			cmds.push_back(cmd);
		}
#pragma endregion

		//�摜�n���h��
		int handle = LoadGraph(source.c_str());

		//�f�[�^�̑}��
		UnitData paramter = {
			name,
			handle,
			hp,
			attack,
			speed,
			cmds
		};
		unitDataMap_.emplace(std::make_pair(num, paramter));

		//�R�}���h�N���A
		cmds.clear();
	}


}



const UnitData& UnitDataManager::GetUnitData(const int& num)
{
	UnitData data;
	return data;
}

const int& UnitDataManager::GetUnitImg(const int& num)
{
	return 0;
}

UnitDataManager::UnitDataManager(void)
{
}

UnitDataManager::~UnitDataManager(void)
{
}

