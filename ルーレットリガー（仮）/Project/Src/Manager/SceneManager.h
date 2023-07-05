#pragma once
#include <chrono>
#include <memory>
#include <array>
#include <random>
class SceneBase;
class Fader;

class SceneManager
{

public:

	// �V�[���Ǘ��p
	enum class SCENE_ID
	{
		NONE,
		TITLE,
		SELECT,
		GAME,
		RESULT,
	};

	
	// �C���X�^���X�̐���
	static void CreateInstance(void);

	// �C���X�^���X�̎擾
	static SceneManager& GetInstance(void);

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	// ��ԑJ��
	void ChangeScene(SCENE_ID nextId, bool isFading);

	// �V�[��ID�̎擾
	SCENE_ID GetmSceneID(void);

	// �f���^�^�C���̎擾
	float GetDeltaTime(void) const;
	//�o�ߎ��Ԃ̎擾
	float GetTotalTime(void) const;

	//�����̎擾
	int GetRand(const int& min, const int& max);

private:

	// �ÓI�C���X�^���X
	static SceneManager* instance_;


	SCENE_ID mSceneID;
	SCENE_ID mWaitSceneID;

	SceneBase* mScene;
	Fader* mFader;

	bool mIsSceneChanging;

	// �f���^�^�C��
	std::chrono::system_clock::time_point preTime_;
	float deltaTime_;
	//�o�ߎ���
	float totalTime_;

	//����������
	std::random_device rd_;
	std::mt19937 gen_;

	//�}�E�X�摜
	int mouseImg_;

	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	SceneManager(void);
	~SceneManager(void);

	void ResetDeltaTime(void);

	// �V�[���J��
	void DoChangeScene(void);

	// �t�F�[�h
	void Fade(void);

};