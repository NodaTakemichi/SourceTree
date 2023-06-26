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
	//�摜�̓o�^
	frameImg_ = LoadGraph("./Data/Image/UI/Dead_Frame.png");
	maskImg_ = LoadGraph("./Data/Image/UI/Dead_Mask.png");
	unitImg_ = LoadGraph("./Data/Image/Unit/�t���X�g���I.png");
	backImg_ = LoadGraph("./Data/Image/bg/�w�i.png");

	//�V�F�[�_�[�̓o�^
	//psTex_ = LoadPixelShader("./x64/Debug/DeathShader.cso");
	psReverTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");
	psMask_ = LoadPixelShader("./x64/Debug/Mask.cso");

	//�X�N���[���̍쐬
	maskScreen_ = MakeScreen(
		Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, true);

}

void DeathStaging::Draw(void)
{
	//�`���w��
	SetDrawScreen(maskScreen_);
	ClearDrawScreen();

	auto& sha = DrawShader::GetInstance();
	//�w�i�`��
	sha.DrawGraphToShader({ 0,0 }, backImg_, psReverTex_, COLOR_F{});
	//���j�b�g�`��
	sha.DrawExtendGraphToShader(
		{ 700,150 }, { 400,400 }, unitImg_, psReverTex_, COLOR_F{});

	//�`���w��
	SetDrawScreen(DX_SCREEN_BACK);
	//�}�X�N�`��
	sha.DrawGraphAndSubToShader(
		{ 0,0 },  maskScreen_, maskImg_, psMask_, COLOR_F{});
	//�t���[���`��
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
	//�`���w��
	SetDrawScreen(maskScreen_);
	ClearDrawScreen();

	auto& sha = DrawShader::GetInstance();
	//�w�i�`��
	sha.DrawGraphToShader({ 0,0 }, backImg_, psReverTex_, COLOR_F{});
	//���j�b�g�`��
	sha.DrawGraphToShader({ 300,300 }, unitImg_, psReverTex_, COLOR_F{});

	//�`���w��
	SetDrawScreen(DX_SCREEN_BACK);
	//�}�X�N��ʕ`��
	sha.DrawGraphAndSubToShader(
		{ 300,100 }, maskImg_, maskScreen_, psMask_, COLOR_F{});
	//�t���[���`��
	sha.DrawGraphToShader({ 300,100 }, frameImg_, psReverTex_, COLOR_F{});

}

