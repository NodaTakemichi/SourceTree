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
	float4 g_color;
	float g_time;
}


//サンプラー：適切な色を決める
SamplerState g_SrcSampler : register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	//時間
	float time = frac(g_time / 3.0f);

	//フレームカラー
	float4 frmCol = g_color;

	//反射
	frmCol.rgb += 1.0f - (uv.x - time);
	frmCol .rgb /= 4.0f;

	return frmCol;
}