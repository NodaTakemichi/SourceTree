#pragma once
#include <map>
#include <string>
#include "Resource.h"

class ResourceManager
{

public:

	// ���\�[�X��
	enum class SRC
	{
		START_LOGO,

		//
		// �w�i�摜
		// UI�摜
		// ���j�b�g�摜
		// �o�t�摜
		// 
		// �G�t�F�N�g
		// 
		// �T�E���h
		// 
		// �t�H���g�f�[�^
		// �V�F�[�_�[�f�[�^
		//
	};

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static ResourceManager& GetInstance(void);

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);

	// ���\�[�X�̃��[�h
	Resource Load(SRC src);
	//�L�[�l�A�^�C�v�APath
	Resource Load(
		std::string key, Resource::TYPE type, std::string path);

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	// �ÓI�C���X�^���X
	static ResourceManager* instance_;

	// ���\�[�X�Ǘ��̑Ώ�
	//std::map<SRC, Resource> mResourcesMap;
	std::map<std::string, Resource> resourcesMap_;

	// �ǂݍ��ݍς݃��\�[�X
	//std::map<SRC, Resource*> mLoadedMap;
	std::map<std::string, Resource*> loadedMap_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);

	// �f�X�g���N�^�����l
	~ResourceManager(void);

	// �������[�h
	//Resource* _Load(SRC src);
	Resource* _Load(std::string key);

};

