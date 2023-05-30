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
cbuffer cbParam : register(b4)
{
	float4 g_color;
	float g_time;
}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);
//描画するテクスチャ
Texture2D g_NoiseTexture:register(t1);

//サンプラー：適切な色を決める
//アドレッシングモード：0.0～1.0
SamplerState g_SrcSampler:register(s0)
{
	addressU = WRAP;
	addressV = WRAP;
};

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標調整
	float2 uv = PSInput.TexCoords0;

	//変更されたuv座標をもとに色を取得する
	//数値を(-1.0～1.0)にする
	float4 noiseUv =
		g_NoiseTexture.Sample(g_SrcSampler, uv) * 2.0f - 1.0f;

	//ノイズの大きさを決めて、uv値を変える
	uv.y += noiseUv * 0.2f;

	//揺らぎを作る
	uv.y += frac(g_time * 0.5f);

	//X：往復
	uv.x += sin(g_time * 0.3);


	return noiseUv;
}