#include <DxLib.h>
#include "../Application.h"
#include "../Utility/DrawShader.h"
#include "../Utility/AsoUtility.h"
#include "../Common/Vector2.h"

#include"../_debug/_DebugDispOut.h"
#include "DeathStaging.h"

DeathStaging* DeathStaging::instance_ = nullptr;

DeathStaging::DeathStaging()
{
}

DeathStaging::~DeathStaging()
{
}

void DeathStaging::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new DeathStaging();
	}
	instance_->Init();
}

DeathStaging& DeathStaging::GetInstance(void)
{
	return *instance_;
}

void DeathStaging::Init(void)
{
	//画像の登録
	frameImg_ = LoadGraph("./Data/Image/UI/Dead_Frame.png");
	maskImg_ = LoadGraph("./Data/Image/UI/Dead_Mask.png");
	unitImg_ = LoadGraph("./Data/Image/Unit/FairySnake.png");
	backImg_ = LoadGraph("./Data/Image/bg/DeadBack.png");

	//シェーダーの登録
	//psTex_ = LoadPixelShader("./x64/Debug/DeathShader.cso");
	psReverTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");
	psMask_ = LoadPixelShader("./x64/Debug/Mask.cso");
	psDeathShader_ = LoadPixelShader("./x64/Debug/DeathUnit.cso");

	//スクリーンの作成
	maskScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	//スクリーンの作成
	deathStagingScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//初期化
	totalTime_ = 0.0f;
	mSizeX_ = 0;
	isPlaying_ = false;
	revers_ = 0.0f;

}

void DeathStaging::Update(void)
{
	if (isPlaying_)
	{
		//サイズ変更
		int x,y;
		GetGraphSize(maskImg_, &x, &y);
		mSizeX_ = min(1.5 * totalTime_ * x, x);

		//時間経過
		float wait = 1.5f;
		bool finish = AsoUtility::OverTime(totalTime_, wait);
		if (finish)
		{
			mSizeX_ = 0;
			totalTime_ = 0.0f;
			isPlaying_ = false;
		}
	}
}

void DeathStaging::Release(void)
{
	DeleteGraph(frameImg_);
	DeleteGraph(maskImg_);
	DeleteGraph(unitImg_);
	DeleteGraph(backImg_);

	DeleteShader(psReverTex_);
	DeleteShader(psMask_);
	DeleteShader(psDeathShader_);
}

void DeathStaging::PlayDeathStaging(void)
{
	if (isPlaying_)
	{
		auto& ds = DrawShader::GetInstance();

		//描画先指定
		SetDrawScreen(maskScreen_);
		ClearDrawScreen();

		//背景描画
		ds.DrawGraphToShader({ 0,0 }, backImg_, psReverTex_, COLOR_F{});
		//ユニット描画
		ds.DrawExtendGraphToShader(
			{ 700,150 }, { 400,400 }, unitImg_, psDeathShader_, COLOR_F{});

		//描画先指定
		SetDrawScreen(deathStagingScreen_);
		ClearDrawScreen();

		//マスク描画
		ds.DrawGraphAndSubToShader(
			{ 0,0 }, {mSizeX_,Application::SCREEN_SIZE_Y },
			maskScreen_, maskImg_, psMask_, COLOR_F{});
		//フレーム描画
		ds.DrawExtendGraphToShader(
			{ 0,0 }, { mSizeX_,Application::SCREEN_SIZE_Y },
			frameImg_, psReverTex_, COLOR_F{});

		//描画先指定
		SetDrawScreen(DX_SCREEN_BACK);
		//死亡演出描画（敵味方によって反転）
		COLOR_F re = COLOR_F{
			revers_
		};
		ds.DrawGraphToShader({ 0,0 }, deathStagingScreen_, psReverTex_, re);

	}

}

void DeathStaging::SetDeathUnit(const int& img, const float& r)
{
	revers_ = r;
	unitImg_ = img;
	isPlaying_ = true;
}


bool DeathStaging::PlayingStaging(void)
{
	return isPlaying_;
}

