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

	//UV座標とテクスチャを参照して、最適な色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, PSInput.TexCoords0);

	float4 dstCol = srcCol * g_color;

	//ここから色を抜く（白黒、モノトーン調にする）
	//①三色の平均値を取得
	//float gray = (srcCol.r + srcCol.g + srcCol.b) / 3.0f;

	//②ITU-R Rec BT.601(内積なので、色乗算して足している)
	float gray = dot(dstCol.rgb ,float3(0.299, 0.587, 0.144));
	dstCol.rgb = float3(gray, gray, gray);

	//③シンプルセピア
	//dstCol.rgb *= float3(1.07f, 0.74f, 0.43f);

	//④シンプルセピア
	float3 sepia = dstCol.rgb;
	sepia.r = dot(dstCol.rgb, float3(0.393f, 0.769f, 0.189f));
	sepia.g = dot(dstCol.rgb, float3(0.349f, 0.686f, 0.168f));
	sepia.b = dot(dstCol.rgb, float3(0.272f, 0.534f, 0.131f));
	dstCol.rgb = lerp(dstCol.rbg, sepia, 1.0f);


	return dstCol;
}