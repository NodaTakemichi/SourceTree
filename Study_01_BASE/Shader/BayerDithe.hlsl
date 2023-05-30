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
	float g_level;			//�x�C���[���x��
	float g_img_sizeX;		//��ʃT�C�YX
	float g_img_sizeY;		//��ʃT�C�YY
}

//�x�C���[�z��
static const int BayerPattern[16] = {
	 0, 8, 2,10,
	12, 4,14, 6,
	 3,11, 1, 9,
	15, 7,13, 5
};

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV�
	int x = round(PSInput.TexCoords0.x * 128);
	int y = round(PSInput.TexCoords0.y * 128);
	int dither = (x % 4) + (y % 4 * 4);
	if (int(g_level) > BayerPattern[dither])
	{
		discard;
	}

	
	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, PSInput.TexCoords0);

	if (srcCol.a < 0.01f)
	{
		//�`�悵�Ȃ�
		discard;
	}

	return srcCol * g_color;
}