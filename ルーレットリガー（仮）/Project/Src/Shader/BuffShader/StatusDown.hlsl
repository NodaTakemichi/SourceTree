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
	float g_revers;
	float g_time;
}

//�`�悷��e�N�X�`��
Texture2D g_SrcTexture : register(t0);

//�T���v���[�F�K�؂ȐF�����߂�
SamplerState g_SrcSampler : register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float2 uv = PSInput.TexCoords0;
	float2 revers = float2(abs(g_revers - uv.x), uv.y);
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, revers);

	//�Q�F�̍��������߂�
	float3 topColor = float3(0.0f, 0.6f, 1.0f);
	float3 bottomColor = float3(0.0f, 0.9f, 1.0f);
	float3 c = abs(bottomColor.rgb - topColor.rgb);

	//�M�U�M�U��
	float heigh = 0.4f;		//����
	float num = 4.0f;		//�M�U�M�U�F����
	uv.x = frac(uv.x * num);
	//���]�i�^�񒆂Ŕ��]�j
	heigh *= uv.x < 0.5f ? uv.x : 0.5f - uv.x;
	uv.y += heigh;

	//�O���f�[�V������
	uv.y += frac(g_time * -0.8f);	//�X�s�[�h
	float grad = frac(uv.y * 5.0f);//���F�c��
	c.rgb *= grad;

	//��ӐF�����Z
	c += topColor;


	
	float efTime = 2.0f;
	

	//���Ԍo�߂Ŕ����Ȃ�
	float a = 1.0f - sin(g_time / (efTime / 2.0f));
	//float a = max(1.0f - sin(g_time / efTime), 0.4f);
	//�ŏI���ʂ̍���
	float3 dec = srcCol.rgb - c;
	//���������Z����
	float3 result = c + (dec * abs(a));


	return float4(result, srcCol.a);
}
