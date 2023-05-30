//�s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	//���W�i�v���W�F�N�V������ԁj
	float4 Position			:SV_POSITION;
	//�f�B�t�[�Y�J���[
	float4 Diffuse			:COLORO;
	//�e�N�X�`�����W
	float2 TexCoords0		:TEXCOORD0;

};

//�萔�o�b�t�@�F�X���b�g�ԍ�3�Ԗځib3�j
cbuffer cbParam : register(b3)
{
	float4 g_color;
	float g_speed;
	float g_time;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W����
	float2 uv = PSInput.TexCoords0 - 0.5f;
	
	//�x�N�g���̒���
	float len = length(uv);

	//���̉Q���ʂŉ�]����������
	float pow = 3.5f;
	//float rad = len * pow + fmod(g_time, 3.14159f * 2.0f);

	//���Ԃɉ����ĉQ���ʂ��ǂ�ǂ񑝂₷
	float rad = len * g_time * g_speed;

	//��]�x�N�g��
	float rotCos = cos(rad);
	float rotSin = sin(rad);

	//2�����̉�]�s��
	float2x2 mat = { rotCos,-rotSin,rotSin,rotCos };

	//uv����
	uv = mul(uv, mat) + 0.5f;

	//�ύX���ꂽuv���W�����ƂɐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	return srcCol *= g_color;
}