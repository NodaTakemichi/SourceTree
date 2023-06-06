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

float4 PosCircle(float2 uv,float2 pos, float genTime)
{
	//発生時間
	float gTime = g_time - genTime;


	//進行度
	//float circlePro = 1.0f - (cos(gTime * 3.0f) + 1.0f) / 2.0f;
	float circlePro = 1.0f - (cos(gTime) + 1.0f) / 2.0f;
	//初期半径
	float initRadius = 0.0f;
	//成長率
	float grow = 0.12f;
	//上昇速度
	float upSpeed = 0.1f;

	// 上昇
	pos.y -= upSpeed * gTime;

	//停止する指標
	// ・半径
	// ・時間
	// ・割合？
	//

	//if (gTime >= 1.0f)
	//{
	//	return float4(0.0f, 0.0f, 0.0f, 0.0f);
	//}


	//座標差
	float2 disPos = uv - pos;
	//円の半径
	float radius = initRadius + grow * saturate(circlePro);
	//円の範囲内
	float alpha = saturate(1.0f - length(disPos) / radius);
	//円の最終的な色を決定
	float4 circle = float4(0.64f, 0.218f, 1.0f, alpha * 0.8f);


	//光線と座標位置のベクトル計算
	float2 light = float2(0.0f, -1.0f);
	//float2 shadowVec = normalize(disPos);
	//内積
	float d = dot(disPos, light);
	//半径から距離が、遠
	float len = saturate(radius * (0.7f + d));
	circle.rg -= length(disPos) >= len ? float2(0.25f, 0.1f) : 0.0f;

	return circle;

}

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
	//座標
	float2 pos = float2(0.8f, 0.8f);
	//発生時間
	float genTime = 0.0f;


	//毒玉
	float4 circle = PosCircle(uv, pos, genTime);

	//入れ物
	float4 c = float4(0.0f, 0.0f, 0.0f, 0.0f);


	//2
	pos = float2(0.3f, 0.8f);
	c = PosCircle(uv, pos, 0.4f);
	circle = c .a > 0.0f ? c : circle;

	//3
	pos = float2(0.2f, 0.6f);
	c = PosCircle(uv, pos, 0.9f);
	circle = c.a > 0.0f ? c : circle;
	//4
	pos = float2(0.6f, 0.7f);
	c = PosCircle(uv, pos, 1.2f);
	circle = c.a > 0.0f ? c : circle;


	//結果
	disCol.rgb = circle.a > 0.0f ? circle.rgb : disCol.rgb;


	return float4 (disCol, max(srcCol.a, circle.a));
}