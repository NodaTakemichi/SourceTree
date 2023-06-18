#include <DxLib.h>
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

	//psTex_ = LoadPixelShader("./x64/Debug/DeathShader.cso");
	psTex_ = LoadPixelShader("./x64/Debug/Texture.cso");
	psTexConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 8);

}

void DeathStaging::Draw(void)
{
	COLOR_F test = COLOR_F{
		1.0f
	};
	//DrawShader::GetInstance().DrawGraphToShader({ 0,0 }, unitImg_, psTex_, test);
	//DrawShader::GetInstance().DrawExtendGraphToShader(
	//	{ 0,0 }, { 300,300 }, unitImg_, psTex_, test);

	//DrawShader();
	//DrawGraph(400, 0, frameImg_, true);
}

void DeathStaging::Release(void)
{
	DeleteGraph(frameImg_);
	DeleteGraph(maskImg_);
	DeleteGraph(unitImg_);

	DeleteShader(psTex_);
	DeleteShaderConstantBuffer(psTexConstBuf_);
}

void DeathStaging::DrawStaging(void)
{
}
