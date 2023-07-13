#pragma once
#include<vector>
#include "../Common/Vector2.h"
#include "SceneBase.h"

//class Vector2;
class RectButton;
class CircleButton;

struct ModeData {
	int modeImg;		//���[�h�I���摜
	RectButton* btn;	//���[�h�{�^��
};

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
		TITLE	  = 4,
		MAX		  
	};


	enum class SELECT_STAGE
	{
		FOREST,
		SEE,
		MAX
	};

	enum class SELECT_ENEMYS
	{
		EASY,
		NORMAL,
		HARD,
		LUNATIC,
		MAX
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
	//�o�b�N�{�^��
	//BackButton* backBtn_;
	CircleButton* backBtn_;
	//�{�^���摜
	int backImg_;


	//�o�g��������
	std::map < SELECT_STAGE, std::vector<std::array<int, 3>>>enemys_;
	
	//�f�b�L���


	//���݃��[�h
	SELECT_MODE mode_;
	//���[�h�{�^��
	std::map<SELECT_MODE, ModeData>modeBtn_;
	//���[�h�{�^���摜
	int modeBtnImg_;


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

	//�V�F�[�_�[�n���h��
	//���]�L��V�F�[�_�[
	int psTex_;


	//���[�h�{�b�N�X�`��
	void DrawModeBox(void);
	//�R�����g�{�b�N�X�`��
	void DrawCmtBox(void);


	//�{�^������
	void BtnProcess();
	//�e�{�^������
	void BattleBtnProcess(void);
	void EditBtnProcess(void);
	void RuleBtnProcess(void);
	void CreditBtnProcess(void);
	void TitleBtnProcess(void);

	//���[�h�{�^������
	void CreateModeBtn(void);

	//���[�h�̕ύX
	void ChangeSelectMode(const SELECT_MODE& mode);

	//�N���b�N�����{�^���̏���
	void SelectBtnProcess(void);

	//�}�X�R�b�g�̃R�����g�Z�b�g
	void SetDevilCmt(const std::string& cmt);

	//�o�g��������̓o�^
	void BattleEnemyInit(void);


};

