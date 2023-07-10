#pragma once
class DeathStaging
{
public:
	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static DeathStaging& GetInstance(void);


	void Init(void);
	void Update(void);
	void Release(void);

	//���S���o�̍Đ�
	void PlayDeathStaging(void);

	//���S���j�b�g�̃Z�b�g
	void SetDeathUnit(const int& img,const float& r);


	//���S���o�̏I��
	bool PlayingStaging(void);


private:
	// �ÓI�C���X�^���X
	static DeathStaging* instance_;

	//���S���j�b�g�摜
	int unitImg_;
	//�Đ��������f
	bool isPlaying_;

	//���v����
	float totalTime_;
	//�}�X�N�摜�̑傫��
	int mSizeX_;

	//�}�X�N�摜
	int maskImg_;
	//���S�t���[���摜
	int frameImg_;
	//���S�w�i
	int backImg_;

	//�ʏ�V�F�[�_�[
	int psReverTex_;
	//���S���j�b�g�p�V�F�[�_�[
	int psDeathShader_;


	//�}�X�N�V�F�[�_�[�n���h��
	int psMask_;

	//�}�X�N�X�N���[��
	int maskScreen_;
	//���S���o�`��X�N���[��
	int deathStagingScreen_;

	//��ʔ��]
	float revers_;


	DeathStaging();
	~DeathStaging();


};

