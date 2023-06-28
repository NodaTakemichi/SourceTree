#include "../Common/Vector2.h"
#include "DrawShader.h"

DrawShader* DrawShader::instance_ = nullptr;

void DrawShader::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new DrawShader();
	}
	instance_->Init();
}

DrawShader& DrawShader::GetInstance(void)
{
	return *instance_;
}

void DrawShader::Init(void)
{
	psConstBuf_= CreateShaderConstantBuffer(sizeof(float) * 8);
}

void DrawShader::Release(void)
{
	DeleteShaderConstantBuffer(psConstBuf_);

	delete[] index_;
	delete[] vertex_;
}

void DrawShader::DrawGraphToShader(const Vector2& pos, const int& handle, const int& ps)
{
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(ps);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, handle);

	//�T�C�Y
	int x, y;
	GetGraphSize(handle, &x, &y);

	//�`����W
	MakeSquereVertex(pos, { x,y });


	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void DrawShader::DrawGraphToShader(
	const Vector2& pos, const int& handle, const int& ps,
	const COLOR_F& buf, const COLOR_F& subBuf)
{
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(ps);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, handle);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psConstBuf_;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	*cbBuf = buf;
	cbBuf++;
	*cbBuf = buf;

	//�T�C�Y
	int x, y;
	GetGraphSize(handle, &x, &y);

	//�`����W
	MakeSquereVertex(pos, {x,y});


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void DrawShader::DrawExtendGraphToShader(
	const Vector2& pos, const Vector2& size, 
	const int& handle, const int& ps, 
	const COLOR_F& buf, const COLOR_F& subBuf)
{
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(ps);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, handle);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psConstBuf_;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	*cbBuf = buf;
	cbBuf++;
	*cbBuf = subBuf;

	//�`����W
	MakeSquereVertex(pos,size);


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�o�C���j�A��ԃ��[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//�l�A���X�g�l�C�o�[�@
	SetDrawMode(DX_DRAWMODE_NEAREST);
}

void DrawShader::DrawGraphAndSubToShader(
	const Vector2& pos,
	const int& mHandle, const int& sHandle, const int& ps, 
	const COLOR_F& buf, const COLOR_F& subBuf)
{
	//�V�F�[�_�[�̐ݒ�
	SetUsePixelShader(ps);

	//�V�F�[�_�[�Ƀe�N�X�`����]��
	SetUseTextureToShader(0, mHandle);
	SetUseTextureToShader(1, sHandle);

	//�V�F�[�_�[�p�̒萔�o�b�t�@
	auto& cBuf = psConstBuf_;

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@�̃A�h���X���擾
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	*cbBuf = buf;
	cbBuf++;
	*cbBuf = subBuf;

	//�T�C�Y
	int x, y;
	GetGraphSize(mHandle, &x, &y);
	//�`����W
	MakeSquereVertex(pos, {x,y});


	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���X�V���ď������񂾓��e�𔽉f����
	UpdateShaderConstantBuffer(cBuf);

	//�s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@��萔�o�b�t�@���W�X�^�ɃZ�b�g
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//�`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void DrawShader::MakeSquereVertex(Vector2 pos, Vector2 size)
{

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + size.x);
	float eY = static_cast<float>(pos.y + size.y);

	// �S���_�̏�����
	for (int i = 0; i < 4; i++)
	{
		vertex_[i].rhw = 1.0f;
		vertex_[i].dif = GetColorU8(255, 255, 255, 255);
		vertex_[i].spc = GetColorU8(255, 255, 255, 255);
		vertex_[i].su = 0.0f;
		vertex_[i].sv = 0.0f;
	}

	// ����
	vertex_[cnt].pos = VGet(sX, sY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertex_[cnt].pos = VGet(eX, sY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// �E��
	vertex_[cnt].pos = VGet(eX, eY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 1.0f;
	cnt++;

	// ����
	vertex_[cnt].pos = VGet(sX, eY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 1.0f;

	// ���_�C���f�b�N�X
	cnt = 0;
	index_[cnt++] = 0;
	index_[cnt++] = 1;
	index_[cnt++] = 3;

	index_[cnt++] = 1;
	index_[cnt++] = 2;
	index_[cnt++] = 3;
}

DrawShader::DrawShader(void)
{
}

DrawShader::~DrawShader(void)
{
	delete instance_;
}
