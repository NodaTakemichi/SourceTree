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
	unitUi_ = new EnemyUI(pos_, name_, nowHp_, maxHp_);
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

	//シェーダー描画
	DrawUnitShader(nowPs_, 0.0f);

	//ネアレストネイバー法
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//UI描画
	unitUi_->Draw();

	//ベースユニットの描画関数
	UnitBase::Draw();

}


