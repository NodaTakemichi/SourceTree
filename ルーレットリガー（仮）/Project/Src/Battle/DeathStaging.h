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
	void Draw(void);
	void Release(void);

	void DrawDeathUnit(void);

	//���S���j�b�g�̃Z�b�g
	void SetDeathUnit(const int& unitNum);

	//���S���o�̍Đ�
	void PlayDeathStaging(void);

	//���S���o�̏I��
	bool FinishStaging(void);


private:
	// �ÓI�C���X�^���X
	static DeathStaging* instance_;


	//���j�b�g�摜
	int duImg_;

	//���S���j�b�g�摜
	int unitImg_;

	//�Đ��������f
	bool isPlaying_;


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


	DeathStaging();
	~DeathStaging();


};

