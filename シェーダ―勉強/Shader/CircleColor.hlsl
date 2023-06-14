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
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	
	//円の描画
	float x = abs(uv.x - 0.5f);
	float y = abs(uv.y - 0.5f);
	float dis = ((x * x) + (y * y)) * 4.0f;
	float4 color = float4(dis, dis, dis, 1.0f);
	color += g_color;
	return color; 
}