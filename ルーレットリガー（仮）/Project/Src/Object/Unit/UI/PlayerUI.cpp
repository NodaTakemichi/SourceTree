#include "PlayerUI.h"

PlayerUI::PlayerUI(
	Vector2 pos, std::string& name, int& hp, int& nowHp, int& maxHp) :
	UnitUI(pos, name, hp, nowHp, maxHp)
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init(void)
{
	//初期化
	UnitUI::Init();

	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	//HP座標
	Vector2 pos = { unitPos_.x - 70 ,unitPos_.y + 20 };
	//四角形ポリゴンの生成(HP用)
	MakeSquereVertex(pos);

}

void PlayerUI::Draw(void)
{

	//名前描画
	DrawName(name_, unitPos_);


	//HPが0以下の時、HPゲージを描画しない
	if (nowHp_ <= 0)return;


	//バフアイコンの描画
	DrawBuffIcon();


	//HP枠の表示
	Vector2 pos = { unitPos_.x - 70 ,unitPos_.y + 20 };
	DrawHpFrame(pos);
	//HPの数値表示
	DrawFormatString(
		pos.x + HP_GAUGE_X +10 , pos.y + HP_GAUGE_Y - 32,
		0xffffff, "HP\n%d", nowHp_);

	//HPシェーダー
	COLOR_F color = { 0.4f,0.8f,0.4f,1.0f };
	DrawHpShader(color);

	//描画
	UnitUI::Draw();

}

void PlayerUI::DrawActUnit(void)
{
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);

	Vector2 pos = { unitPos_.x + unitSize + 20,unitPos_.y + unitSize / 2 };
	

	DrawCircle(pos.x, pos.y, 12, 0xff8888, true);

}

void PlayerUI::DrawRockOn(void)
{
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	Vector2 pos = { unitPos_.x + unitSize ,unitPos_.y + unitSize / 4 };

	DrawGraph(pos.x, pos.y, targetImg_, true);

}
