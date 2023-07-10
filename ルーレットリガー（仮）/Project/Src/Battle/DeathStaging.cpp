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
	//�摜�̓o�^
	frameImg_ = LoadGraph("./Data/Image/UI/Dead_Frame.png");
	maskImg_ = LoadGraph("./Data/Image/UI/Dead_Mask.png");
	unitImg_ = LoadGraph("./Data/Image/Unit/FairySnake.png");
	backImg_ = LoadGraph("./Data/Image/bg/DeadBack.png");

	//�V�F�[�_�[�̓o�^
	//psTex_ = LoadPixelShader("./x64/Debug/DeathShader.cso");
	psReverTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");
	psMask_ = LoadPixelShader("./x64/Debug/Mask.cso");
	psDeathShader_ = LoadPixelShader("./x64/Debug/DeathUnit.cso");

	//�X�N���[���̍쐬
	maskScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);
	//�X�N���[���̍쐬
	deathStagingScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

	//������
	totalTime_ = 0.0f;
	mSizeX_ = 0;
	isPlaying_ = false;
	revers_ = 0.0f;

}

void DeathStaging::Update(void)
{
	if (isPlaying_)
	{
		//�T�C�Y�ύX
		int x,y;
		GetGraphSize(maskImg_, &x, &y);
		mSizeX_ = min(1.5 * totalTime_ * x, x);

		//���Ԍo��
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

		//�`���w��
		SetDrawScreen(maskScreen_);
		ClearDrawScreen();

		//�w�i�`��
		ds.DrawGraphToShader({ 0,0 }, backImg_, psReverTex_, COLOR_F{});
		//���j�b�g�`��
		ds.DrawExtendGraphToShader(
			{ 700,150 }, { 400,400 }, unitImg_, psDeathShader_, COLOR_F{});

		//�`���w��
		SetDrawScreen(deathStagingScreen_);
		ClearDrawScreen();

		//�}�X�N�`��
		ds.DrawGraphAndSubToShader(
			{ 0,0 }, {mSizeX_,Application::SCREEN_SIZE_Y },
			maskScreen_, maskImg_, psMask_, COLOR_F{});
		//�t���[���`��
		ds.DrawExtendGraphToShader(
			{ 0,0 }, { mSizeX_,Application::SCREEN_SIZE_Y },
			frameImg_, psReverTex_, COLOR_F{});

		//�`���w��
		SetDrawScreen(DX_SCREEN_BACK);
		//���S���o�`��i�G�����ɂ���Ĕ��]�j
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

