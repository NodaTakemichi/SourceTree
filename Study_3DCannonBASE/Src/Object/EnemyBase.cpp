#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Utility/AsoUtility.h"
#include "EnemyBase.h"
EnemyBase::EnemyBase()
{
	//シェーダーの登録
	psHpShader_ = LoadPixelShader("./HpShader.pso");
	//ピクセルシェーダー用の定数バッファの作成
	psHpShaderConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);

	MakeSquereVertex({ 0,0 });
}

EnemyBase::~EnemyBase(void)
{
}

void EnemyBase::Init(void)
{
	SetParam();
	Update();
}

void EnemyBase::SetParam(void)
{
	// 使用メモリ容量と読み込み時間の削減のため
	// モデルデータをいくつもメモリ上に存在させない

	// 角度の設定
	rot_ = { 0.0f, -90.0f * DX_PI_F / 180.0f, 0.0f };
	// 位置の設定
	pos_ = { -320.0f, 30.0f, 75.0f };
	// 右方向に移動する
	dir_ = { 1.0f, 0.0f, 0.0f };
	// 初期は生存状態
	SetAlive(true);

	// 再生中のアニメーション時間
	stepAnim_ = 0.0f;
	// アニメーション速度
	speedAnim_ = 30.0f;

	//合計時間
	hpLerpTime_ = 0.0f;
	totalTime_ = 0.0f;

	//キャラ別に初期化する
	auto parInit = [&](std::string pass ,float scale,float speed,
		int animNo,int hp,float colRadius,float colLocalPos) {
		//モデルの登録
		modelId_ = MV1LoadModel(
			(Application::PATH_MODEL + pass.c_str()).c_str());

		// 大きさの設定
		scl_ = { scale, scale, scale };

		// 移動スピード
		speed_ = speed;

		// アニメーションをアタッチする
		animAttachNo_ = MV1AttachAnim(modelId_, animNo);
		// アタッチしているアニメーションの総再生時間を取得する
		animTotalTime_ = MV1GetAttachAnimTotalTime(modelId_, animAttachNo_);

		// HPの設定
		hp_ = hpMax_ = hpNow_ = hpBefore_ = hp;
		// 衝突判定用の球体半径
		collisionRadius_ = colRadius;
		// 衝突判定用の球体中心の調整座標
		collisionLocalPos_ = { 0.0f, colLocalPos, 0.0f };

	};

	switch (type_)
	{
	case EnemyBase::ENEMY_TYPE::SMALL:
		parInit("Enemy/Birb.mv1",0.3f, 1.5f, 10, 4, 35.0f, 50.0f);
		break;
	case EnemyBase::ENEMY_TYPE::MEDIUM:
		parInit("Enemy/Birb.mv1",0.3f, 1.2f, 10, 4, 40.0f, 50.0f);
		break;
	case EnemyBase::ENEMY_TYPE::BAT:
		break;
	case EnemyBase::ENEMY_TYPE::BIG:
		parInit("Enemy/Ghost.mv1",1.0f, 1.0f, 6, 6, 100.0f, 150.0f);
		break;
	default:
		break;
	}
}

void EnemyBase::Update(void)
{
	//生存状態じゃなければ、処理をしない
	if (!IsAlive())return;

	//合計時間
	totalTime_ += SceneManager::GetInstance().GetDeltaTime();

	// アニメーション再生
	// 経過時間の取得
	float deltaTime = 1.0f / SceneManager::DEFAULT_FPS;
	// アニメーション時間の進行
	stepAnim_ += (speedAnim_ * deltaTime);
	if (stepAnim_ > animTotalTime_)
	{
		// ループ再生
		stepAnim_ = 0.0f;
	}
	// 再生するアニメーション時間の設定
	MV1SetAttachAnimTime(modelId_, animAttachNo_, stepAnim_);
	//移動量
	auto movePow = VScale(dir_, speed_);
	//移動処理
	pos_ = VAdd(pos_, movePow);


	//3D基本情報の更新
	MV1SetScale(modelId_, scl_);
	MV1SetPosition(modelId_, pos_);
	MV1SetRotationXYZ(modelId_, rot_);

}

void EnemyBase::Draw(void)
{
#ifdef DEBUG
	DrawSphere3D(GetCollisionPos(), collisionRadius_, 10, 0xff0000, 0xff0000, false);
#endif // _DEBUG

	//モデル描画(死亡時は、表示しない)
	if (IsAlive())	MV1DrawModel(modelId_);

	//HP枠
	int screenX = Application::SCREEN_SIZE_X;
	int screenY = Application::SCREEN_SIZE_Y;
	int dx = 300;
	int dy = 30;
	VECTOR pos = { screenX - 50 - dx, 50 };
	int offset = 3;
	DrawBox(pos.x - offset-30, pos.y - offset,
		pos.x + offset + dx, pos.y + offset + dy, 0x0, true);
	DrawString(pos.x - offset-20, pos.y - offset+10, "HP", 0xffffff);

#pragma region HPシェーダーの描画
	//シェーダーの設定
	SetUsePixelShader(psHpShader_);
	//シェーダー用の定数バッファ
	auto& cBuf = psHpShaderConstBuf_;

	//減少中のみ、HPの線形補間を行う
	if (hp_ != hpBefore_)
	{
		//HPの線形補間
		hpLerpTime_ += SceneManager::GetInstance().GetDeltaTime();
		auto t =  hpLerpTime_/ 0.3f;

		//タイム越え
		if (t >= 1.0f)
		{
			hpNow_ = hp_;
			hpLerpTime_ = 0.0f;
			hpBefore_ = hp_;
		}
		else
		{
			//HPの線形補間
			hpNow_ = AsoUtility::Lerp(
				static_cast<float>(hpBefore_), 
				static_cast<float>(hp_), t);
		}
	}
	//HPの割合
	auto ratio = hpNow_ / static_cast<float>(hpMax_);

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = ratio;
	cbBuf->g = totalTime_;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);
	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);
	//描画
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);

#pragma endregion
}

void EnemyBase::Release(void)
{
	MV1DeleteModel(modelId_);

	//シェーダーの解放
	DeleteShader(psHpShader_);
	DeleteShaderConstantBuffer(psHpShaderConstBuf_);
}

void EnemyBase::SetEnemyType(ENEMY_TYPE type)
{
	type_ = type;
}

VECTOR EnemyBase::GetPos(void)
{
	return pos_;
}

void EnemyBase::SetPos(VECTOR pos)
{
	pos_ = pos;
}

bool EnemyBase::IsAlive(void)
{
	return isAlive_;
}

void EnemyBase::SetAlive(bool alive)
{
	isAlive_ = alive;
}

void EnemyBase::Damage(int damage)
{
	hpBefore_ = hp_;
	hp_ -= damage;
	if (hp_ <= 0)
	{
		SetAlive(false);
	}
}

VECTOR EnemyBase::GetCollisionPos(void)
{
	//衝突用の球体情報
	auto pos= VAdd(collisionLocalPos_, pos_);
	return pos;
}

void EnemyBase::MakeSquereVertex(Vector2 pos)
{
	int screenX = Application::SCREEN_SIZE_X;
	int screenY = Application::SCREEN_SIZE_Y;

	int dx = 300;
	int dy = 30;
	
	VECTOR ePos = { screenX - 50 - dx, 50 };

	int cnt = 0;
	float sX = static_cast<float>(ePos.x);
	float sY = static_cast<float>(ePos.y);
	float eX = static_cast<float>(ePos.x + dx);
	float eY = static_cast<float>(ePos.y + dy);

	// ４頂点の初期化
	for (int i = 0; i < 4; i++)
	{
		mVertex[i].rhw = 1.0f;
		mVertex[i].dif = GetColorU8(255, 255, 255, 255);
		mVertex[i].spc = GetColorU8(255, 255, 255, 255);
		mVertex[i].su = 0.0f;
		mVertex[i].sv = 0.0f;
	}

	// 左上
	mVertex[cnt].pos = VGet(sX, sY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// 右上
	mVertex[cnt].pos = VGet(eX, sY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 0.0f;
	cnt++;

	// 右下
	mVertex[cnt].pos = VGet(eX, eY, 0.0f);
	mVertex[cnt].u = 1.0f;
	mVertex[cnt].v = 1.0f;
	cnt++;

	// 左下
	mVertex[cnt].pos = VGet(sX, eY, 0.0f);
	mVertex[cnt].u = 0.0f;
	mVertex[cnt].v = 1.0f;

	// 頂点インデックス
	cnt = 0;
	mIndex[cnt++] = 0;
	mIndex[cnt++] = 1;
	mIndex[cnt++] = 3;

	mIndex[cnt++] = 1;
	mIndex[cnt++] = 2;
	mIndex[cnt++] = 3;

}
