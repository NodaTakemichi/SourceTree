#include <algorithm>
#include "../../Manager/SceneManager.h"
#include "../../Utility/AsoUtility.h"


#include "../../Common/GetAttr.h"
#include "./UI/UnitUI.h"

#include"../../_debug/_DebugConOut.h"

#include "UnitBase.h"

UnitBase::UnitBase()
{
}

UnitBase::~UnitBase()
{
}

void UnitBase::Init(void)
{
	//生死状態、行動状態、現在行動状態をセットする
	SetAlive(true);
	SetActed(false);
	SetAct(false);
	SetTargeted(false);

	//テクスチャ―シェーダーの登録
	//psHpColor_ = LoadPixelShader("./Data/Shader/HpShader.cso");
	psTex_ = LoadPixelShader("./x64/Debug/Texture.cso");
	psMonotone_ = LoadPixelShader("./x64/Debug/Monotone.cso");
	psBayerDithe_ = LoadPixelShader("./x64/Debug/BayerDithe.cso");

	//ピクセルシェーダー用の定数バッファの作成
	psTexConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);

	//現在のシェーダー
	nowPs_ = psTex_;

	//合計時間
	totalTime_ = 0.0f;

	//揺れ幅
	shakeX_ = 0.0f;
	shakeValue_ = 0.0f;
	movePow_ = 0.0f;

}

void UnitBase::Update(void)
{



}

void UnitBase::Draw(void)
{
	//行動中ユニット
	if (IsAct())unitUi_->DrawActUnit();

	//狙われているユニット
	if (IsTargeted())unitUi_->DrawRockOn();

}

void UnitBase::Release(void)
{
	//解放
	unitUi_->Release();

	//画像の解放
	DeleteGraph(unitImg_);

	//シェーダーの解放
	DeleteShader(psTex_);
	DeleteShader(psMonotone_);
	DeleteShader(psBayerDithe_);
	//シェーダーの定数バッファの解放
	DeleteShaderConstantBuffer(psTexConstBuf_);
	DeleteShaderConstantBuffer(psMonotoneConstBuf_);
	DeleteShaderConstantBuffer(psBayerDitheConstBuf_);
}

bool UnitBase::DecHpProcess(void)
{
	//HP変化がある時、現在HPが０以上の時のみ
	if (nowHp_ != hp_ && nowHp_ >= 0)
	{
		auto changeTime = 1.0f;		//完了時間

		//経過時間
		totalTime_ += SceneManager::GetInstance().GetDeltaTime();
		//経過　＝（完了する時間ー経過時間）/完了する時間
		auto progress = 1.0f - (changeTime - totalTime_) / changeTime;

		//ダメージ後とダメージ前の線形補間を行う
		nowHp_ = AsoUtility::Lerp(beforHp_, hp_, progress);

		//画像を揺らす
		if (hp_ < nowHp_)UnitImgShake(progress);

		//超過している、もしくはHPが現在HPに追いついた時
		if (progress >= 1.0f || nowHp_ == hp_)
		{
			//ダメージ表記を非表示する
			unitUi_->SetDmg(false, 0);
			//経過時間のリセット
			totalTime_ = 0.0f;

			//HP減少：終了
			return true;
		}
		//HP減少：未終了
		return false;
	}
	//HP減少：無し
	return true;
}

void UnitBase::TurnEndProcess(void)
{
	for (auto& buff : buffs_)
	{
		if (!buff->IsAlive())continue;

		//毒ダメージの処理
		if (buff->CheckOwnBuff(Buff::BUFF_TYPE::POISON))
		{
			TRACE("毒ダメージ\n");

			//最大HPの 1/8 のダメージ
			int dmg = maxHp_ / 8;
			Damage(dmg);
		}

		//バフのターン数減少処理
		if (buff->DecBuffTurn())
		{
			//持続ターンが終了したら、バフを無効状態にする
			buff->SetAlive(false);
		}
	}
}

const int& UnitBase::GetSpeed(void)
{
	//バフ込みのスピード計算
	auto nowSpeed = CalcBuffStatus(
		speed_, Buff::BUFF_TYPE::S_UP, Buff::BUFF_TYPE::S_DOWN);

	return nowSpeed;
}

const int& UnitBase::GetAttack(void)
{
	//バフ込みの攻撃力計算
	auto nowAttack = CalcBuffStatus(
		attack_, Buff::BUFF_TYPE::A_UP, Buff::BUFF_TYPE::A_DOWN);

	return nowAttack;
}

int UnitBase::CalcBuffStatus(const int& status, const Buff::BUFF_TYPE& up, const Buff::BUFF_TYPE& down)
{
	float value = static_cast<float>(status);

	//バフの計算
	for (auto buff : buffs_)
	{
		if (!buff->IsAlive())continue;

		//ステータスアップ
		if (buff->CheckOwnBuff(up))value *= 1.2;
		//ステータスダウン
		if (buff->CheckOwnBuff(down))value *= 0.8;
	}

	return static_cast<int>(floor(value));
}

void UnitBase::Damage(const int& dmg)
{
	TRACE(name_.c_str());
	TRACE("\n攻撃値：%d ||", dmg);

	//バフ込みのダメージ計算
	auto calcDmg = CalcBuffStatus(
		dmg, Buff::BUFF_TYPE::D_DOWN, Buff::BUFF_TYPE::D_UP);

	//ダメージの乱数計算
	float randNum = static_cast<float>(
		SceneManager::GetInstance().GetRand(90, 100)) / 100.0f;
	calcDmg = AsoUtility::Round(static_cast<float>(calcDmg) * randNum);

	TRACE("被ダメ値：%d\n", calcDmg);

	//直前HPの保持
	beforHp_ = hp_;

	//ダメージ計算
	hp_ -= calcDmg;

	//残り体力
	TRACE("残り体力:%d\n\n",hp_);

	//ダメージ表記を表示する
	unitUi_->SetDmg(true, calcDmg);

	//画像の揺れ幅の決定
	shakeValue_ = 50.0f;
	movePow_ = 20.0f;


	//死亡判定
	if (CheckDead())
	{
		TRACE("死亡しました\n");

		//シェーダーの変更
		nowPs_ = psMonotone_;

		//死亡状態にする
		SetAlive(false);
	}
}

void UnitBase::Heal(const int& heal)
{
	//直前HPの記憶
	beforHp_ = hp_;

	//HP計算(HP上限あり)
	hp_ += heal;
	hp_ = (std::min)(hp_, maxHp_);
}

void UnitBase::GiveBuff(const Buff::BUFF_TYPE& type)
{
	//バフの生成
	CreateBuff(type);

	//UIにバフの登録
	unitUi_->SetBuff(buffs_);
}

bool UnitBase::CheckDead(void)
{
	//死亡判定
	if (hp_ <= 0)
	{
		return true;
	}
	return false;
}

bool UnitBase::CheckOwnBuff(const Buff::BUFF_TYPE& type)
{
	for (auto& buff : buffs_)
	{
		if (!buff->IsAlive())continue;

		//指定バフを所有している
		if (buff->CheckOwnBuff(type))return true;
	}
	return false;
}

std::string UnitBase::LoadData(std::string fileName)
{
	//ドキュメントを保存する変数
	rapidxml::xml_document<> actDoc;
	//ファイルのオープン
	rapidxml::file<>xmlFile = fileName.c_str();
	//解析構文して、変数にデータを格納
	actDoc.parse<0>(xmlFile.data());

	//tmxの情報を取得（中身にアクセス）
	auto unit = actDoc.first_node("Unit");
	if (unit == nullptr)return std::string();

	//アトリビュート取得関数
	auto getAttr = GetAttr();
	
	//画像のソースパス
	std::string source;

	//ユニットのデータの取得
#pragma region ユニットの基本情報
	auto data = unit->first_node();
	if (data == nullptr)return std::string();
	//ユニットの名前取得
	if (!getAttr(data, "name", name_))return std::string();
	//ユニットの画像パス取得
	if (!getAttr(data, "source", source))return std::string();
	//ユニットのHP取得
	if (!getAttr(data, "hp", hp_))return std::string();
	//ユニットの攻撃力取得
	if (!getAttr(data, "attack", attack_))return std::string();
	//ユニットのスピード取得
	if (!getAttr(data, "speed", speed_))return std::string();
	//ユニットのスピード取得
	if (!getAttr(data, "speed", speed_))return std::string();
#pragma endregion

	

	//ユニットのコマンド技取得
	std::string name, type, target,buff;
	double times = 0.0;
	int efNum = 0;

	auto cmd = unit->first_node("Cmd");


	if (cmd == nullptr)return std::string();
	for (auto skill = cmd->first_node();
		skill != nullptr;
		skill = skill->next_sibling())
	{
		//技の名前取得
		if (!getAttr(skill, "name", name))name = std::string();
		//技のタイプ取得
		if (!getAttr(skill, "type", type))type = std::string();
		//技の技対象取得
		if (!getAttr(skill, "target", target))target = std::string();
		//技の倍率取得
		if (!getAttr(skill, "times", times))times = 0.0;

		//バフの種類取得
		if (!getAttr(skill, "buff", buff))buff = "NONE";

		//エフェクト番号取得
		if (!getAttr(skill, "efNum", efNum))efNum = 0;


		//コマンドの生成
		Command::Par par = {
			name,
			type,
			target,
			static_cast<float>(times),
			buff,
			efNum
		};
		CreateCommand(&par);
	}


	//HP関連の初期化
	maxHp_ = beforHp_= nowHp_ = hp_;

	//画像の登録
	unitImg_ = LoadGraph(source.c_str());
	return std::string();

}

void UnitBase::DrawUnitShader(const int& shader, const float& revers)
{
	//シェーダーの設定
	SetUsePixelShader(shader);

	//シェーダーにテクスチャを転送
	SetUseTextureToShader(0, unitImg_);

	//シェーダー用の定数バッファ
	auto& cBuf = psTexConstBuf_;

	auto time = SceneManager::GetInstance().GetTotalTime();

	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = revers;
	cbBuf->g = time;

	//描画座標
	Vector2 shakePos = { pos_.x + static_cast<int>(shakeX_),pos_.y };
	MakeSquereVertex(shakePos);

	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(vertex_, 4, index_, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


}

void UnitBase::UnitImgShake(const float& leap)
{
	if (leap >= 0.6f)
	{
		shakeX_ = 0.0f;
		return;
	}

	//画像座標の振動値加算
	shakeX_ += movePow_;

	// 値が最大値または最小値を超えた場合、反転させる
	if (shakeValue_ <= shakeX_ || (shakeValue_ * -1) >= shakeX_)
	{
		//反転
		movePow_ *= -0.8;

		//振幅値を減少させる
		shakeValue_ *= (1.0f - leap);

		auto i = 1;
		if ((shakeValue_ * -1) >= shakeX_)i = -1;
		shakeX_=shakeValue_* i + movePow_;
	}
}

void UnitBase::CreateCommand(Command::Par* par)
{
	//コマンドの生成
	auto cmd = new Command(par);
	cmd->Init();
	commands_.push_back(cmd);
}

void UnitBase::CreateBuff(const Buff::BUFF_TYPE& type)
{
	//反発しあうバフの場合、対消滅させる
	for (auto& buff : buffs_)
	{
		//死んでいたら、処理をしない
		if (!buff->IsAlive())continue;

		//重複していた場合、追加しない
		if (buff->GetBuff() == type)return;

		auto checkBuff = [&](Buff::BUFF_TYPE get, Buff::BUFF_TYPE give) {
			if (buff->GetBuff() == get)
			{
				if (type == give)
				{
					//消滅
					buff->SetAlive(false);

					//生成せずに、処理を終了
					return true;
				}
			}
			return false;
		};

		//反発しあうバフ
		if (checkBuff(Buff::BUFF_TYPE::A_UP, Buff::BUFF_TYPE::A_DOWN))return;
		if (checkBuff(Buff::BUFF_TYPE::A_DOWN, Buff::BUFF_TYPE::A_UP))return;
		if (checkBuff(Buff::BUFF_TYPE::D_UP, Buff::BUFF_TYPE::D_DOWN))return;
		if (checkBuff(Buff::BUFF_TYPE::D_DOWN, Buff::BUFF_TYPE::D_UP))return;
		if (checkBuff(Buff::BUFF_TYPE::S_UP, Buff::BUFF_TYPE::S_DOWN))return;
		if (checkBuff(Buff::BUFF_TYPE::S_DOWN, Buff::BUFF_TYPE::S_UP))return;
	}

	//バフの生成
	auto buff = GetValidBuff();
	buff->CreateBuff(type);

}

Buff* UnitBase::GetValidBuff(void)
{
	//使っていないバフがいたら、再利用
	size_t size = buffs_.size();
	for (int i = 0; i < size; i++)
	{
		if (buffs_[i]->IsAlive())continue;
		//利用できるバフを返す
		return buffs_[i];
	}

	//新しいバフを生成
	Buff* buff = new Buff();
	buffs_.push_back(buff);

	return buff;
}

void UnitBase::MakeSquereVertex(Vector2 pos)
{
	//三角形のポリゴンを2つ作って、くっつけている

	int cnt = 0;
	float sX = static_cast<float>(pos.x);
	float sY = static_cast<float>(pos.y);
	float eX = static_cast<float>(pos.x + DRAWING_SIZE - 1);
	float eY = static_cast<float>(pos.y + DRAWING_SIZE - 1);

	// ４頂点の初期化
	for (int i = 0; i < 4; i++)
	{
		vertex_[i].rhw = 1.0f;
		vertex_[i].dif = GetColorU8(255, 255, 255, 255);
		vertex_[i].spc = GetColorU8(255, 255, 255, 255);
		vertex_[i].su = 0.0f;
		vertex_[i].sv = 0.0f;
	}

	// 左上
	vertex_[cnt].pos = VGet(sX, sY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// 右上
	vertex_[cnt].pos = VGet(eX, sY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 0.0f;
	cnt++;

	// 右下
	vertex_[cnt].pos = VGet(eX, eY, 0.0f);
	vertex_[cnt].u = 1.0f;
	vertex_[cnt].v = 1.0f;
	cnt++;

	// 左下
	vertex_[cnt].pos = VGet(sX, eY, 0.0f);
	vertex_[cnt].u = 0.0f;
	vertex_[cnt].v = 1.0f;

	// 頂点インデックス
	cnt = 0;
	index_[cnt++] = 0;
	index_[cnt++] = 1;
	index_[cnt++] = 3;

	index_[cnt++] = 1;
	index_[cnt++] = 2;
	index_[cnt++] = 3;

}

void UnitBase::SetDrawingPos(int x)
{
	
	auto topY = 40;
	auto spanY = 180;

	if (unitNum_ == 1)pos_ = { x, topY + spanY };
	else if (unitNum_ == 2)pos_ = { x,topY };
	else if (unitNum_ == 3)pos_ = { x,topY + spanY * 2 };

	MakeSquereVertex(pos_);
	
	return;
}
