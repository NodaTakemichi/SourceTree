#pragma once
#include<vector>
#include "../Common/Vector2.h"
#include "SceneBase.h"

//class Vector2;
class RectButton;

class SelectScene :
    public SceneBase
{
public:

	enum class SELECT_MODE
	{
		BATTLE	  = 0,
		DECK_EDIT = 1,
		RULE_BOOK = 2,
		CREDIT	  = 3,
		Title	  = 4,
		MAX		  = 5
	};

	// �R���X�g���N�^
	SelectScene(void);

	// �f�X�g���N�^
	~SelectScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;


private:

	//�o�g��������
	//std::array<int, 3> enemys_;
	//�f�b�L���


	//���[�h�{�b�N�X�摜
	Vector2 modePos_;
	std::string nowMode_;
	int modeBox_;
	int modeFontHandle_;


	//�R�����g�{�b�N�X
	Vector2 cmtPos_;
	std::string devilCmt_;
	int cmtBox_;
	int cmtFontHandle_;

	//�}�X�R�b�g�摜
	int devilImg_;
	Vector2 devilPos_;
	int shakeY_;

	//�I���{�^��
	std::vector<RectButton*>buttons_;
	//�{�^��UI�摜
	int backBtnImg_;
	std::map<SELECT_MODE, int>btnImg_;


	//�V�F�[�_�[�n���h��
	//���]�L��V�F�[�_�[
	int psTex_;




	//�e�{�^������
	void BtnProcess();

	//�{�^��UI����
	void CerateBtnUI(void);

	//�e�{�^������
	void BattleBtnProcess(void);
	void EditBtnProcess(void);
	void RuleBtnProcess(void);
	void CreditBtnProcess(void);
	void TitleBtnProcess(void);

	//���[�h�{�b�N�X�`��
	void DrawModeBox(void);
	//�R�����g�{�b�N�X�`��
	void DrawCmtBox(void);

	//�f�r���̃R�����g�Z�b�g
	void SetDevilCmt(const std::string& cmt);

};

