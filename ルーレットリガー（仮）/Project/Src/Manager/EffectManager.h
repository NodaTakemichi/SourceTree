#pragma once
#include<vector>
#include<utility>
#include<string>

class Vector2;
class EffectManager
{
public:

	//�G�t�F�N�g���
	
	
	struct EffectData
	{
		int num;		//�G�t�F�N�g�i���o�[
		int handle;		//�G�t�F�N�g�n���h��
		float scale;	//�傫��
		Vector2 offset;	//�I�t�Z�b�g���W
		int target;		//0:�S�̃G�t�F�N�g�@,1:�P�̃G�t�F�N�g
	};

	EffectManager();
	~EffectManager();

	void Init(void);
	void Release(void);

	//�g�p�G�t�F�N�g�̃��[�h
	std::string EffectLoad(std::string fileName);

	//�G�t�F�N�g�̐���
	void PlayEffect(const int& num,const Vector2& pos);
	void PlayEffect(const int& num,const Vector2& pos, const float& scale);

	//�G�t�F�N�g���I�����Ă��邩�ǂ���
	bool FinishEffect(void);

private:

	//�G�t�F�N�g���
	std::vector<EffectData> ef_;

	//�G�t�F�N�g�Đ��n���h���ibool �F�g�p���g�p�j
	std::vector<std::pair<bool,int>> effectPlays_;

	//�Đ��n���h���̒ǉ�
	void CreatePlayHandle(void);

	//�S�̍U���G�t�F�N�g�̍Đ�
	bool AllTargetEffectPlay(const EffectData& ef, const Vector2& pos);
	bool AllTargetEffectPlay(const EffectData& ef, const Vector2& pos, const float& scale);

};

