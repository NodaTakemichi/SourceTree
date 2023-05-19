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
	float g_ratio;
	float g_time;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	//タイム
	float speed = 2.5f;
	float time = fmod(g_time / speed, 1.0f);

	//ベースカラー
	float4 color = float4(0.5f, 0.2f, 0.2f, 1.0f);
	if (uv.x <= g_ratio)
	{
		//横線
		float uy = 1.0f - (abs(uv.y - 0.5f)) * 3.0f;


		//縦線
		//タイムと近い距離を求める。
		float ux = 1.0f - abs(time - uv.x) * 12.0f;

		//rbは値が大きい方を優先
		color = float4(max(uy, ux), 1.0f, max(uy, ux), 1.0f);

	}

	return color;

}