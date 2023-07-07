#pragma once
#include<vector>
#include<array>
#include<map>
#include "SceneBase.h"

class CircleButton;
class UnitButton;
class UnitData;

class EditScene :
    public SceneBase
{
public:
	const Vector2 FIRST_UNIT_POOL_POS = { 106, 291 };
	const Vector2 OFFSET_UNIT_POOL_POS = { 151, 207 };


	// �R���X�g���N�^
	EditScene(void);

	// �f�X�g���N�^
	~EditScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:
	//�}�C�f�b�L
	std::vector<UnitData> deck_;

	//�������j�b�g�J�[�h
	std::map<int, UnitButton*> unitCards_;



	//�o�b�N�{�^��
	CircleButton* backBtn_;
	//�{�^���摜
	int backImg_;



	//�X�e�[�^�X�t�H���g�n���h��
	int sFontHandle_;
	int sFontColor_;
	//�s�b�N�A�b�v���j�b�g
	int pickUpUnit_;


	//���j�b�g�J�[�h�̔w�ʉ摜
	int unitBack_;

	//�J�[�h�X�e�[�^�X�̕`��
	void DrawUnitStatus(void);

	//�s�b�N�A�b�v���j�b�g�̑I��
	void SelectPickUpUnit(void);

};

