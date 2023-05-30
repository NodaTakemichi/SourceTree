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
	float g_speed;
	float g_time;
}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標調整
	float2 uv = PSInput.TexCoords0;

	//変更されたuv座標をもとに色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);


	//特定範囲を光らせる
	float area = sin(uv.y * 2.0f - g_time * 0.5f);
	//値を１or０にするためにstep関数を使用
	float isArea = step(0.996f, area * area);
	//特定範囲だけ色加算を行い明るくする
	srcCol.rgb += isArea * 0.3f;

	//縦に一定間隔で暗くする
	//スキャンしている感を出すために、縦にUVスクロールする
	srcCol.rbg -= (1.0f - isArea) * abs(sin(uv.y * 60.0f + g_time * 1.0f)) * 0.10f;

	//ランダム感を出すために、もう一本増やす
	srcCol.rbg -= (1.0f - isArea) * abs(sin(uv.y * 100.0f - g_time * 2.0f)) * 0.20f;
	//感覚を細かく、速度を倍に、もっと暗く

	return srcCol *= g_color;
}