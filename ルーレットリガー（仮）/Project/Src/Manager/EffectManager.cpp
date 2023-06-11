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

	//�G�t�F�N�g�W�̓ǂݍ���
	EffectLoad("./Data/Effect/EffectData.xml");
}

void EffectManager::Release(void)
{
}

std::string EffectManager::EffectLoad(std::string fileName)
{
	//�G�t�F�N�g�̃��[�h
	//�h�L�������g��ۑ�����ϐ�
	rapidxml::xml_document<> actDoc;
	//�t�@�C���̃I�[�v��
	rapidxml::file<>xmlFile = fileName.c_str();
	//��͍\�����āA�ϐ��Ƀf�[�^���i�[
	actDoc.parse<0>(xmlFile.data());

	//tmx�̏����擾�i���g�ɃA�N�Z�X�j
	auto data = actDoc.first_node("Data");
	if (data == nullptr)return std::string();

	//�A�g���r���[�g�擾�֐�
	auto getAttr = GetAttr();

	//�G�t�F�N�g�̃\�[�X�p�X
	std::string pass;
	//�G�t�F�N�g�ԍ��A�I�t�Z�b�g�l�A�^�[�Q�b�g
	int num, offsetX, offsetY, target;
	//�傫��
	float scale;

	//�G�t�F�N�g���擾

	for (auto ef = data->first_node();
		ef != nullptr;
		ef = ef->next_sibling())
	{
		//�G�t�F�N�g�̔ԍ��擾
		if (!getAttr(ef, "num", num))num = 0;
		//�G�t�F�N�g�̃p�X�擾
		if (!getAttr(ef, "pass", pass))pass = std::string();
		//�G�t�F�N�g�̑傫���擾
		if (!getAttr(ef, "scale", scale))scale = 0.0f;
		//�G�t�F�N�g�̃I�t�Z�b�g�lX�擾
		if (!getAttr(ef, "offsetX", offsetX))offsetX = 0;
		//�G�t�F�N�g�̃I�t�Z�b�g�lY�擾
		if (!getAttr(ef, "offsetY", offsetY))offsetY = 0;
		//�G�t�F�N�g�̑Ώێ擾
		if (!getAttr(ef, "target", target))target = 0;

		//�G�t�F�N�g�n���h��
		auto handle = LoadEffekseerEffect(pass.c_str());

		//�ǉ�
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
	//Effect ef = ef_[num];

	//�G�t�F�N�g�̍Đ�
	effectPlay_ = PlayEffekseer2DEffect(effectHandle_);

	//�����ϐ��ɁA�v���C���Ă���ƁA�ϐ��̒��g���ς���Ă���ۂ�


	//�G�t�F�N�g�̑傫��
	SetScalePlayingEffekseer2DEffect(
		effectPlay_,20, 20, 20);
	//�G�t�F�N�g�̈ʒu
	Vector2 offset = { pos.x + 75, pos.y + 100 };
	SetPosPlayingEffekseer2DEffect(
		effectPlay_, offset.x, offset.y, 0);
}

bool EffectManager::FinishEffect(void)
{
	bool finish = false;
	//0:�Đ��� , -1:�Đ��I��
	if (IsEffekseer2DEffectPlaying(effectPlay_) == -1)
	{
		StopEffekseer2DEffect(effectPlay_);
		finish = true;
	}

	return finish;
}
