#pragma once
#include<string>
#include<vector>
#include<unordered_map>

//���j�b�g�̃f�[�^
struct UnitData
{
	int num;					//���j�b�g�ԍ�
	std::string name;			//���O
	std::string imgPath;		//�摜�p�X�E�E�E�n���h���ɓ���ւ��Ă���������
	int hp;						//�̗�
	int attack;					//�U����
	int speed;					//�f����
	std::vector<int> cmdNum;	//�R�}���h�ԍ�
};

class UnitDataManager
{


public:
	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static UnitDataManager& GetInstance(void);

	// ������
	void Init(void);

	// ���
	void Release(void);

	//���j�b�g�f�[�^�̃��[�h
	void LoadUnitData(void);

	//�w�胆�j�b�g�̎擾�i�����j
	const UnitData& GetUnitData(const int& num);

	//�w�胆�j�b�g�̉摜�擾
	const int& GetUnitImg(const int& num);
private:

	// �ÓI�C���X�^���X
	static UnitDataManager* instance_;

	// ���\�[�X�Ǘ��̑Ώ�
	std::unordered_map<int,UnitData> resMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::unordered_map<int,UnitData> loadedMap_;

	// �O�����琶���ł��Ȃ��l�ɂ���
	UnitDataManager(void);
	// �f�X�g���N�^�����l
	~UnitDataManager(void);


};

