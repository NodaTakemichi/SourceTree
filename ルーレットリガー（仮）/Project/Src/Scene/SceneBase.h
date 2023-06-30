#pragma once

class SceneBase
{
public:

	// �R���X�g���N�^
	SceneBase(void);
	// �f�X�g���N�^
	virtual ~SceneBase(void);

	// ����������
	virtual void Init(void) = 0;
	// �X�V�X�e�b�v
	virtual void Update(void) = 0;
	// �`�揈��
	virtual void Draw(void) = 0;
	// �������
	virtual void Release(void) = 0;

protected:

	//�w�i�摜
	int bgImg_;

	//BGM�n���h��
	int bgmHandle_;
	//�o�ߎ���
	float totalTime_;




private:

};

