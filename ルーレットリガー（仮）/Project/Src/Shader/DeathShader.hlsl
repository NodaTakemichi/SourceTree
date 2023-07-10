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
	float g_revers;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);
Texture2D g_MaskTexture:register(t1);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;
	//���]
	float2 revers = float2(abs(g_revers - uv.x), uv.y);

	//�摜�F�A�}�X�N�摜
	float4 srcCol = g_SrcTexture.Sample(g_SrcSampler, revers);
	float4 maskCol = g_MaskTexture.Sample(g_SrcSampler, revers);

	//�}�X�N����
	if (maskCol.a == 0.0f)
	{
		discard;
	}

	return srcCol;
}