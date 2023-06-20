#pragma once
#include<DxLib.h>
class Vector2;

class DrawShader
{
public:

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static DrawShader& GetInstance(void);

	// ������
	void Init(void);

	// ���(�V�[���ؑ֎��Ɉ�U���)
	void Release(void);


	//�摜�`��i�萔�Ȃ��j
	void DrawGraphToShader(
		const Vector2& pos,const int& handle, const int& ps);
	//�摜�`��i�萔�t���j
	void DrawGraphToShader(
		const Vector2& pos,const int& handle, const int& ps,
		const COLOR_F& buf,const COLOR_F& subBuf = COLOR_F{});
	//�T�C�Y�w��`��
	void DrawExtendGraphToShader(
		const Vector2& pos, const Vector2& size , 
		const int& handle, const int& ps, 
		const COLOR_F& buf, const COLOR_F& subBuf = COLOR_F{});
	
	
	//�T�u�e�N�X�`���t���`��
	void DrawGraphAndSubToShader(
		const Vector2& pos,
		const int& mHandle, const int& sHandle,
		const int& ps, const COLOR_F& buf, const COLOR_F& subBuf = COLOR_F{});


private:

	// �ÓI�C���X�^���X
	static DrawShader* instance_;

	//HP�V�F�[�_�[
	//���_���
	VERTEX2DSHADER vertex_[4];
	WORD index_[6];

	//�V�F�[�_�[�萔�o�b�t�@
	int psConstBuf_;

	//�`��p�̎l�p���_�̍쐬
	void MakeSquereVertex(Vector2 pos, Vector2 size);





	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	DrawShader(void);

	// �f�X�g���N�^�����l
	~DrawShader(void);

};

