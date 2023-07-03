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
    float g_darkness;
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
    
    if (srcCol.a <= 0)
    {
        discard;
    }
    
    if (srcCol.r + srcCol.g + srcCol.b>=3.0f)
    {
        return srcCol;
    }
    
    
    //�g
    float frame = 0.0f;
    
    if (uv.x <= 0.1f)
    {
        frame += 1.0f - (uv.x / 0.1f);
    }
    if (uv.y <= 0.15f)
    {
        frame += 1.0f - (uv.y / 0.15f);
    }

    if (uv.x >= 0.9f)
    {
        frame += (uv.x - 0.9f) * 10.0f;
    }
    if (uv.y >= 0.85f)
    {
        frame += (uv.y - 0.85f) * 10.0f;
    }

    float d = max(g_darkness, 1.0f);
    frame /= d;
    srcCol.rgb += frame;
    return srcCol;
}