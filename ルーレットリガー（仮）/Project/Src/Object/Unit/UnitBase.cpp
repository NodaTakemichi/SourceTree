#include "../../Common/GetAttr.h"
#include "./UI/UnitUI.h"
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
	DeleteGraph(img_);
}

void UnitBase::SetActed(bool acted)
{
	isActed_ = acted;
}

void UnitBase::SetAlive(bool alive)
{
	isAlive_ = alive;
}

void UnitBase::SetAct(bool act)
{
	isAct_ = act;
}

void UnitBase::SetTargeted(bool target)
{
	isTargeted_ = target;
}

void UnitBase::Damage(int dmg)
{
	//ダメージ計算
	hp_ -= dmg;

	//死亡判定
	if (CheckDead())
	{
		//死亡状態にする
		SetAlive(false);
	}
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
#pragma endregion

	

	//ユニットのコマンド技取得
	std::string name, type, target;
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

		//コマンドの生成
		Command::Par par = {
			name,
			type,
			target,
			static_cast<float>(times)
		};
		CreateCommand(&par);
	}


	//最大HP
	maxHp_ = hp_;

	//画像の登録
	img_ = LoadGraph(source.c_str());
	return std::string();

}

void UnitBase::CreateCommand(Command::Par* par)
{
	//コマンドの生成
	auto cmd = new Command(par);
	cmd->Init();
	commands_.push_back(cmd);
}

void UnitBase::SetDrawingPos(int x)
{
	
	auto topY = 40;
	auto spanY = 180;

	if (unitNum_ == 1)pos_ = { x, topY + spanY };
	else if (unitNum_ == 2)pos_ = { x,topY };
	else if (unitNum_ == 3)pos_ = { x,topY + spanY * 2 };
	
	return;
}
