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
	float g_time;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);
//�@���}�b�v
Texture2D g_SrcNormalMap:register(t1);

//�T���v���[
SamplerState g_SrcSampler:register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	float2 uv = PSInput.TexCoords0;

	//�x�N�g���̎Z�o
	float4 n = g_SrcNormalMap.Sample(g_SrcSampler,uv);
	//�͈́@���K��
	n.xy *= 2;
	n.xy -= 1;
	n.z = -1;
	n.xyz = normalize(n.xyz);//���K��

	//���F��]���x
	float ls = g_time * 0.6f;

	//�A�e�v�Z						 
	float3 light = normalize(float3(cos(ls), sin(ls), 1));
	//float3 light = normalize(float3(1, -1, 1));
	float b = saturate(dot(n.xyz, -light));//�N�����v��葬���N�����v
	light = reflect(light, n);//�f�B�t�[�Y
	float3 eye = float3(0, 0, 1);
	float spec = pow(saturate(dot(-eye, light)), 10);//�X�y�L����
	float4 col = g_SrcTexture.Sample(g_SrcSampler,uv);
	return float4(col.xyz * b + spec, col.a);

}