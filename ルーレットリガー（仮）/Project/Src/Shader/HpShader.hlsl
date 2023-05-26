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
	float g_nowRatio;
	float g_hpRatio;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;


	float4 color= float4(0.0f, 0.0f, 0.0f, 1.0f);
	float x = 1 - abs(uv.x - 0.5);


	float gBack = g_hpRatio;
	float gFront = g_nowRatio;
	float rate = 1.5f;
	if (g_nowRatio > g_hpRatio)
	{
		gBack = g_nowRatio;
		gFront = g_hpRatio;
		rate = 0.7f;
	}
	
	if (uv.y >= 1.0f - gBack)			//HP�Q�[�W(��)
	{
		color = float4(x, x, x, 1.0f);
		color.rgb *= rate;

		if (uv.y >= 1.0f - gFront)		//HP�Q�[�W�i��O�j
		{
			color = float4(x, x, x, 1.0f);
		}
	}





	return color *= g_color;
}