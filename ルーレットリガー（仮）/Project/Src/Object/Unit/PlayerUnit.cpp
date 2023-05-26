#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

#include "./UI/PlayerUI.h"
#include "PlayerUnit.h"

PlayerUnit::PlayerUnit()
{
}

PlayerUnit::PlayerUnit(std::string unitFile,int unitNum)
{
	unitFile_ = unitFile;
	unitNum_ = unitNum;

	type_ = UNIT_TYPE::PLAYER;
}

PlayerUnit::~PlayerUnit()
{
}

void PlayerUnit::Init(void)
{
	//ユニットデータのロード
	LoadData(unitFile_.c_str());

	//座標初期化
	SetDrawingPos(DRAWING_OFFSET_X);


	//UI情報の初期化
	unitUi_ = new PlayerUI(pos_, name_, hp_ ,nowHp_, maxHp_);
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
	//バイリニア補間モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//シェーダー描画
	DrawUnitShader(nowPs_,1.0f);

	//ネアレストネイバー法
	SetDrawMode(DX_DRAWMODE_NEAREST);


	//UI描画
	unitUi_->Draw();

	//ベースユニットの描画関数
	UnitBase::Draw();

}


