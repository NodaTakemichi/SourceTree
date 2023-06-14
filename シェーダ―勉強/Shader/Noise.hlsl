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
	float g_time;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, PSInput.TexCoords0);

	//�m�C�Y�v�Z(�����Ōo�ߎ��Ԃ�^���邱�ƂŁA�m�C�Y�ɓ������������邱�Ƃ��o����)
	float noise = frac(sin(
		dot(uv , float2(12.9898f, 78.233f))) * 43758.5453f) - 0.5f;

	if (srcCol.a == 0.0f && noise > 0.0f)
	{
		//���R�ƃE�~�G�Ńm�C�Y�A���́A�m�C�Y�J���[�g�p
		srcCol.rgb = float3(noise, noise, noise);
		//�X�ɕs�����ɂ���
		srcCol.a = 1.0f;
	}
	else
	{
		//�m�C�Y�J���[�����Z����
		srcCol.rgb += float3(noise, noise, noise);
	}

	return srcCol;
}