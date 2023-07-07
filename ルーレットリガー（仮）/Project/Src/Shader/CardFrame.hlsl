//�s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	//���W�i�v���W�F�N�V������ԁj
	float4 Position : SV_POSITION;
	//�f�B�t�[�Y�J���[
	float4 Diffuse : COLORO;
	//�e�N�X�`�����W
	float2 TexCoords0 : TEXCOORD0;
};

//�萔�o�b�t�@�F�X���b�g�ԍ�3�Ԗځib3�j
cbuffer cbParam : register(b3)
{
	float4 g_color;
	float g_time;
}


//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler : register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//����
	float time = frac(g_time / 3.0f);

	//�t���[���J���[
	float4 frmCol = g_color;

	//����
	frmCol.rgb += 1.0f - (uv.x - time);
	frmCol .rgb /= 4.0f;

	return frmCol;
}