#include "EnemyUI.h"

EnemyUI::EnemyUI(
	Vector2 pos, std::string& name,int& hp, int& maxHp, int& beforHp) :
	UnitUI(pos, name, hp, maxHp, beforHp)
{
}

EnemyUI::~EnemyUI()
{
}

void EnemyUI::Init(void)
{
	//初期化
	UnitUI::Init();


	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);
	//HP表示座標
	Vector2 pos = { unitPos_.x + unitSize, unitPos_.y + 20 };
	//四角形ポリゴンの生成(HP用)
	MakeSquereVertex(pos);

	nowHp_ = hp_;

}

void EnemyUI::Draw(void)
{
	//ユニットのサイズ
	auto unitSize = static_cast<int>(UnitBase::DRAWING_SIZE);


	//名前描画
	DrawName(name_, unitPos_);


	//HPが0以下の時、HPゲージを描画しない
	if (nowHp_ <= 0)return;


	//バフアイコンの描画
	DrawBuffIcon();


	//HP枠の表示
	Vector2 pos = { unitPos_.x + unitSize,unitPos_.y + 20 };
	DrawHpFrame(pos);

	//HPゲージの計算
	DecHpGauge();
	//HPの割合
	float ratio = static_cast<float>(nowHp_) / static_cast<float>(maxHp_);
	//HPシェーダー
	COLOR_F color = { 0.8f,0.4f,0.4f,1.0f };
	DrawHpShader(ratio, color);

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
