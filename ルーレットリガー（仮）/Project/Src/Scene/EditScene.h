#pragma once
#include<vector>
#include<array>
#include<map>
#include "SceneBase.h"
#include "../Manager/DataManager/UnitDataManager.h"

class CircleButton;
class UnitButton;
class CmdButton;

class EditScene :
    public SceneBase
{
public:
	const Vector2 FIRST_UNIT_POOL_POS = { 106, 291 };
	const Vector2 OFFSET_UNIT_POOL_POS = { 151, 207 };

	const Vector2 FIRST_UNIT_DECK_POS = { 336, 47 };
	const int OFFSET_UNIT_DECK_POS = 148;


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
	std::map<int, UnitButton*> deck_;

	//�������j�b�g�J�[�h
	std::map<int, UnitButton*> unitCards_;



	//�o�b�N�{�^��
	CircleButton* backBtn_;
	//�{�^���摜
	int backImg_;


	//�s�b�N�A�b�v���j�b�g
	int pickUpUnit_;
	//�X�e�[�^�X�t�H���g�n���h��
	int sFontHandle_;
	int sFontColor_;

	//�s�b�N�A�b�v���j�b�g�f�[�^
	UnitData pickUpUnitData_;

	//HP�A�U���́A�X�s�[�h�A�C�R��
	int hpIcon_;
	int attackIcon_;
	int speedIcon_;

	//�R�}���h�{�^��
	std::vector<CmdButton*> cmdBtns_;

	//�y�[�W��
	int page_;




	//���j�b�g�J�[�h�̔w�ʉ摜
	int unitBack_;

	//�J�[�h�X�e�[�^�X�̕`��
	void DrawUnitStatus(void);

	//�f�b�L�ҏW
	void DeckEditProcess(void);

	//�s�b�N�A�b�v���j�b�g�̑I��
	void SelectPickUpUnit(void);

	//�f�b�L�̊m��
	void DeckDecision(void);

};

