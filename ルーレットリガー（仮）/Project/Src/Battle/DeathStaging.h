#pragma once
class DeathStaging
{
public:

	DeathStaging();
	~DeathStaging();

	void Init(void);
	void Draw(void);
	void Release(void);

	void DrawDeathUnit(void);

private:

	//�}�X�N�摜
	int maskImg_;
	//���S�t���[���摜
	int frameImg_;
	//���S���j�b�g�摜
	int unitImg_;
	//���S�w�i
	int backImg_;

	//�ʏ�V�F�[�_�[
	int psReverTex_;
	//���S���j�b�g�p�V�F�[�_�[
	int deathShader_;


	//�}�X�N�V�F�[�_�[�n���h��
	int psMask_;

	//�}�X�N�X�N���[��
	int maskScreen_;




};

