#include <EffekseerForDXLib.h>
#include "../Common/Vector2.h"
#include "../Common/GetAttr.h"
#include "EffectManager.h"

#include "../_debug/_DebugDispOut.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init(void)
{
	//エフェクト集の読み込み
	EffectLoad("./Data/Effect/EffectData.xml");
}

void EffectManager::Release(void)
{
	//エフェクトの再生終了
	for (auto& play : effectPlays_)
	{
		StopEffekseer2DEffect(play.second);
	}


	//破棄
	ef_.clear();
	effectPlays_.clear();
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
	std::string path;
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
		if (!getAttr(ef, "path", path))path = std::string();
		//エフェクトの大きさ取得
		if (!getAttr(ef, "scale", scale))scale = 0.0f;
		//エフェクトのオフセット値X取得
		if (!getAttr(ef, "offsetX", offsetX))offsetX = 0;
		//エフェクトのオフセット値Y取得
		if (!getAttr(ef, "offsetY", offsetY))offsetY = 0;
		//エフェクトの対象取得
		if (!getAttr(ef, "target", target))target = 0;

		//エフェクトハンドル
		auto handle = LoadEffekseerEffect(path.c_str());

		//追加
		auto d = EffectData{
			num,
			handle,
			scale,
			Vector2{offsetX,offsetY},
			target
		};
		ef_.push_back(d);
	}


	return std::string();
}


void EffectManager::PlayEffect(const int& num, const Vector2& pos)
{
	//再生するエフェクト
	EffectData ef = ef_[num];

	//使用できる再生ハンドルがない場合、作る
	CreatePlayHandle();

	//全体攻撃エフェクトの場合
	if (AllTargetEffectPlay(ef,pos))return;


	//エフェクトの再生
	for (auto& play : effectPlays_)
	{
		//使用中のハンドルは使わない
		if (!play.first)continue;

		play.second = PlayEffekseer2DEffect(ef.handle);

		//エフェクトの大きさ
		float s = ef.scale;
		SetScalePlayingEffekseer2DEffect(
			play.second, s, s, s);
		//エフェクトの位置
		SetPosPlayingEffekseer2DEffect(
			play.second, pos.x + ef.offset.x, pos.y + ef.offset.y, 0);
		//使用中
		play.first = false;

		break;
	}
}

bool EffectManager::FinishEffect(void)
{
	bool finish = true;
	for (auto& play : effectPlays_)
	{
		if (play.first)continue;

		//0:再生中 , -1:再生終了
		if (IsEffekseer2DEffectPlaying(play.second) == -1)
		{
			StopEffekseer2DEffect(play.second);
			play.first = true;

			finish = true;
			continue;
		}

		finish = false;
		break;
	}

	return finish;
}

void EffectManager::CreatePlayHandle(void)
{
	//使用できるハンドルがあるか確認
	for (auto& play : effectPlays_)
	{
		if (play.first == true)return;
	}


	//再生ハンドルの追加
	effectPlays_.push_back(std::make_pair(true, -1));

}

bool EffectManager::AllTargetEffectPlay(const EffectData& ef, const Vector2& pos)
{
	//全体かどうか判断
	if (ef.target != 0)return false;

	//すでに再生している場合、処理をしない
	for (auto& play : effectPlays_)
	{
		if (play.first == false)return true;
	}

	//エフェクトの再生
	for (auto& play : effectPlays_)
	{
		//使用中のハンドルは使わない
		if (!play.first)continue;

		play.second = PlayEffekseer2DEffect(ef.handle);

		//エフェクトの大きさ
		float s = ef.scale;
		SetScalePlayingEffekseer2DEffect(
			play.second, s, s, s);
		//エフェクトの位置
		SetPosPlayingEffekseer2DEffect(
			play.second, pos.x + ef.offset.x, pos.y + ef.offset.y, 0);
		//使用中
		play.first = false;

		return true;
	}

}
