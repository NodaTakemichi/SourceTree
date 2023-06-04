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

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	//�i�s�x
	float circlePro = 1.0f - (cos(g_time * 2.0f) + 1.0f) / 2.0f;

	//�ʖ͗l
	float2 pos = float2(0.5f, 0.8f);
	//�������a
	float initRadius = 0.0f;
	//������
	float grow = 0.15f;
	//�㏸���x
	float upSpeed = 0.1f;

	// �㏸
	float yOffset = upSpeed * g_time;
	pos.y -= yOffset;
	

	//���W��
	float2 disPos = uv - pos;
	float radius = initRadius + grow * circlePro;
	//�ʂ̍ŏI�I�ȐF������
	float alpha = saturate(1.0f - length(disPos) / radius);
	float4 circle = float4(0.64f, 0.218f, 1.0f, alpha * 8.0f);


	//�����ƍ��W�ʒu�̃x�N�g���v�Z
	float2 light = float2(0.0f, 1.0f);
	//float2 shadowVec = normalize(disPos);
	//����
	float d = dot(disPos, light);
	//���a���狗�����A��
	float len = radius * (0.7f + d);
	if (length(disPos) >= len)
	{
		circle.rg -= float2(0.25f, 0.1f);
	}


	//�摜�F�̐i�s�x
	float pro = min(sin(g_time * 2.0f) - 1.0f / 2.0f, 0.6f);
	//���F�i��)
	float3 poi = float3(0.54f, 0.168f, 1.0f);
	//�摜�Ƃ̍���
	float3 disCol = lerp(poi.rgb, srcCol.rgb, pro);
	//float3 disCol = poi.rgb - srcCol.rgb;


	//����
	float3 result = srcCol.rgb + (disCol * pro);

	//return float4 (disCol, srcCol.a) + circle;
	return circle;
}