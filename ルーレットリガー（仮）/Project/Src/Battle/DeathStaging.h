#pragma once
class DeathStaging
{
public:

	DeathStaging();
	~DeathStaging();

	void Init(void);
	void Draw(void);
	void Release(void);

	void DrawStaging(void);
	void DrawShader(void);

private:

	//�}�X�N�摜
	int maskImg_;
	//���S�t���[���摜
	int frameImg_;
	//���S���j�b�g�摜
	int unitImg_;


	//���S���j�b�g�p�V�F�[�_�[
		//�V�F�[�_�[�֘A
	//���_���
	VERTEX2DSHADER vertex_[4];
	WORD index_[6];

	//�V�F�[�_�[�n���h��
	//�}�X�N�`��
	int psTex_;
	int psTexConstBuf_;


	//�`��p�̎l�p���_�̍쐬
	void MakeSquereVertex(Vector2 pos);



};

