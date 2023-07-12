//�s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	//���W�i�v���W�F�N�V������ԁj
	float4 Position : SV_POSITION;
	//�f�B�t�[�Y�J���[
	float4 Diffuse : COLORO;
	//�e�N�X�`�����W
	float2 TexCoords0 : TEXCOORD0;
};

//�萔�o�b�t�@�F�X���b�g�ԍ�3�Ԗځib3�j
cbuffer cbParam : register(b3)
{
	float4 g_color;
	float g_time;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture : register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler : register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;
	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	//�g���ȊO�X�L�b�v
	if ((srcCol.r + srcCol.g + srcCol.b) < 3.0)
	{
		return srcCol;
	}



	//��]
	//��]�x�N�g��
    float speed = 1.0f;
    float rotCos = cos(g_time * speed);
    float rotSin = sin(g_time * speed);

	//2�����̉�]�s��
    float2x2 mat = { rotCos, -rotSin, rotSin, rotCos };

	//UV���W���󂯎��(���S�n��^�񒆂ɂ���)
    uv = PSInput.TexCoords0 - 0.5f;
	//uv�X�N���[��
    uv = mul(uv, mat) + 0.5f;



    float2 center = float2(0.5f, 0.5f);
	//���S���ɋ߂�������Ƃ炷
    float lr = 1.0f - distance(uv.x, center.x);
	
    float3 light = float3(lr, 0.0f, 0.0f);
    float3 white = float3(1.0f, 1.0f, 1.0f);
	
    white - light;
	
	//��
    float3 result = lerp(white, light, lr);


    return float4(result, 1.0f);
}