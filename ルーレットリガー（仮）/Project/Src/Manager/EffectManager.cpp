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
	auto test = "./Data/Effect/0.efkefc";
	effectHandle_ = LoadEffekseerEffect(test);
}

void EffectManager::Release(void)
{
}

void EffectManager::EffectLoad(void)
{
	//�G�t�F�N�g�̃��[�h

}

void EffectManager::PlayEffect(const int& num, const Vector2& pos)
{
	////�Đ�����G�t�F�N�g
	//Effect ef = ef_[num];

	////�G�t�F�N�g�̍Đ�
	//effectPlay_ = PlayEffekseer2DEffect(ef.handle);

	////�G�t�F�N�g�̑傫��
	//SetScalePlayingEffekseer2DEffect(
	//	effectPlay_, ef.scale, ef.scale, ef.scale);
	////�G�t�F�N�g�̈ʒu
	//SetPosPlayingEffekseer2DEffect(
	//	effectPlay_, pos.x + ef.offset.x, pos.y + ef.offset.y, 0);

	//�Đ�����G�t�F�N�g
	Effect ef = ef_[num];

	//�G�t�F�N�g�̍Đ�
	effectPlay_ = PlayEffekseer2DEffect(effectHandle_);

	////�G�t�F�N�g�̑傫��
	//SetScalePlayingEffekseer2DEffect(
	//	effectPlay_, ef.scale, ef.scale, ef.scale);
	//�G�t�F�N�g�̈ʒu
	SetPosPlayingEffekseer2DEffect(
		effectPlay_, pos.x, pos.y, 0);
}

bool EffectManager::FinishEffect(void)
{
	bool finish = false;
	//0:�Đ��� , -1:�Đ��I��
	if (IsEffekseer3DEffectPlaying(effectPlay_) == -1)
	{
		finish = true;
	}

	return finish;
}
