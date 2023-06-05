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

float noise(float2 p)
{
	return frac(sin(dot(p, float2(12.9898, 78.233))) * 43758.5453);
}

float CreateLine(
	float2 currentTempPos, float2 currentStraightPos, 
	float2 size, float2 uv)
{
	// �{���̗��|�W�V��������␳��̃|�W�V�����ւ̃x�N�g��
	float2 lab = currentTempPos - currentStraightPos;
	// �␳��|�W�V�������珈������uv���W�ւ̃x�N�g��
	float2 la = uv - currentTempPos;
	// �{���̃|�W�V�������珈����uv���W�ւ̃x�N�g��
	float2 lb = uv - currentStraightPos;
	// +1���Ɠ_�ɂȂ�
	float2 d = (length(la) + length(lb) - length(lab)) * min(length(la), length(lb));
	// pow(x,y) x��y���Ԃ�
	return size - pow(d * 4e8, 0.07);
}

float Lightning(float2 uv ,float2 sPos, float2 ePos)
{
	float s = 0.0f;
	int num = 10;
	// �����ɕ\�����闋�̖{��
	int lightningNum = 4;
	for (int j = 1; j < lightningNum; j++)
	{
		// ���̐�[�|�W�V����
		float2 temp = sPos;
		// ������������1���̋���
		float2 d = (ePos - sPos) / num;
		for (int i = 1; i < num; i++)
		{
			float2 currentPos = sPos + d * i;
			if (i == j * 2)
			{
				// ���̓����������������郉���_���v�f
				d += (noise(float2(j, j) + currentPos) - 0.5) *
					noise(currentPos) * 0.025;
			}
			currentPos += (noise(currentPos) - 0.5) * d.y;
			float l = CreateLine(
				temp, currentPos, j * 0.25 + 2.0, uv);
			s = max(l, s);

			temp = currentPos;
		}
	}

	return s;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{

	//UV���W���󂯎��
	float2 uv = PSInput.TexCoords0;

	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);


	//��
	float s = 0.0f;

	//�n�_�A�I�_
	float2 endPos = float2(0.1, 1.2);
	float2  startPos =
		float2((cos(g_time*0.001f) + 1.0f) * 0.5f * 0.01f + 0.1f,
		    	(sin(g_time*0.001) + 1.0f) * 0.5 * 0.01f - 0.2f);
	//���߂����͗l��k���Z
	s += Lightning(uv, startPos, endPos);

	//�n�_�A�I�_
	startPos = float2(0.9, 1.2);
	endPos =
		float2((cos(g_time*0.001f) + 1.0f) * 0.5f * 0.01f + 0.9f,
				(sin(g_time*0.001) + 1.0f) * 0.5 * 0.01f - 0.2f);
	//���߂����͗l��k���Z
	s += Lightning(uv, startPos, endPos);


	// ���̐F���Z�b�g
	float4 lightning =  float4(s, s, s -1.05f, s);





	//�摜�F�̐i�s�x
	//float pro = min(1.0f - (sin(g_time * 3.0f) + 1.0f) / 2.0f, 0.8f);
	float pro =  (cos(g_time * 2.0f) + 1.0f) / 2.0f;
	//���F
	float3 black = 0.0f;
	//�摜�Ƃ̍���
	float3 disCol = lerp(black.rgb, srcCol.rgb, pro);
	//float3 disCol = poi.rgb - srcCol.rgb;


	//����
	float3 result = srcCol.rgb + (disCol * pro);

	return float4 (disCol, srcCol.a)+ lightning;
}