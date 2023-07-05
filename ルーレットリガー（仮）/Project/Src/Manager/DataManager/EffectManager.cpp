#include <EffekseerForDXLib.h>
#include <assert.h>
#include "../../Common/GetAttr.h"
#include "EffectManager.h"

#include "../../_debug/_DebugConOut.h"
#include "../../_debug/_DebugDispOut.h"

EffectManager* EffectManager::instance_ = nullptr;

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new EffectManager();
	}
	instance_->Init();
}

EffectManager& EffectManager::GetInstance(void)
{
	return *instance_;
}

void EffectManager::Init(void)
{
	//�G�t�F�N�g���̓ǂݍ���
	EffectDataLoad("./Data/Effect/EffectData.xml");
}

void EffectManager::Release(void)
{
	//�G�t�F�N�g�̍Đ��I��
	for (auto& play : effectPlays_)
	{
		StopEffekseer2DEffect(play.second);
	}


	//�j��
	effectPlays_.clear();
	loadedMap_.clear();
	
}

void EffectManager::LoadedEffectRelease(void)
{
	//�G�t�F�N�g�̍Đ��I��
	for (auto& play : effectPlays_)
	{
		StopEffekseer2DEffect(play.second);
	}

	loadedMap_.clear();
	effectPlays_.clear();

}

std::string EffectManager::EffectDataLoad(std::string fileName)
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
	std::string path;
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
		if (!getAttr(ef, "path", path))path = std::string();
		//�G�t�F�N�g�̑傫���擾
		if (!getAttr(ef, "scale", scale))scale = 0.0f;
		//�G�t�F�N�g�̃I�t�Z�b�g�lX�擾
		if (!getAttr(ef, "offsetX", offsetX))offsetX = 0;
		//�G�t�F�N�g�̃I�t�Z�b�g�lY�擾
		if (!getAttr(ef, "offsetY", offsetY))offsetY = 0;
		//�G�t�F�N�g�̑Ώێ擾
		if (!getAttr(ef, "target", target))target = 0;


		//�f�[�^
		auto d = EffectData{
			path,
			scale,
			Vector2{offsetX,offsetY},
			target,
			0
		};

		//���\�[�X�Ǘ��ɒǉ�
		resMap_.emplace(std::make_pair(num, d));
	}


	return std::string();
}

void EffectManager::EffectLoad(const int& num)
{
	//�o�^����Ă��邩�m�F
	const auto& lPair = loadedMap_.find(num);
	if (lPair != loadedMap_.end()) 
	{
		//���ɓo�^����Ă���̂ŉ������Ȃ�
		return;
	}

	//�f�[�^�ɂ��邩�m�F
	const auto& rPair = resMap_.find(num);
	if (rPair == resMap_.end())
	{
		//�f�[�^��ɑ��݂��Ȃ�
		TRACE("\n���݂��Ȃ��G�t�F�N�g�f�[�^������܂�\n");
		return;
	}

	//�G�t�F�N�g�̃��[�h
	auto& path = resMap_.at(num).path;
	auto handle = LoadEffekseerEffect(path.c_str());
	//���[�h�ς݂ɓo�^
	const EffectData& ef = EffectData{
		rPair->second.path,
		rPair->second.scale,
		rPair->second.offset,
		rPair->second.target,
		handle
	};
	loadedMap_.emplace(std::make_pair(num, ef));

}


void EffectManager::PlayEffect(const int& num, const Vector2& pos)
{
	//�Đ�����G�t�F�N�g
	EffectData ef = loadedMap_.at(num);


	//�g�p�ł���Đ��n���h�����Ȃ��ꍇ�A���
	CreatePlayHandle();

	//�S�̍U���G�t�F�N�g�̏ꍇ
	if (AllTargetEffectPlay(ef,pos))return;


	//�G�t�F�N�g�̍Đ�
	for (auto& play : effectPlays_)
	{
		//�g�p���̃n���h���͎g��Ȃ�
		if (!play.first)continue;

		play.second = PlayEffekseer2DEffect(ef.handle);

		//�G�t�F�N�g�̑傫��
		float s = ef.scale;
		SetScalePlayingEffekseer2DEffect(
			play.second, s, s, s);
		//�G�t�F�N�g�̈ʒu
		SetPosPlayingEffekseer2DEffect(
			play.second, pos.x + ef.offset.x, pos.y + ef.offset.y, 0);
		//�g�p��
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

		//0:�Đ��� , -1:�Đ��I��
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
	//�g�p�ł���n���h�������邩�m�F
	for (auto& play : effectPlays_)
	{
		if (play.first == true)return;
	}


	//�Đ��n���h���̒ǉ�
	effectPlays_.push_back(std::make_pair(true, -1));

}

bool EffectManager::AllTargetEffectPlay(const EffectData& ef, const Vector2& pos)
{
	//�S�̂��ǂ������f
	if (ef.target != 0)return false;

	//���łɍĐ����Ă���ꍇ�A���������Ȃ�
	for (auto& play : effectPlays_)
	{
		if (play.first == false)return true;
	}

	//�G�t�F�N�g�̍Đ�
	for (auto& play : effectPlays_)
	{
		//�g�p���̃n���h���͎g��Ȃ�
		if (!play.first)continue;

		play.second = PlayEffekseer2DEffect(ef.handle);

		//�G�t�F�N�g�̑傫��
		float s = ef.scale;
		SetScalePlayingEffekseer2DEffect(
			play.second, s, s, s);
		//�G�t�F�N�g�̈ʒu
		SetPosPlayingEffekseer2DEffect(
			play.second, pos.x + ef.offset.x, pos.y + ef.offset.y, 0);
		//�g�p��
		play.first = false;

		return true;
	}

}

