#include <DxLib.h>
#include "../Application.h"
#include "../Utility/DrawShader.h"
#include "../Common/Vector2.h"
#include "DeathStaging.h"

DeathStaging::DeathStaging()
{
}

DeathStaging::~DeathStaging()
{
}

void DeathStaging::Init(void)
{
	//画像の登録
	frameImg_ = LoadGraph("./Data/Image/UI/Dead_Frame.png");
	maskImg_ = LoadGraph("./Data/Image/UI/Dead_Mask.png");
	unitImg_ = LoadGraph("./Data/Image/Unit/フロストレオ.png");
	backImg_ = LoadGraph("./Data/Image/bg/背景.png");

	//シェーダーの登録
	//psTex_ = LoadPixelShader("./x64/Debug/DeathShader.cso");
	psReverTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");
	psMask_ = LoadPixelShader("./x64/Debug/Mask.cso");

	//スクリーンの作成
	maskScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

}

void DeathStaging::Draw(void)
{
	//描画先指定
	SetDrawScreen(maskScreen_);
	ClearDrawScreen();

	auto& sha = DrawShader::GetInstance();
	//背景描画
	sha.DrawGraphToShader({ 0,0 }, backImg_, psReverTex_, COLOR_F{});
	//ユニット描画
	sha.DrawExtendGraphToShader(
		{ 700,150 }, { 400,400 }, unitImg_, psReverTex_, COLOR_F{});

	//描画先指定
	SetDrawScreen(DX_SCREEN_BACK);
	//マスク描画
	sha.DrawGraphAndSubToShader(
		{ 0,0 },  maskScreen_, maskImg_, psMask_, COLOR_F{});
	//フレーム描画
	sha.DrawGraphToShader({ 0,0 }, frameImg_, psReverTex_, COLOR_F{});


}

void DeathStaging::Release(void)
{
	DeleteGraph(frameImg_);
	DeleteGraph(maskImg_);
	DeleteGraph(unitImg_);

	DeleteShader(psReverTex_);
}

void DeathStaging::DrawDeathUnit(void)
{
	//描画先指定
	SetDrawScreen(maskScreen_);
	ClearDrawScreen();

	auto& sha = DrawShader::GetInstance();
	//背景描画
	sha.DrawGraphToShader({ 0,0 }, backImg_, psReverTex_, COLOR_F{});
	//ユニット描画
	sha.DrawGraphToShader({ 300,300 }, unitImg_, psReverTex_, COLOR_F{});

	//描画先指定
	SetDrawScreen(DX_SCREEN_BACK);
	//マスク画面描画
	sha.DrawGraphAndSubToShader(
		{ 300,100 }, maskImg_, maskScreen_, psMask_, COLOR_F{});
	//フレーム描画
	sha.DrawGraphToShader({ 300,100 }, frameImg_, psReverTex_, COLOR_F{});

}

