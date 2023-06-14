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
//アドレッシングモード：0.0～1.0
SamplerState g_SrcSampler:register(s0);
//{
//	addressU = WRAP;
//	addressV = WRAP;
//};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	//uvスクロール
	uv.x += g_time * g_speed;

	//自力で0.0～1.0にする
	uv.x = frac(uv.x);

	//変更されたuv座標をもとに色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	return srcCol;
}