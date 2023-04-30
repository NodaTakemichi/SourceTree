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
	//名前枠の登録
	nameFrameImg_ = LoadGraph("./Data/Image/UI/NameFrame.png");

	//シェーダーの登録
	//psHpColor_ = LoadPixelShader("./Data/Shader/HpShader.cso");
	psHpColor_ = LoadPixelShader("./x64/Debug/HpShader.cso");
	//ピクセルシェーダー用の定数バッファの作成
	psHpColorConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);
}

void UnitUI::Release(void)
{
	DeleteGraph(nameFrameImg_);
	DeleteGraph(hpFrameImg_);

	//シェーダーの解放
	DeleteShader(psHpColor_);
	DeleteShaderConstantBuffer(psHpColorConstBuf_);
}

void UnitUI::MakeSquereVertex(Vector2 pos)
{
	//三角形のポリゴンを2つ作って、くっつけている

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + HP_GAUGE_X - 1);
	float eY = static_cast<float>(pos.y + HP_GAUGE_Y - 1);

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
	　〜〜〜〜〜〜
		0-----1
		|     |
		|     |
		3-----2
	　〜〜〜〜〜〜
		0-----1
		|  ／
		|／
		3
	　〜〜〜〜〜〜
			  1
		   ／ |
		 ／   |
		3-----2
	　〜〜〜〜〜〜
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


