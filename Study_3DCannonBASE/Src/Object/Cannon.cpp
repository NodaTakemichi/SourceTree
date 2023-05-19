#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "./ShotBase.h"
#include "Cannon.h"

Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}

void Cannon::Init(void)
{
	//爆発エフェクト読み込み
	LoadDivGraph((Application::PATH_IMAGE + "Blast.png").c_str(),
		BLAST_ANIM_NUM, 4,4, BLAST_SIZE_X, BLAST_SIZE_Y, blastImgs_, true);

	//3D基本情報の初期化
	//土台
	standModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Stand.mv1").c_str());
	standScl_ = { 0.8f, 0.8f, 0.8f };
	standRot_ = { 0.0f, 0.0f, 0.0f };
	standPos_ = { 0.0f, 10.0f, -200.0f };

	//相対座標
	barrelLocalos_ = { 0.0f, 100.0f, 0.0f };
	//砲身
	barrelModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Barrel.mv1").c_str());
	barrelScl_ = { 0.8f, 0.8f, 0.8f };
	barrelRot_ = { 0.0f, 0.0f, 0.0f };
	barrelPos_ = VAdd(standPos_, barrelLocalos_);

	//弾
	shotModelId_ = MV1LoadModel(
		(Application::PATH_MODEL + "Cannon/Shot.mv1").c_str());
	stepShotDelay_ = 0.0f;

	//初期設定をモデルに反映
	Update();
}

void Cannon::Update(void)
{
	//砲身の回転処理
	ProcessRot();

	//処理
	ProcessShot();

	//土台
	MV1SetScale(standModelId_, standScl_);
	MV1SetPosition(standModelId_, standPos_);
	MV1SetRotationXYZ(standModelId_, standRot_);

	//砲身
	MV1SetScale(barrelModelId_, barrelScl_);
	MV1SetPosition(barrelModelId_, barrelPos_);
	MV1SetRotationXYZ(barrelModelId_, barrelRot_);

}

void Cannon::Draw(void)
{
	MV1DrawModel(standModelId_);
	MV1DrawModel(barrelModelId_);

#ifdef DEBUG


	// 弾の発射位置
	VECTOR pos = barrelPos_;
	// 砲身からの相対座標
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };

	MATRIX matRot = MGetIdent();
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));
	VECTOR localRotPos = VTransform(localPos, matRot);

	// ローカル座標からワールド座標へ変換
	pos = VAdd(pos, localRotPos);
	// 弾の発射位置目安
	DrawSphere3D(pos, 10.0f, 10, 0x00ff00, 0x00ff00, true);
	// 砲台のモデル描画
	MV1DrawModel(standModelId_);
	// 砲身のモデル描画(一時的に半透明にする)
	MV1SetMaterialDifColor(barrelModelId_, 0, GetColorF(1.0f, 1.0f, 1.0f, 0.5f));
	MV1DrawModel(barrelModelId_);
#endif // _DEBUG

}

void Cannon::Release(void)
{
	MV1DeleteModel(standModelId_);
	MV1DeleteModel(barrelModelId_);
	MV1DeleteModel(shotModelId_);

	for (auto shot : shots_)
	{
		shot->Release();
		delete shot;
	}

	for (int i = 0; i < BLAST_ANIM_NUM; i++)
	{
		DeleteGraph(blastImgs_[i]);
	}
}

void Cannon::ProcessRot(void)
{
	auto& ins = InputManager::GetInstance();

	//回転量
	auto rotPow = 1.0f * DX_PI_F / 180.0f;

	//左右
	if (ins.IsNew(KEY_INPUT_LEFT))standRot_.y -= rotPow;
	if (ins.IsNew(KEY_INPUT_RIGHT))standRot_.y += rotPow;
	barrelRot_.y = standRot_.y;

	//上下
	if ((barrelRot_.x <= MAX_ANGLE_X) && (ins.IsNew(KEY_INPUT_DOWN)))barrelRot_.x += rotPow;
	if ((barrelRot_.x > MN_ANGLE_X) && (ins.IsNew(KEY_INPUT_UP)))barrelRot_.x -= rotPow;
}

void Cannon::ProcessShot(void)
{
	auto& ins = InputManager::GetInstance();

	//砲身の方向
#pragma region 行列
	//①回転行列を作る
	//単位行列
	MATRIX matRot = MGetIdent();

	///それぞれの軸の行列を作り、さらに行列を合成する
	matRot = MMult(matRot, MGetRotX(barrelRot_.x));
	matRot = MMult(matRot, MGetRotY(barrelRot_.y));
	matRot = MMult(matRot, MGetRotZ(barrelRot_.z));

	//②方向を回転させる
	//回転行列を使用して、ベクトルを回転させる
	VECTOR dir = VTransform({ 0.0f,0.0f,1.0f }, matRot);

	// 弾の発射位置
	VECTOR pos = barrelPos_;
	// 砲身からの相対座標
	VECTOR localPos = { 0.0f, 25.0f, 30.0f };
	VECTOR localRotPos = VTransform(localPos, matRot);
	// ローカル座標からワールド座標へ変換
	pos = VAdd(pos, localRotPos);
#pragma endregion


	//発射
	if (ins.IsNew(KEY_INPUT_Z) && stepShotDelay_ <= 0.0f)
	{
		// 有効な弾を取得する
		ShotBase* shot = GetValidShot();
		// 弾を生成
		shot->CreateShot(pos, dir);
		// 弾発射後の硬直時間セット
		stepShotDelay_ = SHOT_DELAY;
	}

	// 弾発射後の硬直時間を減らしていく
	if (stepShotDelay_ > 0.0f) {
		stepShotDelay_ -= 1.0f / SceneManager::DEFAULT_FPS;
	}
}

ShotBase* Cannon::GetValidShot(void)
{
	//使っていない弾があったら、再利用する
	size_t size = shots_.size();
	for (int i = 0; i < size; i++)
	{
		if (!shots_[i]->IsAlive())
		{
			return shots_[i];
		}
	}

	//使っていない弾がない場合、新しく作る
	ShotBase* shot = new ShotBase(shotModelId_, blastImgs_, BLAST_ANIM_NUM);
	shots_.push_back(shot);
	return shot;
}

std::vector<ShotBase*> Cannon::GetShots(void)
{
	return shots_;
}
