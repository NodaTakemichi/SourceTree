#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#include "./UI/PlayerUI.h"
#include "PlayerUnit.h"


PlayerUnit::PlayerUnit(const int& dataNum, const int& unitNum) :
	UnitBase(dataNum, unitNum)
{
	type_ = UNIT_TYPE::PLAYER;
}


PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::Init(void)
{
	//座標初期化
	SetDrawingPos(DRAWING_OFFSET_X);


	//UI情報の初期化
	unitUi_ = new PlayerUI(pos_, name_, hp_ ,changeHp_, maxHp_);
	unitUi_->Init();

	//初期化
	UnitBase::Init();
	
}

void PlayerUnit::Update(void)
{
	//if (CheckHitKey(KEY_INPUT_UP))pos_.y -= 1;
	//if (CheckHitKey(KEY_INPUT_DOWN))pos_.y += 1;
	//if (CheckHitKey(KEY_INPUT_LEFT))pos_.x -= 1;
	//if (CheckHitKey(KEY_INPUT_RIGHT))pos_.x += 1;
	//
	//_dbgDrawFormatString(0.0f, 150.0f, 0xff00ff, "{%d,%d}", pos_.x, pos_.y);


}

void PlayerUnit::Draw(void)
{

	//ユニット画像描画
	DrawUnitShader(1.0f);


	//UI描画
	unitUi_->Draw();

	//ベースユニットの描画関数
	UnitBase::Draw();

}


