#pragma once
#include <vector>
#include "SceneBase.h"
class TitleScene :
    public SceneBase
{
public:

	// �R���X�g���N�^
	TitleScene(void);

	// �f�X�g���N�^
	~TitleScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:


	//�^�C�g���摜
	int titleImg_;
	//�w�i�摜
	int backImg_;

	//�����X�^�[�摜
	std::vector<int> monsters_;

	//�����X�^�[�摜�\���V�F�[�_�[
	int psMon_;
	//�^�C�g���摜�V�F�[�_�[
	int psTitle_;

	//�t�H���g�n���h��
	int fontHandle_;
	int fontColor_;
};

