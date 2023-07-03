#pragma once
#include"../Common/Vector2.h"
class ButtonUI
{
public:
	ButtonUI();
	~ButtonUI();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//�{�^������
	void Create(Vector2 pos, Vector2 size, int back, int front);

	//�N���b�N����
	bool PushButton(void);

	//����i�{�^�����痣�����Ƃ��j
	bool ButtonDecision(void);

private:

	//���W
	Vector2 pos_;
	//�{�^���T�C�Y
	Vector2 size_;

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

	//�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
	bool MouseOnButton(void);
	//�l�p�`��ɍ��W�����邩�̊m�F
	bool IsMouseInRect(
		const Vector2& inside,const Vector2& outside,const Vector2& size);
};

