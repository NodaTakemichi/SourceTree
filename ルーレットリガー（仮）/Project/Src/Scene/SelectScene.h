#pragma once
#include<vector>
#include "../Common/Vector2.h"
#include "SceneBase.h"

//class Vector2;
class ButtonUI;

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
		EXIT	  = 4,
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

	//�e�{�^������
	void BtnProcess();

	//�{�^��UI����
	void CerateBtnUI(void);

	//�e�{�^������
	void BattleBtnProcess(void);
	void EditBtnProcess(void);
	void RuleBtnProcess(void);
	void CreditBtnProcess(void);
	void ExitBtnProcess(void);

private:

	//�G���z��

	//�f�b�L���



	//�I���{�^��
	std::vector<ButtonUI*>buttons_;
	//�{�^��UI�摜
	int backBtnImg_;
	std::map<SELECT_MODE, int>btnImg_;


	//�����܉摜
	int devilImg_;
	Vector2 devilPos_;
	int shakeY_;


	//�V�F�[�_�[
	int psTex_;
};

