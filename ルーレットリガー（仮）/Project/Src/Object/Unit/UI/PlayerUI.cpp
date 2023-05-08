#include "PlayerUI.h"

PlayerUI::PlayerUI(Vector2 pos, std::string& name,int& hp, int& maxHp, int& beforHp):
unitPos_(pos), name_(name), hp_(hp), maxHp_(maxHp), beforHp_(beforHp)
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
	Vector2 pos = { unitPos_.x - 20,unitPos_.y + 20 };
	//四角形ポリゴンの生成(HP用)
	MakeSquereVertex(pos);

	nowHp_ = hp_;

}

void PlayerUI::Draw(void)
{

	//名前描画
	DrawName(name_, unitPos_);


	//HPが0以下の時、HPゲージを描画しない
	if (hp_ <= 0)return;

	//HP枠の表示
	Vector2 pos = { unitPos_.x - 20,unitPos_.y + 20 };
	auto frame = 2;
	DrawBox(pos.x - frame, pos.y - frame,
		pos.x + HP_GAUGE_X + frame, pos.y + HP_GAUGE_Y + frame,
		0xffffff, true);


	auto test = 1.0f;
	auto changeTime = 1.0f;
	//HP変化があるときのみ
	if (nowHp_ != hp_)
	{
		//（完了する時間ー経過時間）/干渉する時間
		auto delet = SceneManager::GetInstance().GetDeltaTime();
		totalTime_ += delet;
		test = (changeTime - totalTime_) / changeTime;
		if (test >= 1.0f)
		{
			test = 1.0f;
			totalTime_ = 0.0f;
			nowHp_ = hp_;
		}
		//BeforHPを入れる
		nowHp_ = AsoUtility::Lerp(hp_, beforHp_,  test);
	}
	else
	{
		test = 1.0f;
		totalTime_ = 0.0f;
		nowHp_ = hp_;
	}

	//auto test = 1.0f;
	////HP変化があるときのみ
	//if (nowHp_ > hp_)
	//{
	//	//（完了する時間ー経過時間）/干渉する時間
	//	auto delet = SceneManager::GetInstance().GetDeltaTime();
	//	totalTime_ += delet;
	//	test = (1.5f - totalTime_) / 1.5f;
	//	if (test >= 1.0f)
	//	{
	//		test = 1.0f;
	//		totalTime_ = 0.0f;
	//		nowHp_ = hp_;
	//	}
	//	//BeforHPを入れる
	//	nowHp_ = AsoUtility::Lerp(hp_, beforHp_, test);
	//}
	//else
	//{
	//	test = 1.0f;
	//	totalTime_ = 0.0f;
	//	nowHp_ = hp_;
	//}


	//HPの割合
	float ratio = static_cast<float>(nowHp_) / static_cast<float>(maxHp_);
	//HPシェーダー
	COLOR_F color = { 0.4f,0.8f,0.4f,1.0f };
	DrawHpShader(ratio, color);

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
	Vector2 pos = { unitPos_.x + unitSize + 20,unitPos_.y + unitSize / 2 + 20 };


	DrawCircle(pos.x, pos.y, 12, 0x8888ff, true);

}
