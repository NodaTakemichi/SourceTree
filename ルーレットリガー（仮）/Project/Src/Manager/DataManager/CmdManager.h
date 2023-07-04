#pragma once
#include<string>
#include<vector>
#include<unordered_map>

struct Parameter
{
	//�R�}���h��
	std::string name;
	//�R�}���h�^�C�v(�L���X�g�O)
	std::string type;
	//�^�[�Q�b�g(�L���X�g�O)
	std::string target;

	//�Z�F�{��
	float times;

	//�o�t�^�C�v(�L���X�g�O)
	std::string buff;

	//�G�t�F�N�g�ԍ�
	int efNum;
};

class CmdManager
{

public:
	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static CmdManager& GetInstance(void);

	// ������
	void Init(void);

	// ���
	void Release(void);

	//�R�}���h�f�[�^�̃��[�h
	void LoadCmdData(void);

	//�w��R�}���h�̎擾�i�����j
	const Parameter& GetCmdData(const int& num);

private:
	// �ÓI�C���X�^���X
	static CmdManager* instance_;

	//�t�@�C����
	std::string fileName_;
	// �R�}���h�f�[�^�i�ԍ����L�[�l�Ƃ���j
	std::unordered_map<int, Parameter> cmdDataMap_;


	// �O�����琶���ł��Ȃ��l�ɂ���
	CmdManager(void);
	// �f�X�g���N�^�����l
	~CmdManager(void);

};

