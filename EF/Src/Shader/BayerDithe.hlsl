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
	float g_time;
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
	//�ψڑ��x
	int speed = 4;

	//�T�C���͈�
	float s = (sin(g_time * speed) + 1.0f) / 2.0f;
	//�x�C���[���x��
	float level = s * 14.0f;

	//UV�
	int x = round(PSInput.TexCoords0.x * 200);
	int y = round(PSInput.TexCoords0.y * 200);
	int dither = (x % 4) + (y % 4 * 4);
	if (int(level) > BayerPattern[dither])
	{
		discard;
	}

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float2 uv = PSInput.TexCoords0;
	float2 revers = float2(abs(g_revers - uv.x), uv.y);
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, revers);

	if (srcCol.a < 0.01f)
	{
		//�`�悵�Ȃ�
		discard;
	}

	return srcCol;
}