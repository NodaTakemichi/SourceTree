#include <chrono>
#include <math.h>
#include <string>
#include <DxLib.h>
#include "main.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_X, SCREEN_Y, 32, 60);

	// ＤＸライブラリの初期化
	if (DxLib_Init() < 0)
	{
		// エラーが発生したら直ちに終了
		return -1;
	}

	// 初期化
	Init();
	// 実行
	Run();
	// 解放
	Release();
	// ＤＸライブラリの後始末
	DxLib_End();
	// ソフトの終了
	return 0;
}

void Init(void)
{

	// 描画に使用する画像の読み込み
	texDragon = LoadGraph("Data/Dragon.png");

	// 描画に使用する画像の読み込み
	texDragonNor = LoadGraph("Data/Dragon_n.png");

	// 描画に使用する画像の読み込み
	texFire = LoadGraph("Data/Fire.png");

	// 描画に使用する画像の読み込み
	texNoize = LoadGraph("Data/Noise128.png");

	// 描画に使用する画像の読み込み
	texWhite = LoadGraph("Data/White.png");

	// 描画に使用する画像の読み込み
	texCircle = LoadGraph("Data/mainTex.png");
	// 描画に使用する画像の読み込み
	texCircleMask = LoadGraph("Data/loadMask.png");



	//ピクセルシェーダーのロード
	psSimpleColor = LoadPixelShader(
		(PATH_SHADER + "SimpleColor.cso").c_str());

	//ピクセルシェーダーのロード
	psCustomColor = LoadPixelShader(
		(PATH_SHADER + "CustomColor.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psCustomColorConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//ピクセルシェーダーのロード
	psCircleColor = LoadPixelShader(
		(PATH_SHADER + "CircleColor.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psCircleColorConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//ピクセルシェーダーのロード
	psTexture = LoadPixelShader(
		(PATH_SHADER + "Texture.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psTextureConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//ピクセルシェーダーのロード
	psAlphaBlend = LoadPixelShader(
		(PATH_SHADER + "AlphaBlend.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psAlphaBlendConstBuf = CreateShaderConstantBuffer(sizeof(float) * 4);

	//ピクセルシェーダーのロード
	psDithering = LoadPixelShader(
		(PATH_SHADER + "Dithering.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psDitheringConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psBayerDithe = LoadPixelShader(
		(PATH_SHADER + "BayerDithe.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psBayerDitheConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psMonotone = LoadPixelShader(
		(PATH_SHADER + "Monotone.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psMonotoneConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psSimleSepia = LoadPixelShader(
		(PATH_SHADER + "SimleSepia.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psSimleSepiaConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psNoise = LoadPixelShader(
		(PATH_SHADER + "Noise.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psNoiseConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psMosaic = LoadPixelShader(
		(PATH_SHADER + "Mosaic.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psMosaicConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psCrayon = LoadPixelShader(
		(PATH_SHADER + "Crayon.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psCrayonConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psScroll = LoadPixelShader(
		(PATH_SHADER + "Scroll.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psScrollConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psRotate = LoadPixelShader(
		(PATH_SHADER + "Rotate.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psRotateConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psSwirl = LoadPixelShader(
		(PATH_SHADER + "Swirl.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psSwirlConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psScanningLine = LoadPixelShader(
		(PATH_SHADER + "ScanningLine.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psScanningLineConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psDistortion = LoadPixelShader(
		(PATH_SHADER + "Distortion.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psDistortionConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psDirBlur = LoadPixelShader(
		(PATH_SHADER + "DirBlur.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psDirBlurConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psBlur = LoadPixelShader(
		(PATH_SHADER + "Blur.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psBlurConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psFlash = LoadPixelShader(
		(PATH_SHADER + "Flash.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psFlashConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psNormalMap = LoadPixelShader(
		(PATH_SHADER + "NormalMap.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psNormalMapConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psStatusUp = LoadPixelShader(
		(PATH_SHADER + "StatusUp.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psStatusUpConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psStatusDown = LoadPixelShader(
		(PATH_SHADER + "StatusDown.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psStatusDownConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psPoison = LoadPixelShader(
		(PATH_SHADER + "Poison.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psPoisonConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

	//ピクセルシェーダーのロード
	psParalysis = LoadPixelShader(
		(PATH_SHADER + "Paralysis.cso").c_str());
	//ピクセルシェーダー用の定数バッファの作成
	psParalysisConstBuf = CreateShaderConstantBuffer(sizeof(float) * 8);

}

void Release(void)
{

	// ピクセルシェーダーを解放
	DeleteShader(psSimpleColor);
	DeleteShader(psCustomColor);
	DeleteShader(psCircleColor);
	DeleteShader(psTexture);
	DeleteShader(psAlphaBlend);
	DeleteShader(psDithering);
	DeleteShader(psBayerDithe);
	DeleteShader(psMonotone);
	DeleteShader(psSimleSepia);
	DeleteShader(psNoise);
	DeleteShader(psMosaic);
	DeleteShader(psCrayon);
	DeleteShader(psScroll);
	DeleteShader(psRotate);
	DeleteShader(psSwirl);
	DeleteShader(psScanningLine);
	DeleteShader(psDistortion);
	DeleteShader(psDirBlur);
	DeleteShader(psBlur);
	DeleteShader(psFlash);
	DeleteShader(psNormalMap);
	DeleteShader(psStatusUp);
	DeleteShader(psStatusDown);
	DeleteShader(psPoison);
	DeleteShader(psParalysis);

	// ピクセルシェーダー用定数バッファを解放
	DeleteShaderConstantBuffer(psCustomColorConstBuf);
	DeleteShaderConstantBuffer(psCircleColorConstBuf);
	DeleteShaderConstantBuffer(psTextureConstBuf);
	DeleteShaderConstantBuffer(psAlphaBlendConstBuf);
	DeleteShaderConstantBuffer(psDitheringConstBuf);
	DeleteShaderConstantBuffer(psBayerDitheConstBuf);
	DeleteShaderConstantBuffer(psMonotoneConstBuf);
	DeleteShaderConstantBuffer(psSimleSepiaConstBuf);
	DeleteShaderConstantBuffer(psNoiseConstBuf);
	DeleteShaderConstantBuffer(psMosaicConstBuf);
	DeleteShaderConstantBuffer(psCrayonConstBuf);
	DeleteShaderConstantBuffer(psScrollConstBuf);
	DeleteShaderConstantBuffer(psRotateConstBuf);
	DeleteShaderConstantBuffer(psSwirlConstBuf);
	DeleteShaderConstantBuffer(psScanningLineConstBuf);
	DeleteShaderConstantBuffer(psDistortionConstBuf);
	DeleteShaderConstantBuffer(psDirBlurConstBuf);
	DeleteShaderConstantBuffer(psBlurConstBuf);
	DeleteShaderConstantBuffer(psFlashConstBuf);
	DeleteShaderConstantBuffer(psStatusUpConstBuf);
	DeleteShaderConstantBuffer(psStatusDownConstBuf);
	DeleteShaderConstantBuffer(psPoisonConstBuf);
	DeleteShaderConstantBuffer(psParalysisConstBuf);


}

void Run(void)
{

	// メインスクリーン作成
	mainScreen = MakeScreen(SCREEN_X, SCREEN_Y, true);

	// デルタタイム
	mPreTime = std::chrono::system_clock::now();
	mTotalTime = 0.0f;

	// ESCキーが押されるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		// デルタタイム
		auto nowTime = std::chrono::system_clock::now();
		mDeltaTime = static_cast<float>(
			std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - mPreTime).count() / 1000000000.0);
		mPreTime = nowTime;

		// ゲーム起動時間
		mTotalTime += mDeltaTime;

		// メインへ切替
		SetDrawScreen(mainScreen);

		// 画面を初期化
		ClearDrawScreen();

		// 背景色の描画
		//DrawBox(0, 0, SCREEN_X, SCREEN_Y, 0x0, true);
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, 0x00aaaa, true);

		// 座標の初期化
		mPosX = 10;
		mPosY = 80;
		
		// 通常の描画
		DrawTitle("DrawGraph");
		DrawGraph(mPosX, mPosY, texDragon, true);
		mPosX += PLUS_X;

		//単色
		DrawSimpleColor();
		mPosX += PLUS_X;

		//指定色
		DrawCustomColor();
		mPosX += PLUS_X;

		//円
		DrawCircleColor();
		mPosX += PLUS_X;

		//テクスチャ
		DrawTexture();
		mPosX += PLUS_X;

		//半透明
		DrawAlphaBlend();
		mPosX += PLUS_X;

		//ディザリング
		DrawDithering();
		mPosX += PLUS_X;

		// 座標の初期化
		mPosX = 10;
		mPosY += 180;

		//べイヤーディザ
		DrawBayerDithe();
		mPosX += PLUS_X;

		//グレースケール
		DrawMonotone();
		mPosX += PLUS_X;

		//シンプルセピア
		DrawSimleSepia();
		mPosX += PLUS_X;

		//ノイズ
		DrawNoise();
		mPosX += PLUS_X;

		//モザイク
		DrawMosaic();
		mPosX += PLUS_X;

		//クレヨン
		//DrawCrayon();
		//mPosX += PLUS_X;

		//スクロール
		DrawScroll();
		mPosX += PLUS_X;

		//回転
		DrawRotate();
		mPosX += PLUS_X;

		// 座標の初期化
		mPosX = 10;
		mPosY += 180;

		//渦巻
		DrawSwirl();
		mPosX += PLUS_X;

		//走査線
		DrawScanningLine();
		mPosX += PLUS_X;

		//歪み
		//DrawDistortion();
		//mPosX += PLUS_X;

		//方向ブラー
		DrawDirBlur();
		mPosX += PLUS_X;

		//ブラー
		DrawBlur();
		mPosX += PLUS_X;

		//発光
		DrawFlash();
		mPosX += PLUS_X;

		//法線マップ
		DrawNormalMap();
		mPosX += PLUS_X;

		//ステータスアップ
		DrawStatusUp();
		mPosX += PLUS_X;

		// 座標の初期化
		mPosX = 10;
		mPosY += 180;

		//ステータスダウン
		DrawStatusDown();
		mPosX += PLUS_X;

		//毒
		DrawPoison();
		mPosX += PLUS_X;

		//麻痺
		DrawParalysis();
		mPosX += PLUS_X;


		// 裏画面に描画
		SetDrawScreen(DX_SCREEN_BACK);
		// 画面を初期化
		ClearDrawScreen();
		// 描画
		DrawGraph(0, 0, mainScreen, true);

		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

	}

	// メインスクリーン削除
	DeleteGraph(mainScreen);

}

void MakeSquereVertex(void)
{
	//三角形のポリゴンを2つ作って、くっつけている

	// 毎回頂点データを作成するのは無駄ですが、
	// シェーダー追加時の作業を減らすため、毎フレーム作成

	int cnt = 0;
	float sX = static_cast<float>(mPosX);
	float sY = static_cast<float>(mPosY);
	float eX = static_cast<float>(mPosX + IMG_SIZE_X - 1);
	float eY = static_cast<float>(mPosY + IMG_SIZE_Y - 1);

	// ４頂点の初期化
	for (int i = 0; i < 4; i++)
	{
		mVertex[i].rhw = 1.0f;
		mVertex[i].dif = GetColorU8(255, 255, 255, 255);
		mVertex[i].spc = GetColorU8(255, 255, 255, 255);
		mVertex[i].su = 0.0f;
		mVertex[i].sv = 0.0f;
	}

	// 左上
	mVertex[cnt].pos = VGet(sX, sY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// 右上
	mVertex[cnt].pos = VGet(eX, sY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// 右下
	mVertex[cnt].pos = VGet(eX, eY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 1.0f;
	cnt++;

	// 左下
	mVertex[cnt].pos = VGet(sX, eY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 1.0f;

	/*
	　～～～～～～
		0-----1
		|     |
		|     |
		3-----2
	　～～～～～～
		0-----1
		|  ／
		|／
		3
	　～～～～～～
			  1
		   ／ |
		 ／   |
		3-----2
	　～～～～～～
	*/


	// 頂点インデックス
	cnt = 0;
	mIndex[cnt++] = 0;
	mIndex[cnt++] = 1;
	mIndex[cnt++] = 3;

	mIndex[cnt++] = 1;
	mIndex[cnt++] = 2;
	mIndex[cnt++] = 3;

}

/// <summary>
/// 改行
/// </summary>
/// <param name=""></param>
void NewLine(void)
{
	mPosX = 10;
	mPosY += 180;
}

void DrawTitle(std::string title)
{
	DrawString(mPosX, mPosY + TITLE_Y, title.c_str(), 0x000000);
}

void DrawFrame(void)
{
	DrawBox(mPosX - 1, mPosY - 1, mPosX + IMG_SIZE_X, mPosY + IMG_SIZE_Y, 0x000000, false);
}

void DrawSimpleColor(void)
{
	DrawTitle("単色");

	//シェーダーの設定
	SetUsePixelShader(psSimpleColor);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

	//フレーム
	DrawFrame();
}

void DrawCustomColor(void)
{
	DrawTitle("指定色");

	//シェーダーの設定
	SetUsePixelShader(psCustomColor);
	
	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf = 
		(COLOR_F*)GetBufferShaderConstantBuffer(psCustomColorConstBuf);
	cbBuf->r = 0.0f;
	cbBuf->g = 0.5f;
	cbBuf->b = 0.0f;
	cbBuf->a = 1.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(psCustomColorConstBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(psCustomColorConstBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

	//フレーム
	DrawFrame();
}

void DrawCircleColor(void)
{
	DrawTitle("円");

	auto& cBuf = psCircleColorConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psCircleColor);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 0.4f;
	cbBuf->g = 0.4f;
	cbBuf->b = 0.8f;
	cbBuf->a = 1.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

	//フレーム
	DrawFrame();
}

void DrawTexture(void)
{
	DrawTitle("テクスチャ");

	auto& cBuf = psTextureConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psTexture);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawAlphaBlend(void)
{
	DrawTitle("アルファブレンド");

	auto& cBuf = psAlphaBlendConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psAlphaBlend);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	//cbBuf->a = 0.5f;
	cbBuf->a = 1.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();
}

void DrawDithering(void)
{
	DrawTitle("ディザリング");

	auto& cBuf = psDitheringConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psDithering);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 128;		

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();
}

void DrawBayerDithe(void)
{
	DrawTitle("ベイヤーディザ");

	auto& cBuf = psBayerDitheConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psBayerDithe);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 10;		//ベイヤーレベル
	cbBuf->g = 128;		//画像サイズX
	cbBuf->b = 128;		//画像サイズY

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawMonotone(void)
{
	DrawTitle("グレースケール");

	auto& cBuf = psMonotoneConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psMonotone);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawSimleSepia(void)
{
	DrawTitle("シンプルセピア");

	auto& cBuf = psSimleSepiaConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psSimleSepia);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();
}

void DrawNoise(void)
{
	DrawTitle("ノイズ");

	auto& cBuf = psNoiseConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psNoise);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->g = mDeltaTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawMosaic(void)
{
	DrawTitle("モザイク");

	auto& cBuf = psMosaicConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psMosaic);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 8.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawCrayon(void)
{
	DrawTitle("クレヨン");

	auto& cBuf = psCrayonConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psCrayon);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();
}

void DrawScroll(void)
{
	DrawTitle("スクロール");

	auto& cBuf = psScrollConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psScroll);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 0.3f;
	cbBuf->g = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//アグレッシブモードを設定する
	//SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);
	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawRotate(void)
{
	DrawTitle("回転");

	auto& cBuf = psRotateConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psRotate);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texCircle);
	SetUseTextureToShader(1, texCircleMask);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->g = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawSwirl(void)
{
	DrawTitle("渦巻");

	auto& cBuf = psSwirlConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psSwirl);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 0.5f;
	cbBuf->g = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawScanningLine(void)
{
	DrawTitle("走査線");

	auto& cBuf = psScanningLineConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psScanningLine);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 0.3f;
	cbBuf->g = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();
}

void DrawDistortion(void)
{
	DrawTitle("歪み");

	auto& cBuf = psDistortionConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psDistortion);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);
	//シェーダーにテクスチャを転送
	SetUseTextureToShader(1, texNoize);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 4);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//アグレッシブモードを設定する
	SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);
	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//アグレッシブモードをもとに戻す
	SetTextureAddressModeUV(DX_TEXADDRESS_CLAMP, DX_TEXADDRESS_CLAMP);

	//フレーム
	DrawFrame();
}

void DrawDirBlur(void)
{
	DrawTitle("ブラー");

	auto& cBuf = psDirBlurConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psDirBlur);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawBlur(void)
{
	DrawTitle("ブラー");

	auto& cBuf = psBlurConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psBlur);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->r = 128.0f;
	cbBuf->r = 128.0f;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();
}

void DrawFlash(void)
{
	DrawTitle("発光");

	auto& cBuf = psFlashConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psFlash);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->r = 128.0f;
	cbBuf->r = 128.0f;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawNormalMap(void)
{
	DrawTitle("法線マップ");

	auto& cBuf = psNormalMapConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psNormalMap);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);
	SetUseTextureToShader(1, texDragonNor);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 1.0f;
	cbBuf->g = 1.0f;
	cbBuf->b = 1.0f;
	cbBuf->a = 1.0f;
	cbBuf++;
	cbBuf->r = 1.0f;
	cbBuf->r = 1.0f;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawStatusUp(void)
{
	DrawTitle("ステータスアップ");

	auto& cBuf = psStatusUpConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psStatusUp);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawStatusDown(void)
{
	DrawTitle("ステータスダウン");

	auto& cBuf = psStatusDownConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psStatusDown);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}

void DrawPoison(void)
{
	DrawTitle("毒");

	auto& cBuf = psPoisonConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psPoison);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();


}

void DrawParalysis(void)
{
	DrawTitle("麻痺");

	auto& cBuf = psParalysisConstBuf;

	//シェーダーの設定
	SetUsePixelShader(psParalysis);

	////シェーダーにテクスチャを転送
	SetUseTextureToShader(0, texDragon);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = mTotalTime;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//四角ポリゴン（三角2つ）を生成
	MakeSquereVertex();

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フレーム
	DrawFrame();

}
