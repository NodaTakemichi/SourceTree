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
	float g_time;
}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	//UV座標とテクスチャを参照して、最適な色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);



	//画像色の進行度
	float pro = min(1.0f - (cos(g_time * 3.0f) + 1.0f) / 2.0f, 0.6f);
	//黒色
	float3 black = 0.0f;
	//画像との差分
	float3 disCol = lerp(black.rgb, srcCol.rgb, pro);
	//float3 disCol = poi.rgb - srcCol.rgb;


	//結果
	float3 result = srcCol.rgb + (disCol * pro);

	return float4 (disCol, srcCol.a);
}