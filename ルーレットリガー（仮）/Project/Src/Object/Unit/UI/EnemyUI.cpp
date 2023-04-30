#include "EnemyUI.h"

EnemyUI::EnemyUI(Vector2 pos, std::string* name):
unitPos_(pos), name_(name)
{
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::Init(void)
{
	//初期化
	UnitUI::Init();

	//HP座標
	Vector2 pos;
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);

	hpFrameImg_ = LoadGraph("./Data/Image/UI/HP_E.png");
	pos = { unitPos_.x + unitSize - 10, unitPos_.y + 20 };


	//四角形ポリゴンの生成(HP用)
	MakeSquereVertex(pos);

}

void EnemyUI::Draw(void)
{
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);

	//HPの表示
	Vector2 pos = { unitPos_.x + unitSize - 10,unitPos_.y + 20 };
	//HPの枠
	auto frame = 2;
	DrawBox(pos.x - frame, pos.y - frame,
		pos.x + HP_GAUGE_X + frame, pos.y + HP_GAUGE_Y + frame,
		0xffffff, true);


#pragma region HPシェーダー
	//シェーダーの設定
	SetUsePixelShader(psHpColor_);

	//シェーダー用の定数バッファ
	auto& cBuf = psHpColorConstBuf_;

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = 0.7f;
	cbBuf->g = 0.3f;
	cbBuf->b = 0.3f;
	cbBuf->a = 1.0f;

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//描画
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
#pragma endregion

#pragma region 名前
	//名前の表示
	pos = { unitPos_.x - 10,unitPos_.y + 140 };
	DrawTurnGraph(pos.x, pos.y, nameFrameImg_, true);

	//名前　文字列
	auto name = name_->c_str();
	//文字列の文字数の取得
	int len = strlen(name);
	//文字列の（半分の）長さを取得
	auto fx = GetDrawStringWidth(name, len) / 2;
	pos = { unitPos_.x + unitSize / 2,unitPos_.y + 152 };
	//名前描画
	DrawString(pos.x - fx, pos.y, name, 0xffffff);
#pragma endregion

}

void EnemyUI::Release(void)
{
}

void EnemyUI::DrawActUnit(void)
{
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);

	Vector2 pos = { unitPos_.x - 20,unitPos_.y + unitSize / 2 };

	DrawCircle(pos.x, pos.y, 12, 0xff8888, true);

}

void EnemyUI::DrawRockOn(void)
{
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 pos = { unitPos_.x - 20,unitPos_.y + unitSize / 2 + 20 };
	DrawCircle(pos.x, pos.y, 12, 0x8888ff, true);

}
