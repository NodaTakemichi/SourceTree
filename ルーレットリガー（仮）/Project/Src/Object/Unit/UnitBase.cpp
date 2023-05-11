#include <algorithm>
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

	//ピクセルシェーダー用の定数バッファの作成
	psTexConstBuf_ = CreateShaderConstantBuffer(sizeof(float) * 4);

	//現在のシェーダー
	nowPs_ = psTex_;
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
}

void UnitBase::TurnEndProcess(void)
{
	for (auto& buff : buffs_)
	{
		if (!buff->IsAlive())continue;

		//毒ダメージの処理
		if (buff->CheckOwnBuff(Buff::BUFF_TYPE::POISON))
		{
			//HPの 1/8 のダメージ
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
		if (buff->CheckOwnBuff(up))value *= 1.1;
		//ステータスダウン
		if (buff->CheckOwnBuff(down))value *= 0.9;
	}

	return static_cast<int>(floor(value));
}

void UnitBase::Damage(const int& dmg)
{
	TRACE("ダメージ：（%d", dmg);

	//バフ込みのダメージ計算
	auto calcDmg = CalcBuffStatus(
		dmg, Buff::BUFF_TYPE::D_DOWN, Buff::BUFF_TYPE::D_UP);

	TRACE("、%d）\n", calcDmg);

	//直前HPの記憶
	beforHp_ = hp_;

	//ダメージ計算
	hp_ -= calcDmg;

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


		//コマンドの生成
		Command::Par par = {
			name,
			type,
			target,
			static_cast<float>(times),
			buff
		};
		CreateCommand(&par);
	}


	//最大HP
	maxHp_ = beforHp_= hp_;

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


	//ピクセルシェーダー用の定数バッファのアドレスを取得
	COLOR_F* cbBuf =
		(COLOR_F*)GetBufferShaderConstantBuffer(cBuf);
	cbBuf->r = revers;


	//ピクセルシェーダー用の定数バッファを更新して書き込んだ内容を反映する
	UpdateShaderConstantBuffer(cBuf);

	//ピクセルシェーダー用の定数バッファを定数バッファレジスタにセット
	SetShaderConstantBuffer(cBuf, DX_SHADERTYPE_PIXEL, 3);

	//描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);
	DrawPolygonIndexed2DToShader(mVertex, 4, mIndex, 2);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


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
	auto buff = new Buff(type);
	buff->Init();
	buffs_.push_back(buff);

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

	/*
	　〜〜〜〜〜〜
		0-----1
		|     |
		|     |
		3-----2
	　〜〜〜〜〜〜
		0-----1
		|  ／
		|／
		3
	　〜〜〜〜〜〜
			  1
		   ／ |
		 ／   |
		3-----2
	　〜〜〜〜〜〜
	*/


	// 頂点インデックス
	cnt = 0;
	mIndex[cnt++] = 0;
	mIndex[cnt++] = 1;
	mIndex[cnt++] = 3;

	mIndex[cnt++] = 1;
	mIndex[cnt++] = 2;
	mIndex[cnt++] = 3;

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
