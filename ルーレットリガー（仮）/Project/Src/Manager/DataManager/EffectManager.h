#pragma once
#include<vector>
#include<utility>
#include<string>
#include<unordered_map>
#include"../../Common/Vector2.h"


struct EffectData
{
	//int num;			//�G�t�F�N�g�i���o�[
	std::string path;	//�G�t�F�N�g�p�X
	float scale;		//�傫��
	Vector2 offset;		//�I�t�Z�b�g���W
	int target;			//0:�S�̃G�t�F�N�g�@,1:�P�̃G�t�F�N�g
	int handle;			//�G�t�F�N�g�n���h��
};

class EffectManager
{
public:

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static EffectManager& GetInstance(void);


	void Init(void);
	void Release(void);

	//�o�^�G�t�F�N�g�̉��
	void LoadedEffectRelease(void);

	//�G�t�F�N�g���̃��[�h
	std::string EffectDataLoad(std::string fileName);

	//�g�p�G�t�F�N�g�̃��[�h
	void EffectLoad(const int& num);

	//�G�t�F�N�g�̐���
	void PlayEffect(const int& num,const Vector2& pos);

	//�G�t�F�N�g���I�����Ă��邩�ǂ���
	bool FinishEffect(void);

private:
	// �ÓI�C���X�^���X
	static EffectManager* instance_;


	//���\�[�X�Ǘ��}�b�v
	std::unordered_map<int, EffectData>resMap_;
	//���[�h�ς݃}�b�v
	std::unordered_map<int, EffectData>loadedMap_;


	//�G�t�F�N�g�Đ��n���h���ibool �F�g�p���g�p�j
	std::vector<std::pair<bool,int>> effectPlays_;

	//�Đ��n���h���̒ǉ�
	void CreatePlayHandle(void);

	//�S�̍U���G�t�F�N�g�̍Đ�
	bool AllTargetEffectPlay(const EffectData& ef, const Vector2& pos);

	EffectManager();
	~EffectManager();

};

