#pragma once
#include"../../Common/Vector2.h"
class ButtonUI
{
public:
	ButtonUI();
	~ButtonUI();

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;



	//�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
	virtual bool MouseOnButton(void) = 0;
	//�N���b�N����
	bool PushButton(void);
	//����i�{�^�����痣�����Ƃ��j
	bool ButtonDecision(void);

protected:

	//���W
	Vector2 pos_;

	//�w�ʉ摜
	int backImg_;
	//��O�摜
	int frontImg_;
	
	//�{�^���摜�V�F�[�_�[
	int buttonPs_;
	//�V�F�[�_�[
	int psOnButton_;

	
	//�{�^���t���[���̔Z��
	float darkness_;

	//�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
	bool onButton_;


private:

};

