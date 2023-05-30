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

//サンプラー：適切な色を決める
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	//周囲の色をランダムに取得する
	//ランダム生成関数
	// -0.50～0.49
	float a = frac(dot(uv, float2(2.067390879775102f, 12.451168662908249f))) - 0.5f;
	float s = a * (6.182785114200511f + a * a *
		(-38.026512460676566f + a * a * 53.392573080032137f));
	// -0.99～0.99
	float t = frac(s * 43758.5453f);

	//更新されたuv座標をもとに色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	srcCol.rgb += float3(t, t, t);

	return srcCol *= g_color;
}