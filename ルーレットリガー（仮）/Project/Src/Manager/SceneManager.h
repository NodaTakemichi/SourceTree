#pragma once
#include <chrono>
#include <memory>
class SceneBase;
class Fader;
class ResourceManager;
class InputManager;

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

private:

	// �ÓI�C���X�^���X
	static SceneManager* mInstance;


	SCENE_ID mSceneID;
	SCENE_ID mWaitSceneID;

	SceneBase* mScene;
	Fader* mFader;

	bool mIsSceneChanging;

	// �f���^�^�C��
	std::chrono::system_clock::time_point mPreTime;
	float mDeltaTime;

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