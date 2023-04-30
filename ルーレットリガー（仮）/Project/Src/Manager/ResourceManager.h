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

		PLAYER,
		IDLE_ANIM,
		WALK_ANIM,
		RUN_ANIM,
		DEAD_ANIM,
		ATTACK_ANIM,
		DAMAGE_ANIM,
		WIN_ANIM,

		TRURTLE_SHELL,
		TRURTLE_SHELL_ANIM,
		SLIME,
		SLIME_ANIM,

		FLAME,
		LASER,
		TORNADE,
		FIRE,

		STAGE,
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

	// ���\�[�X�̕������[�h(���f���p)
	int LoadModelDuplicate(SRC src);

private:

	// �ÓI�C���X�^���X
	static ResourceManager* mInstance;

	// ���\�[�X�Ǘ��̑Ώ�
	std::map<SRC, Resource> mResourcesMap;

	// �ǂݍ��ݍς݃��\�[�X
	std::map<SRC, Resource*> mLoadedMap;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	ResourceManager(void);

	// �f�X�g���N�^�����l
	~ResourceManager(void);

	// �������[�h
	Resource* _Load(SRC src);

};

