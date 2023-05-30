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
	float2 g_light;

}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);
//�@���}�b�v
Texture2D g_SrcNormalMap:register(t1);

//�T���v���[
SamplerState g_SrcSampler:register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W����
	float2 uv = PSInput.TexCoords0;
	float4 color = g_SrcTexture.Sample(g_SrcSampler, uv);

	float4 norCol = g_SrcNormalMap.Sample(g_SrcSampler, uv);

	//�@���}�b�v��RGB���x�N�g���ɕϊ�
	float3 normalVec = 2.0f * norCol - 1.0f;

	//���K��
	normalVec = normalize(normalVec);


	//���C�g�����Ɩ@���x�N�g���ŁA���ς��g�p���A���̓������𐔒l������
	//-1.0f�F���˕����@�A�@1.0�F������v�@�A 0.5�F���s
	//float3 bright = dot(g_light, normalVec);
	float3 bright = dot(0.9f, normalVec);

	color.rgb *= bright;
	return color;
}