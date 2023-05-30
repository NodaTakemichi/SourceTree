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
cbuffer cbParam : register(b4)
{
	float4 g_color;
	float g_time;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);
//�`�悷��e�N�X�`��
Texture2D g_NoiseTexture:register(t1);

//�T���v���[�F�K�؂ȐF�����߂�
//�A�h���b�V���O���[�h�F0.0�`1.0
SamplerState g_SrcSampler:register(s0)
{
	addressU = WRAP;
	addressV = WRAP;
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W����
	float2 uv = PSInput.TexCoords0;

	//�ύX���ꂽuv���W�����ƂɐF���擾����
	//���l��(-1.0�`1.0)�ɂ���
	float4 noiseUv =
		g_NoiseTexture.Sample(g_SrcSampler, uv) * 2.0f - 1.0f;

	//�m�C�Y�̑傫�������߂āAuv�l��ς���
	uv.y += noiseUv * 0.2f;

	//�h�炬�����
	uv.y += frac(g_time * 0.5f);

	//X�F����
	uv.x += sin(g_time * 0.3);


	return noiseUv;
}