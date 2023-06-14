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

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, PSInput.TexCoords0);

	float4 dstCol = srcCol * g_color;

	//��������F�𔲂��i�����A���m�g�[�����ɂ���j
	//�@�O�F�̕��ϒl���擾
	//float gray = (srcCol.r + srcCol.g + srcCol.b) / 3.0f;

	//�AITU-R Rec BT.601(���ςȂ̂ŁA�F��Z���đ����Ă���)
	float gray = dot(dstCol.rgb ,float3(0.299, 0.587, 0.144));
	dstCol.rgb = float3(gray, gray, gray);

	//�B�V���v���Z�s�A
	//dstCol.rgb *= float3(1.07f, 0.74f, 0.43f);

	//�C�V���v���Z�s�A
	float3 sepia = dstCol.rgb;
	sepia.r = dot(dstCol.rgb, float3(0.393f, 0.769f, 0.189f));
	sepia.g = dot(dstCol.rgb, float3(0.349f, 0.686f, 0.168f));
	sepia.b = dot(dstCol.rgb, float3(0.272f, 0.534f, 0.131f));
	dstCol.rgb = lerp(dstCol.rbg, sepia, 1.0f);


	return dstCol;
}