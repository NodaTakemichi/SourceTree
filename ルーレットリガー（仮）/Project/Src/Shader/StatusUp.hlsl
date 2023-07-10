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
    float g_revers;
    float g_time;
}

//描画するテクスチャ
Texture2D g_SrcTexture : register(t0);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler : register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{

	//UV座標とテクスチャを参照して、最適な色を取得する
    float2 uv = PSInput.TexCoords0;
    float2 revers = float2(abs(g_revers - uv.x), uv.y);
    float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, revers);


    return srcCol;
}