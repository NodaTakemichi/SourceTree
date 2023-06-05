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
	float g_time;
	float g_par;
}

//描画するテクスチャ
Texture2D g_SrcTexture:register(t0);

//サンプラー：適切な色を決める
SamplerState g_SrcSampler:register(s0);

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV座標を受け取る
	float2 uv = PSInput.TexCoords0;

	//UV座標とテクスチャを参照して、最適な色を取得する
	float4 srcCol =
		g_SrcTexture.Sample(g_SrcSampler, uv);

	//テクスチャ画像
	//画像色の進行度
	float pro = 1.0f - (cos(g_time * 2.0f) + 1.0f) * 0.5f;
	//紫色（毒)
	float3 poi = float3(0.54f, 0.168f, 1.0f) ;
	//色の線形補間
	float3 disCol = lerp(srcCol.rgb, poi.rgb, min(pro * 2.5f, 2.0f));
	//float3 disCol = poi.rgb - srcCol.rgb;


	//玉模様
	//進行度
	float circlePro = 1.0f - (cos(g_time * 2.0f) + 1.0f) / 2.0f;
	//座標
	float2 pos = float2(0.2f, 0.9f);

	//初期半径
	float initRadius = 0.0f;
	//成長率
	float grow = 0.12f;
	//上昇速度
	float upSpeed = 0.05f;

	// 上昇
	float yOffset = upSpeed * g_time;
	pos.y -= yOffset;


	//座標差
	float2 disPos = uv - pos;
	float radius = initRadius + grow * circlePro;
	//円の最終的な色を決定
	float alpha = saturate(1.0f - length(disPos) / radius);
	float4 circle = float4(0.64f, 0.218f, 1.0f, alpha * 8.0f);


	//光線と座標位置のベクトル計算
	float2 light = float2(0.0f, -1.0f);
	//float2 shadowVec = normalize(disPos);
	//内積
	float d = dot(disPos, light);
	//半径から距離が、遠
	float len = radius * (0.7f + d);
	circle.rg -= length(disPos) >= len ? float2(0.25f, 0.1f) : 0.0f;

	disCol.rgb = circle.a > 0.0f ? circle.rgb : disCol.rgb;


	return float4 (disCol, max(srcCol.a, circle.a));
}