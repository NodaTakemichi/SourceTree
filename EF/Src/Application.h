#pragma once
#include <string>

class Application
{

public:

	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 600;
	static constexpr int SCREEN_SIZE_Y = 600;


	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static Application& GetInstance(void);

	// ������
	void Init(void);

	// �Q�[�����[�v�̊J�n
	void Run(void);

	// ���\�[�X�̉��
	void Release(void);

	// �����������^���s�̔���
	bool IsInitFail(void) const;

	// ��������^���s�̔���
	bool IsReleaseFail(void) const;

private:

	// �ÓI�C���X�^���X
	static Application* mInstance;

	// ���������s
	bool mIsInitFail;

	// ������s
	bool mIsReleaseFail;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Application(void);

	// �f�X�g���N�^�����l
	~Application(void);

	// Effekseer�̏�����
	void InitEffekseer(void);

};