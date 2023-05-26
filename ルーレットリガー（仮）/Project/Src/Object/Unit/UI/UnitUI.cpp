#include<DxLib.h>
#include"../../../_debug/_DebugConOut.h"
#include"../../../Manager/SceneManager.h"

#include "UnitUI.h"

UnitUI::UnitUI(
	Vector2 pos, std::string& name, int& hp, int& nowHp, int& maxHp) :
	unitPos_(pos), name_(name), hp_(hp), nowHp_(nowHp), maxHp_(maxHp)
{
}

UnitUI::~UnitUI()
{
}

void UnitUI::Init(void)
{
	//名前枠,ターゲット画像の登録
	nameFrameImg_ = LoadGraph("./Data/Image/UI/NameFrame.png");
	targetImg_ = LoadGraph("./Data/Image/UI/target.png");

	//シェーダーの登録
	//psHpColor_ = LoadPixelShader("./Data/Shader/HpShader.cso");
	psHpColor_ = LoadPixelShader("./x64/Debug/HpShader.cso");
	//ピクセルシェーダー用の定数バッファの作成
	psHpColorConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 8);

	//テスト
	icon_[0] = LoadGraph("./Data/Image/Icon/麻痺.png");
	icon_[1] = LoadGraph("./Data/Image/Icon/毒.png");
	icon_[2] = LoadGraph("./Data/Image/Icon/混乱.png");
	icon_[3] = LoadGraph("./Data/Image/Icon/Avoidance.png");
	icon_[4] = LoadGraph("./Data/Image/Icon/A_UP.png");
	icon_[5] = LoadGraph("./Data/Image/Icon/A_DOWN.png");
	icon_[6] = LoadGraph("./Data/Image/Icon/S_UP.png");
	icon_[7] = LoadGraph("./Data/Image/Icon/S_DOWN.png");
	icon_[8] = LoadGraph("./Data/Image/Icon/D_UP.png");
	icon_[9] = LoadGraph("./Data/Image/Icon/D_DOWN.png");

	//ダメージフレーム画像
	dmgFrameImg_= LoadGraph("./Data/Image/UI/DmgNum.png");
	//ダメージフォント
	dmgFontHandle_= CreateFontToHandle("零ゴシック", 40, 20, -1);
	//ダメージ描画
	dmgNumDrawing_ = false;	//ダメージを true:表示 , false:非表示

}

void UnitUI::Draw(void)
{
	//ダメージ数値の表示
	if (dmgNumDrawing_)
	{
		DrawGraph(unitPos_.x - 50, unitPos_.y, dmgFrameImg_, true);
		//数値
		DrawFormatStringToHandle(
			unitPos_.x ,
			unitPos_.y + 25,
			0xff0000, dmgFontHandle_,
			"%d", dmg_);
	}
}

void UnitUI::Release(void)
{
	DeleteGraph(nameFrameImg_);

	//シェーダーの解放
	DeleteShader(psHpColor_);
	DeleteShaderConstantBuffer(psHpColorConstBuf_);
}

void UnitUI::SetBuff(std::vector<Buff*> buffs)
{
	buffs_ = buffs;
}

void UnitUI::SetDmg(const bool& drawing, const int& dmg)
{
	dmgNumDrawing_ = drawing;
	dmg_ = dmg;

	return;
}

void UnitUI::DrawHpShader(const COLOR_F& color)
{
	//シェーダーの設定
	SetUsePixelShader(psHpColor_);

	//シェーダー用の定数バッファ
	auto& cBuf = psHpColorConstBuf_;

	//HPの割合
	float nowRatio = static_cast<float>(nowHp_) / static_cast<float>(maxHp_);
	float hpRatio = static_cast<float>(hp_) / static_cast<float>(maxHp_);


	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = color.r;
	cbBuf->g = color.g;
	cbBuf->b = color.b;
	cbBuf->a = color.a;
	cbBuf++;
	cbBuf->r = nowRatio;	//減少HP割合
	cbBuf->g = hpRatio;		//HP割合


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//描画
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

}

void UnitUI::DrawHpFrame(const Vector2& pos)
{
	//HPフレームの描画
	auto frame = 2;
	DrawBox(pos.x - frame, pos.y - frame,
		pos.x + HP_GAUGE_X + frame, pos.y + HP_GAUGE_Y + frame,
		0xffffff, true);
}

void UnitUI::DrawName(const std::string& name, const Vector2& uPos)
{
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 fPos = { uPos.x - 10,uPos.y + 140 };
	Vector2 nPos = { uPos.x + unitSize / 2,uPos.y + 152 };

	//名前枠の表示
	DrawGraph(fPos.x, fPos.y, nameFrameImg_, true);

	//名前　文字列
	auto n = name.c_str();
	//文字列の文字数の取得
	int len = strlen(n);
	//文字列の（半分の）長さを取得
	auto fx = GetDrawStringWidth(n, len) / 2;
	//名前描画
	DrawString(nPos.x - fx, nPos.y, n, 0xffffff);

}

void UnitUI::DrawBuffIcon()
{
	//バフアイコンの描画
	int i = 0;
	for (auto& buff : buffs_)
	{
		if(!buff->IsAlive())continue;

		int num = 0;
		switch (buff->GetBuff())
		{
		case Buff::BUFF_TYPE::PALALYSIS:
			num = 0;
			break;
		case Buff::BUFF_TYPE::POISON:
			num = 1;
			break;
		case Buff::BUFF_TYPE::CONFUSION:
			num = 2;
			break;
		case Buff::BUFF_TYPE::AVOIDANCE:
			num = 3;
			break;

		case Buff::BUFF_TYPE::A_UP:
			num = 4;
			break;
		case Buff::BUFF_TYPE::A_DOWN:
			num = 5;
			break;
		case Buff::BUFF_TYPE::S_UP:
			num = 6;
			break;
		case Buff::BUFF_TYPE::S_DOWN:
			num = 7;
			break;
		case Buff::BUFF_TYPE::D_UP:
			num = 8;
			break;
		case Buff::BUFF_TYPE::D_DOWN:
			num = 9;
			break;

		default:
			return;
		}

		//バイリニア補間モード
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		int s = 32;
		Vector2 iPos = { unitPos_.x + (i * 36) + 10, unitPos_.y + 130 };
		DrawExtendGraph(iPos.x, iPos.y, iPos.x + s, iPos.y + s, icon_[num], true);
		i++;

		//ネアレストネイバー法
		SetDrawMode(DX_DRAWMODE_NEAREST);
	}
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


