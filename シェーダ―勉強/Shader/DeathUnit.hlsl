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
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[
SamplerState g_SrcSampler:register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W����
	float2 uv = PSInput.TexCoords0;
	float4 color = g_SrcTexture.Sample(g_SrcSampler, uv);

	//����̉�f���擾����i�w������j
	float pi = 3.14159265f;
	float2 direction = float2(cos(pi),sin(pi));
	float uv_dis = 0.1f;

	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 0.25f);
	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 0.50f);
	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 0.75f);
	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 1.00f);

	//�P������
	color /= 5.0f;

	return color;
}