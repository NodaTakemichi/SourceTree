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
	float g_scale;		//���U�C�N�X�P�[��
	float g_sizeX;		//��ʃT�C�YX
	float g_sizeY;		//��ʃT�C�YY
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//UV���W��ς���
	float scaleX = 128 / g_scale;
	float scaleY = 128 / g_scale;
	uv.x = floor(uv.x * scaleX) / scaleX;
	uv.y = floor(uv.y * scaleY) / scaleY;

	//�X�V���ꂽuv���W�����ƂɐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	return srcCol *= g_color;
}