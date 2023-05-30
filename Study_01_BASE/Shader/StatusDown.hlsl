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
	//UV基準
	float2 uv = PSInput.TexCoords0;

	//UV座標とテクスチャを参照して、最適な色を取得する
	float4 srcCol = g_SrcTexture.Sample(g_SrcSampler, uv);


	//２色の差分を求める
	float3 topColor = float3(0.0f, 0.6f, 1.0f);
	float3 bottomColor = float3(0.0f, 0.9f, 1.0f);
	float3 c = abs(bottomColor.rgb - topColor.rgb);

	//ギザギザ線
	float heigh = 0.4f;		//高さ
	float num = 4.0f;		//ギザギザ：横数
	uv.x = frac(uv.x * num);
	//反転（真ん中で反転）
	heigh *= uv.x < 0.5f ? uv.x : 0.5f - uv.x;
	uv.y += heigh;

	//グラデーション線
	uv.y += frac(g_time * -0.8f);	//スピード
	float grad = frac(uv.y * 5.0f);//線：縦数
	c.rgb *= grad;


	//底辺色を加算
	c += topColor;


	//時間経過で薄くなる
	float a = clamp(g_time - 3.0f, 0.4f, 1.0f);
	//最終結果の差分
	float3 dec = srcCol.rgb - c;
	//差分を加算する
	float3 result = c + (dec * 0.4f);


	return float4(result.r, result.g, result.b, srcCol.a);
}