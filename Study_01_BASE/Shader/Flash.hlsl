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
	float g_distance;
	float g_sizeX;
	float g_sizeY;
}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);

//サンプラー
SamplerState g_SrcSampler:register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標調整
	float2 uv = PSInput.TexCoords0;
	float4 color = g_SrcTexture.Sample(g_SrcSampler, uv);

	//周囲の方向数（何方向の画素を集めるか。１６以下）
	float directions = 16.0f;
	//1方向当たりの距離（サイズ）
	//g_distance
	//UV半径
	//float2 radius = float2(g_distance / g_sizeX, g_distance / g_sizeY);
	float2 radius = float2(0.1f, 0.1f);

	//周りの画素を取得する（指定方向）
	float twoPi = 3.14159265f * 2.0f;

	//方向
	float2 dir = float2(cos(twoPi), sin(twoPi));

	//dir *= float2(1.0f / 128.0f, 1.0f / 128.0f);
	//自分調べのやり方
	// 正方向(右、上)の隣のピクセル///ここでエラーが出る
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 1.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 2.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 3.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv + dir * 4.0f);
	//// 負方向(左、下)の隣のピクセル
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 1.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 2.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 3.0f);
	//color += g_SrcTexture.Sample(g_SrcSampler, uv - dir * 4.0f);
	//return color /= 9.0f;

	//教科書
	//１あたりいくつ画素を取るか（距離を半分割するか。４以下）
	float quality = 3.0f;

	//2PIを分割方向数で割って、1回あたりの回転量（ラジアン）を
	//算出し、sin,cosで方向を出す
	for (float rad = 0.0f; rad < twoPi; rad += twoPi / directions)
	{
		//この距離をクオリティー分、分割して繰り返す
		for (float i = 0; i < quality; i++)
		{
			//対象画素からブラー距離分、離れた画素が取得できる。
			color += g_SrcTexture.Sample(g_SrcSampler,
				uv + float2(cos(rad), sin(rad)) * radius * (i * 1.0f / quality));
		}
	}

	//平均
	color /= (directions * quality * 0.7f);


	return color;
}