#include<DxLib.h>
#include "UnitUI.h"

UnitUI::UnitUI()
{
}

UnitUI::~UnitUI()
{
}

void UnitUI::Init(void)
{
	//–¼‘O˜g‚Ì“o˜^
	nameFrameImg_ = LoadGraph("./Data/Image/UI/NameFrame.png");

	//ƒVƒF[ƒ_[‚Ì“o˜^
	//psHpColor_ = LoadPixelShader("./Data/Shader/HpShader.cso");
	psHpColor_ = LoadPixelShader("./x64/Debug/HpShader.cso");
	//ƒsƒNƒZƒ‹ƒVƒF[ƒ_[—p‚Ì’è”ƒoƒbƒtƒ@‚Ìì¬
	psHpColorConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);
}

void UnitUI::Release(void)
{
	DeleteGraph(nameFrameImg_);
	DeleteGraph(hpFrameImg_);

	//ƒVƒF[ƒ_[‚Ì‰ğ•ú
	DeleteShader(psHpColor_);
	DeleteShaderConstantBuffer(psHpColorConstBuf_);
}

void UnitUI::MakeSquereVertex(Vector2 pos)
{
	//OŠpŒ`‚Ìƒ|ƒŠƒSƒ“‚ğ2‚Âì‚Á‚ÄA‚­‚Á‚Â‚¯‚Ä‚¢‚é

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + HP_GAUGE_X - 1);
	float eY = static_cast<float>(pos.y + HP_GAUGE_Y - 1);

	// ‚S’¸“_‚Ì‰Šú‰»
	for (int i = 0; i < 4; i++)
	{
		mVertex[i].rhw = 1.0f;
		mVertex[i].dif = GetColorU8(255, 255, 255, 255);
		mVertex[i].spc = GetColorU8(255, 255, 255, 255);
		mVertex[i].su = 0.0f;
		mVertex[i].sv = 0.0f;
	}

	// ¶ã
	mVertex[cnt].pos = VGet(sX, sY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// ‰Eã
	mVertex[cnt].pos = VGet(eX, sY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// ‰E‰º
	mVertex[cnt].pos = VGet(eX, eY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 1.0f;
	cnt++;

	// ¶‰º
	mVertex[cnt].pos = VGet(sX, eY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 1.0f;

	/*
	@``````
		0-----1
		|     |
		|     |
		3-----2
	@``````
		0-----1
		|  ^
		|^
		3
	@``````
			  1
		   ^ |
		 ^   |
		3-----2
	@``````
	*/


	// ’¸“_ƒCƒ“ƒfƒbƒNƒX
	cnt = 0;
	mIndex[cnt++] = 0;
	mIndex[cnt++] = 1;
	mIndex[cnt++] = 3;

	mIndex[cnt++] = 1;
	mIndex[cnt++] = 2;
	mIndex[cnt++] = 3;

}


