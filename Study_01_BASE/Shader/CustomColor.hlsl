//�萔�o�b�t�@�F�X���b�g�ԍ�3�Ԗځib3�j
cbuffer cbParam : register(b3)
{
	float4 g_color;
}

float4 main() : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return g_color;
}