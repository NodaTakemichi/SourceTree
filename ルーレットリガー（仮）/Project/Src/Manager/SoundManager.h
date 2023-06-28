#pragma once
#include <unordered_map>
#include <string>

class SoundManager
{
public:
	// �T�E���h��
	enum class SOUND_TYPE
	{
		TITLE_BGM,
		SELECT_BGM,
		BATTLE1_BGN,
		BATTLE2_BGN,
		BATTLE3_BGN,
		VICTORY_BGN,
		LOSE_BGN,
		RESULT_BGN,



	};

	// �����I�ɃC���X�e���X�𐶐�����
	static void CreateInstance(void);

	// �ÓI�C���X�^���X�̎擾
	static SoundManager& GetInstance(void);

	// ������
	void Init(void);

	// ���
	void Release(void);

	// �����̃��[�h
	int LoadSound(SOUND_TYPE sound);

	//�����̍Đ��i�m�[�}���j
	void PlaySoundNormal(const int& sound);
	//�����̍Đ��i�o�b�N�O�����h�j
	void PlaySoundBack(const int& sound);
	//�����̍Đ��iBGM�j
	void PlaySoundBGM(const int& sound);

private:

	// �ÓI�C���X�^���X
	static SoundManager* instance_;

	// ���\�[�X�Ǘ��̑Ώ�
	std::unordered_map<SOUND_TYPE, std::string> resMap_;

	// �ǂݍ��ݍς݃��\�[�X
	std::unordered_map<SOUND_TYPE, int> loadedMap_;

	// �O�����琶���ł��Ȃ��l�ɂ���
	SoundManager(void);
	// �f�X�g���N�^�����l
	~SoundManager(void);

	//�}�X�^�[�{�����[��
	int masterVolume_;
	//BGM�{�����[��
	int bgmVolume_;
	//SE�{�����[��
	int seVolume_;


};

