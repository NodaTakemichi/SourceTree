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
		g_SrcTexture.Sample(g_SrcSampler, uv);



	//�摜�F�̐i�s�x
	float pro = min(1.0f - (cos(g_time * 3.0f) + 1.0f) / 2.0f, 0.6f);
	//���F
	float3 black = 0.0f;
	//�摜�Ƃ̍���
	float3 disCol = lerp(black.rgb, srcCol.rgb, pro);
	//float3 disCol = poi.rgb - srcCol.rgb;


	//����
	float3 result = srcCol.rgb + (disCol * pro);

	return float4 (disCol, srcCol.a);
}