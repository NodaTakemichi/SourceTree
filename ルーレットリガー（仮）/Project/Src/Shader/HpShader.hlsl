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

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	float x = 1 - abs(uv.x - 0.5);

	float4 color = float4(x, x, x, 1.0f);
	color *= g_color;
	return color;

}