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
	float g_par;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture:register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler:register(s0);

float4 PosCircle(float2 uv,float2 pos, float genTime)
{
	//��������
	float gTime = g_time - genTime;

	//�i�s�x�Ŕ��f����
	//�~�̔��a��sin�֐��ŋ��߂�
	float per = gTime * 0.5f;	
	//1�ȏ�ɂȂ�Ȃ�
	if (per >= 1.0f || 0.0f >= per)
	{
		return float4(0.0f, 0.0f, 0.0f, 0.0f);
	}


	//�i�s�x
	//float circlePro = 1.0f - (cos(gTime) + 1.0f) / 2.0f;
	//�������a
	float initRadius = 0.0f;
	//������
	float grow = 0.4f;
	//�㏸���x
	float upSpeed = 0.2f;

	// �㏸
	pos.y -= gTime > 0.0f ? upSpeed * gTime : 0.0f;

	//���W��
	float2 disPos = uv - pos;
	//�~�̔��a
	float circlePer = sin(per*3.0f)/3.0f;


	float radius = initRadius + grow * circlePer;	//���]
	//�~�͈͓̔�
	float alpha = saturate(1.0f - length(disPos) / radius);
	//�~�̍ŏI�I�ȐF������
	float4 circle = float4(0.64f, 0.218f, 1.0f, alpha * 1.9f);


	//�����ƍ��W�ʒu�̃x�N�g���v�Z
	float2 light = float2(0.0f, -1.0f);
	//float2 shadowVec = normalize(disPos);
	//����
	float d = dot(disPos, light);
	//���a���狗�����A��
	float len = saturate(radius * (0.7f + d));
	circle.rg -= length(disPos) >= len ? float2(0.25f, 0.1f) : 0.0f;

	return circle;

}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	//�e�N�X�`���摜
	//�摜�F�̐i�s�x
	float pro = 1.0f - (cos(g_time * 2.0f) + 1.0f) * 0.5f;
	//���F�i��)
	float3 poi = float3(0.54f, 0.168f, 1.0f) ;
	//�F�̐��`���
	float3 disCol = lerp(srcCol.rgb, poi.rgb, min(pro * 2.5f, 2.0f));
	//float3 disCol = poi.rgb - srcCol.rgb;


	//�ʖ͗l
	//���W
	float2 pos = float2(0.8f, 0.5f);
	//��������
	float genTime = 0.0f;


	//�ŋ�
	float4 circle = PosCircle(uv, pos, genTime);

	//���ꕨ
	float4 c = float4(0.0f, 0.0f, 0.0f, 0.0f);


	//2
	pos = float2(0.3f, 0.8f);
	c = PosCircle(uv, pos, 0.8f);
	circle = c .a > circle.a ? c : circle;

	//3
	pos = float2(0.6f, 0.6f);
	c = PosCircle(uv, pos, 1.4f);
	circle = c.a > circle.a ? c : circle;
	//4
	pos = float2(0.2f, 0.8f);
	c = PosCircle(uv, pos, 1.8f);
	circle = c.a > circle.a ? c : circle;


	//����
	disCol.rgb = circle.a > 0.0f ? circle.rgb : disCol.rgb;


	return float4 (disCol, max(srcCol.a, circle.a));
}