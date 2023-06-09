#pragma once
#include<vector>
#include<EffekseerForDXLib.h>

class Vector2;
class EffectManager
{
public:

	//�G�t�F�N�g���
	struct Effect
	{
		int num;		//�G�t�F�N�g�i���o�[
		int handle;		//�G�t�F�N�g�n���h��
		float scale;	//�傫��
		Vector2 offset;	//�I�t�Z�b�g���W
	};

	EffectManager();
	~EffectManager();

	void Init(void);
	void Release(void);

	//�g�p�G�t�F�N�g�̃��[�h
	void EffectLoad(void);

	//�G�t�F�N�g�̐���
	void PlayEffect(const int& num,const Vector2& pos);

	//�G�t�F�N�g���I�����Ă��邩�ǂ���
	bool FinishEffect(void);

private:
	//�g�p�G�t�F�N�g�̃n���h��
	int effectHandle_;

	//�G�t�F�N�g���
	std::vector<Effect> ef_;

	//�Đ��G�t�F�N�g
	int effectPlay_;

};

