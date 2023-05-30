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
	float2 uv = PSInput.TexCoords0 - 0.5f;
	
	//ベクトルの長さ
	float len = length(uv);

	//一定の渦巻量で回転をし続ける
	float pow = 3.5f;
	//float rad = len * pow + fmod(g_time, 3.14159f * 2.0f);

	//時間に応じて渦巻量をどんどん増やす
	float rad = len * g_time * g_speed;

	//回転ベクトル
	float rotCos = cos(rad);
	float rotSin = sin(rad);

	//2次元の回転行列
	float2x2 mat = { rotCos,-rotSin,rotSin,rotCos };

	//uv調整
	uv = mul(uv, mat) + 0.5f;

	//変更されたuv座標をもとに色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	return srcCol *= g_color;
}