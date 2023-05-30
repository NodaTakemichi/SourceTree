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
	float g_scale;		//モザイクスケール
	float g_sizeX;		//画面サイズX
	float g_sizeY;		//画面サイズY
}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	//UV座標を変える
	float scaleX = 128 / g_scale;
	float scaleY = 128 / g_scale;
	uv.x = floor(uv.x * scaleX) / scaleX;
	uv.y = floor(uv.y * scaleY) / scaleY;

	//更新されたuv座標をもとに色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	return srcCol *= g_color;
}