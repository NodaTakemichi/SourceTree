#include "PlayerUI.h"

PlayerUI::PlayerUI(
	Vector2 pos, std::string& name, int& hp, int& nowHp, int& maxHp, bool& active) :
	UnitUI(pos, name, hp, nowHp, maxHp,active)
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init(void)
{
	//初期化
	UnitUI::Init();

}

void PlayerUI::Draw(void)
{
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);

	COLOR_F color = { 0.4f,0.8f,0.4f,1.0f };	//緑

	//名前描画
	DrawName(name_, unitPos_, color);


	//HPが0以下の時、HPゲージを描画しない
	if (nowHp_ <= 0)return;


	//バフアイコンの描画
	DrawBuffIcon();


	//HP枠の表示
	Vector2 pos = { unitPos_.x - 70 ,unitPos_.y + 20 };
	DrawHpFrame(pos);

	//HPシェーダー
	pos = { unitPos_.x - 70 ,unitPos_.y + 20 };
	DrawHpShader(pos,color);

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
