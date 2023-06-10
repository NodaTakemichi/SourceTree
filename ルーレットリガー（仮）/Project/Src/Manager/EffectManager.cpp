#include <EffekseerForDXLib.h>
#include "../Common/Vector2.h"
#include "EffectManager.h"


EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init(void)
{

	effectHandle_ = LoadEffekseerEffect("./Data/Effect/force.efkefc");
	effectHandle1_ = LoadEffekseerEffect("./Data/Effect/meteo.efkefc");


}

void EffectManager::Release(void)
{
}

void EffectManager::EffectLoad(void)
{
	//エフェクトのロード

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

	//エフェクトの大きさ
	SetScalePlayingEffekseer2DEffect(
		effectPlay_,3,3,3);
	//エフェクトの位置
	SetPosPlayingEffekseer2DEffect(
		effectPlay_, pos.x, pos.y, 0);
}

bool EffectManager::FinishEffect(void)
{
	bool finish = false;
	//0:再生中 , -1:再生終了
	if (IsEffekseer3DEffectPlaying(effectPlay_) == -1)
	{
		finish = true;
	}

	return finish;
}
