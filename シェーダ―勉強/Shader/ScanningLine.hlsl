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
	float g_speed;
	float g_time;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W����
	float2 uv = PSInput.TexCoords0;

	//�ύX���ꂽuv���W�����ƂɐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);


	//����͈͂����点��
	float area = sin(uv.y * 2.0f - g_time * 0.5f);
	//�l���Por�O�ɂ��邽�߂�step�֐����g�p
	float isArea = step(0.996f, area * area);
	//����͈͂����F���Z���s�����邭����
	srcCol.rgb += isArea * 0.3f;

	//�c�Ɉ��Ԋu�ňÂ�����
	//�X�L�������Ă��銴���o�����߂ɁA�c��UV�X�N���[������
	srcCol.rbg -= (1.0f - isArea) * abs(sin(uv.y * 60.0f + g_time * 1.0f)) * 0.10f;

	//�����_�������o�����߂ɁA������{���₷
	srcCol.rbg -= (1.0f - isArea) * abs(sin(uv.y * 100.0f - g_time * 2.0f)) * 0.20f;
	//���o���ׂ����A���x��{�ɁA�����ƈÂ�

	return srcCol *= g_color;
}