//ピクセルシェーダーの入力
struct PS_INPUT
{
	//座標（プロジェクション空間）
	float4 Position			:SV_POSITION;
	//ディフーズカラー
	float4 Diffuse			:COLORO;
	//テクスチャ座標
	float2 TexCoords0		:TEXCOORD0;

};

//定数バッファ：スロット番号3番目（b3）
cbuffer cbParam : register(b3)
{
	float4 g_color;
}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);

//サンプラー
SamplerState g_SrcSampler:register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標調整
	float2 uv = PSInput.TexCoords0;
	float4 color = g_SrcTexture.Sample(g_SrcSampler, uv);

	//周りの画素を取得する（指定方向）
	float pi = 3.14159265f;
	float2 direction = float2(cos(pi),sin(pi));
	float uv_dis = 0.1f;

	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 0.25f);
	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 0.50f);
	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 0.75f);
	color += g_SrcTexture.Sample(g_SrcSampler, uv + direction * uv_dis * 1.00f);

	//単純平均
	color /= 5.0f;

	return color;
}