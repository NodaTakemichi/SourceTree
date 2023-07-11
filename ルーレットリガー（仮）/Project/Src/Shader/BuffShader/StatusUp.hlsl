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
    float g_compTime;
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

	//ギザギザ線
	float heigh = 0.4f;		//高さ
	float num = 4.0f;		//ギザギザ：横数
	uv.x = frac(uv.x * num);
	//反転（真ん中で反転）
	heigh *= uv.x < 0.5f ? uv.x : 0.5f - uv.x;
	uv.y += heigh;

	//グラデーション線
	//２色の差分を求める
	float3 topColor = float3(1.0f, 0.6f, 0.0f);
	float3 bottomColor = float3(1.0f, 0.9f, 0.0f);
	float3 c = abs(bottomColor.rgb - topColor.rgb);

	//線を動かす
	uv.y += frac(g_time * 0.8f);	//スピード
	float grad = frac(uv.y * 5.0f);//線：縦数
	c.rgb *= grad;


	//底辺色を加算
	c += topColor;


	//時間経過で薄くなる
    float pro = 1.0f - sin(g_time * g_compTime);
    pro = max(pro, 0.2f);
	//最終結果の差分
	float3 dec = srcCol.rgb - c;
	//差分を加算する
    float3 result = c + (dec * pro);



    return float4(result, srcCol.a) * 1.2f;
}
