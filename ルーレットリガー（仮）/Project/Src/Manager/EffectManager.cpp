#include <EffekseerForDXLib.h>
#include "../Common/Vector2.h"
#include "../Common/GetAttr.h"
#include "EffectManager.h"


EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init(void)
{

	effectHandle_ = LoadEffekseerEffect(
		"./Data/Effect/00_Basic/Simple_Sprite_BillBoard.efkefc");

	//エフェクト集の読み込み
	EffectLoad("./Data/Effect/EffectData.xml");
}

void EffectManager::Release(void)
{
}

std::string EffectManager::EffectLoad(std::string fileName)
{
	//エフェクトのロード
	//ドキュメントを保存する変数
	rapidxml::xml_document<> actDoc;
	//ファイルのオープン
	rapidxml::file<>xmlFile = fileName.c_str();
	//解析構文して、変数にデータを格納
	actDoc.parse<0>(xmlFile.data());

	//tmxの情報を取得（中身にアクセス）
	auto data = actDoc.first_node("Data");
	if (data == nullptr)return std::string();

	//アトリビュート取得関数
	auto getAttr = GetAttr();

	//エフェクトのソースパス
	std::string pass;
	//エフェクト番号、オフセット値、ターゲット
	int num, offsetX, offsetY, target;
	//大きさ
	float scale;

	//エフェクト情報取得

	for (auto ef = data->first_node();
		ef != nullptr;
		ef = ef->next_sibling())
	{
		//エフェクトの番号取得
		if (!getAttr(ef, "num", num))num = 0;
		//エフェクトのパス取得
		if (!getAttr(ef, "pass", pass))pass = std::string();
		//エフェクトの大きさ取得
		if (!getAttr(ef, "scale", scale))scale = 0.0f;
		//エフェクトのオフセット値X取得
		if (!getAttr(ef, "offsetX", offsetX))offsetX = 0;
		//エフェクトのオフセット値Y取得
		if (!getAttr(ef, "offsetY", offsetY))offsetY = 0;
		//エフェクトの対象取得
		if (!getAttr(ef, "target", target))target = 0;

		//エフェクトハンドル
		auto handle = LoadEffekseerEffect(pass.c_str());

		//追加
		auto d = EffectData{
			num,
			handle,
			scale,
			Vector2{offsetX,offsetY}
		};
		ef_.push_back(d);
	}


	return std::string();
}


void EffectManager::PlayEffect(const int& num, const Vector2& pos)
{
	////再生するエフェクト
	//Effect ef = ef_[num];

	////エフェクトの再生
	//effectPlay_ = PlayEffekseer2DEffect(ef.handle);

	////エフェクトの大きさ
	//SetScalePlayingEffekseer2DEffect(
	//	effectPlay_, ef.scale, ef.scale, ef.scale);
	////エフェクトの位置
	//SetPosPlayingEffekseer2DEffect(
	//	effectPlay_, pos.x + ef.offset.x, pos.y + ef.offset.y, 0);

	//再生するエフェクト
	//Effect ef = ef_[num];

	//エフェクトの再生
	effectPlay_ = PlayEffekseer2DEffect(effectHandle_);

	//同じ変数に、プレイしていると、変数の中身が変わってるっぽい


	//エフェクトの大きさ
	SetScalePlayingEffekseer2DEffect(
		effectPlay_,20, 20, 20);
	//エフェクトの位置
	Vector2 offset = { pos.x + 75, pos.y + 100 };
	SetPosPlayingEffekseer2DEffect(
		effectPlay_, offset.x, offset.y, 0);
}

bool EffectManager::FinishEffect(void)
{
	bool finish = false;
	//0:再生中 , -1:再生終了
	if (IsEffekseer2DEffectPlaying(effectPlay_) == -1)
	{
		StopEffekseer2DEffect(effectPlay_);
		finish = true;
	}

	return finish;
}
