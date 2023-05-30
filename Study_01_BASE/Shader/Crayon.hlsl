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

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//���͂̐F�������_���Ɏ擾����
	//�����_�������֐�
	// -0.50�`0.49
	float a = frac(dot(uv, float2(2.067390879775102f, 12.451168662908249f))) - 0.5f;
	float s = a * (6.182785114200511f + a * a *
		(-38.026512460676566f + a * a * 53.392573080032137f));
	// -0.99�`0.99
	float t = frac(s * 43758.5453f);

	//�X�V���ꂽuv���W�����ƂɐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	srcCol.rgb += float3(t, t, t);

	return srcCol *= g_color;
}