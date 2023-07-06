#pragma once
#include<vector>
#include<array>
#include "SceneBase.h"
class CircleButton;

class EditScene :
    public SceneBase
{
public:

	// �R���X�g���N�^
	EditScene(void);

	// �f�X�g���N�^
	~EditScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:


	//�ҏW�g�摜
	int editFrameImg_;

	//�}�C�f�b�L
	std::array<int,3> deck_;

	//�������j�b�g�ԍ�
	std::vector<int>units_;

	//�o�b�N�{�^��
	CircleButton* backBtn_;
	//�{�^���摜
	int backImg_;


	//�V�F�[�_�[
	int psMon_;

	//�t�H���g�n���h��
	int fontHandle_;
	int fontColor_;

};

