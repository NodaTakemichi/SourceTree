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
	float g_ratio;
	float g_time;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//�^�C��
	float speed = 2.5f;
	float time = fmod(g_time / speed, 1.0f);

	//�x�[�X�J���[
	float4 color = float4(0.5f, 0.2f, 0.2f, 1.0f);
	if (uv.x <= g_ratio)
	{
		//����
		float uy = 1.0f - (abs(uv.y - 0.5f)) * 3.0f;


		//�c��
		//�^�C���Ƌ߂����������߂�B
		float ux = 1.0f - abs(time - uv.x) * 12.0f;

		//rb�͒l���傫������D��
		color = float4(max(uy, ux), 1.0f, max(uy, ux), 1.0f);

	}

	return color;

}