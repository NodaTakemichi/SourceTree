#include "../../Application.h"
#include "./UI//EnemyUI.h"
#include "EnemyUnit.h"

EnemyUnit::EnemyUnit()
{
}

EnemyUnit::EnemyUnit(std::string unitFile, int unitNum)
{
	unitFile_ = unitFile;
	unitNum_ = unitNum;

	type_ = UNIT_TYPE::ENEMY;

}

EnemyUnit::~EnemyUnit()
{
}

void EnemyUnit::Init(void)
{
	//ユニットデータのロード
	LoadData(unitFile_.c_str());

	//座標初期化
	auto ScreenX = Application::SCREEN_SIZE_X;
	SetDrawingPos(ScreenX - DRAWING_SIZE - DRAWING_OFFSET_X);

	//UI情報の初期化
	unitUi_ = new EnemyUI(pos_, &name_);
	unitUi_->Init();


	//初期化
	UnitBase::Init();

}


void EnemyUnit::Update(void)
{
}

void EnemyUnit::Draw(void)
{
	//バイリニア補間モード
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//描画
	DrawExtendGraph(pos_.x, pos_.y,
		pos_.x + DRAWING_SIZE, pos_.y + DRAWING_SIZE, img_, true);

	//ネアレストネイバー法
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//UI描画
	unitUi_->Draw();

	//ベースユニットの描画関数
	UnitBase::Draw();

}


