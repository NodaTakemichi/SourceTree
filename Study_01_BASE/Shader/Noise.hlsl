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
		g_SrcTexture.Sample(g_SrcSampler, PSInput.TexCoords0);

	//ノイズ計算(ここで経過時間を与えることで、ノイズに動きを持たせることが出来る)
	float noise = frac(sin(
		dot(uv , float2(12.9898f, 78.233f))) * 43758.5453f) - 0.5f;

	if (srcCol.a == 0.0f && noise > 0.0f)
	{
		//敢然とウミエでノイズアリは、ノイズカラー使用
		srcCol.rgb = float3(noise, noise, noise);
		//更に不透明にする
		srcCol.a = 1.0f;
	}
	else
	{
		//ノイズカラーを加算する
		srcCol.rgb += float3(noise, noise, noise);
	}

	return srcCol;
}