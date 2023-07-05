#include <DxLib.h>
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();
	}
	instance_->Init();
}

SoundManager& SoundManager::GetInstance(void)
{
	return *instance_;
}

void SoundManager::Init(void)
{
	std::string res;
	const std::string pathSound = "Data/Sound/BGM/";

	// �^�C�g�����BGM
	res = pathSound + "Title.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::TITLE_BGM, res));

	//�Z���N�g���GM
	res = pathSound + "Select.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::SELECT_BGM, res));

	// �o�g���PBGM
	res = pathSound + "Battle1.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::BATTLE1_BGN, res));

	// �o�g���QBGM
	res = pathSound + "BAttle2.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::BATTLE2_BGN, res));

	// �o�g���RBGM
	res = pathSound + "Battle3.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::BATTLE3_BGN, res));

	// ����BGM
	res = pathSound + "Victory.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::VICTORY_BGN, res));

	// �s�kBGM
	res = pathSound + "Lose.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::LOSE_BGN, res));

	// ���U���g���BGM
	res = pathSound + "Result.mp3";
	resMap_.insert(std::make_pair(SOUND_TYPE::RESULT_BGN, res));


}

void SoundManager::Release(void)
{
	InitSoundMem();

	resMap_.clear();
	loadedMap_.clear();
}

int SoundManager::LoadSound(SOUND_TYPE sound)
{

	const auto& lPair = loadedMap_.find(sound);
	if (lPair != loadedMap_.end())
	{
		//�o�^����Ă���
		return lPair->second;
	}

	const auto& rPair = resMap_.find(sound);
	if (rPair == resMap_.end())
	{
		// ���݂��Ȃ�
		return -1;
	}

	//�o�^����Ă��Ȃ��ꍇ
	int handle = LoadSoundMem(rPair->second.c_str());
	//�ǉ��o�^
	loadedMap_.insert(std::make_pair(sound, handle));

	return handle;
}

void SoundManager::PlaySoundNormal(const int& handle)
{
	PlaySoundMem(handle, DX_PLAYTYPE_NORMAL);
}

void SoundManager::PlaySoundBack(const int& handle)
{
	PlaySoundMem(handle, DX_PLAYTYPE_BACK);
}

void SoundManager::PlaySoundBGM(const int& handle)
{
	PlaySoundMem(handle, DX_PLAYTYPE_LOOP);
}

SoundManager::SoundManager(void)
{
}

SoundManager::~SoundManager(void)
{
	delete instance_;
}

