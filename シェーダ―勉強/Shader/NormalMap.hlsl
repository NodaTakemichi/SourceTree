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
	float2 g_light;

}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);
//法線マップ
Texture2D g_SrcNormalMap:register(t1);

//サンプラー
SamplerState g_SrcSampler:register(s0);


float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標調整
	float2 uv = PSInput.TexCoords0;
	float4 color = g_SrcTexture.Sample(g_SrcSampler, uv);

	float4 norCol = g_SrcNormalMap.Sample(g_SrcSampler, uv);

	//法線マップのRGBをベクトルに変換
	float3 normalVec = 2.0f * norCol - 1.0f;

	//正規化
	normalVec = normalize(normalVec);


	//ライト方向と法線ベクトルで、内積を使用し、光の当たり具合を数値化する
	//-1.0f：反射方向　、　1.0：方向一致　、 0.5：直行
	//float3 bright = dot(g_light, normalVec);
	float3 bright = dot(0.9f, normalVec);

	color.rgb *= bright;
	return color;
}