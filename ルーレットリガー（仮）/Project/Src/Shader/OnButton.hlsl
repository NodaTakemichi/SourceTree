//ピクセルシェーダーの入力
struct PS_INPUT
{
	//座標（プロジェクション空間）
    float4 Position : SV_POSITION;
	//ディフーズカラー
    float4 Diffuse : COLORO;
	//テクスチャ座標
    float2 TexCoords0 : TEXCOORD0;
};

//定数バッファ：スロット番号3番目（b3）
cbuffer cbParam : register(b3)
{
    float g_darkness;
}

//描画するテクスチャ
Texture2D g_SrcTexture : register(t0);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler : register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
    float2 uv = PSInput.TexCoords0;

	//UV座標とテクスチャを参照して、最適な色を取得する
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
    
    
    //枠
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