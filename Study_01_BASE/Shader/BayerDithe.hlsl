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
	float g_level;			//ベイヤーレベル
	float g_img_sizeX;		//画面サイズX
	float g_img_sizeY;		//画面サイズY
}

//ベイヤー配列
static const int BayerPattern[16] = {
	 0, 8, 2,10,
	12, 4,14, 6,
	 3,11, 1, 9,
	15, 7,13, 5
};

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV基準
	int x = round(PSInput.TexCoords0.x * 128);
	int y = round(PSInput.TexCoords0.y * 128);
	int dither = (x % 4) + (y % 4 * 4);
	if (int(g_level) > BayerPattern[dither])
	{
		discard;
	}

	
	//UV座標とテクスチャを参照して、最適な色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, PSInput.TexCoords0);

	if (srcCol.a < 0.01f)
	{
		//描画しない
		discard;
	}

	return srcCol * g_color;
}