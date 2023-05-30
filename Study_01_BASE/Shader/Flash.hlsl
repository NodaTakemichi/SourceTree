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
	float g_distance;
	float g_sizeX;
	float g_sizeY;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[
SamplerState g_SrcSampler:register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W����
	float2 uv = PSInput.TexCoords0;
	float4 color = g_SrcTexture.Sample(g_SrcSampler, uv);

	//���͂̕������i�������̉�f���W�߂邩�B�P�U�ȉ��j
	float directions = 16.0f;
	//1����������̋����i�T�C�Y�j
	//g_distance
	//UV���a
	//float2 radius = float2(g_distance / g_sizeX, g_distance / g_sizeY);
	float2 radius = float2(0.1f, 0.1f);

	//����̉�f���擾����i�w������j
	float twoPi = 3.14159265f * 2.0f;

	//����
	float2 dir = float2(cos(twoPi), sin(twoPi));

	//dir *= float2(1.0f / 128.0f, 1.0f / 128.0f);
	//�������ׂ̂���
	// ������(�E�A��)�ׂ̗̃s�N�Z��///�����ŃG���[���o��
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 1.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 2.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 3.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 4.0f);
	//// ������(���A��)�ׂ̗̃s�N�Z��
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 1.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 2.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 3.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 4.0f);
	//return color /= 9.0f;

	//���ȏ�
	//�P�����肢����f����邩�i�����𔼕������邩�B�S�ȉ��j
	float quality = 3.0f;

	//2PI�𕪊��������Ŋ����āA1�񂠂���̉�]�ʁi���W�A���j��
	//�Z�o���Asin,cos�ŕ������o��
	for (float rad = 0.0f; rad < twoPi; rad += twoPi / directions)
	{
		//���̋������N�I���e�B�[���A�������ČJ��Ԃ�
		for (float i = 0; i < quality; i++)
		{
			//�Ώۉ�f����u���[�������A���ꂽ��f���擾�ł���B
			color += g_SrcTexture.Sample(g_SrcSampler,
				uv + float2(cos(rad), sin(rad)) * radius * (i * 1.0f / quality));
		}
	}

	//����
	color /= (directions * quality * 0.7f);


	return color;
}