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
//シェーダ―
//法線マップ
Texture2D g_SrcNormalMap:register(t1);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{

	////回転ベクトル
	//float rotCos = cos(g_time * g_speed);
	//float rotSin = sin(g_time * g_speed);
	////2次元の回転行列
	//float2x2 mat = { rotCos,-rotSin,rotSin,rotCos };
	////UV座標を受け取る(中心地を真ん中にする)
	//float2 uv = PSInput.TexCoords0 - 0.5f;
	////uvスクロール
	//uv = mul(uv, mat) + 0.5f;
	////変更されたuv座標をもとに色を取得する
	//float4 srcCol =
	//	g_SrcTexture.Sample(g_SrcSampler, uv);

	//回転ベクトル
	float rotCos = cos(g_time * g_speed);
	float rotSin = sin(g_time * g_speed);

	//2次元の回転行列
	float2x2 mat = { rotCos,-rotSin,rotSin,rotCos };

	//UV座標を受け取る(中心地を真ん中にする)
	float2 uv = PSInput.TexCoords0 - 0.5f;
	//uvスクロール
	uv = mul(uv, mat) + 0.5f;

	//変更されたuv座標をもとに色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	float4 maskCol =
		g_SrcNormalMap.Sample(g_SrcSampler, uv);

	maskCol *= srcCol;


	return maskCol;
}