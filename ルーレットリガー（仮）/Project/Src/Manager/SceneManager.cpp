#include <chrono>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Application.h"
#include "../Common/Fader.h"

#include "../Scene/GameScene.h"
#include "../Scene/GameScene.h"


#include "../Utility/Measure.h"
#include "../Utility/DrawShader.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

SceneManager* SceneManager::mInstance = nullptr;

void SceneManager::CreateInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new SceneManager();
	}
	mInstance->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *mInstance;
}

void SceneManager::Init(void)
{
	//�E�C���h���A�N�e�B�u��Ԃ���Ȃ��Ă��A�����𑱍s������
	//SetAlwaysRunFlag(false);

	//�}�E�X�̔�\��
	SetMouseDispFlag(false);

	// �V�F�[�_�\�`��N���X������
	DrawShader::CreateInstance();


	mFader = new Fader();
	mFader->Init();

	mScene = new GameScene();
	mScene->Init();

	mSceneID = SCENE_ID::GAME;
	mWaitSceneID = SCENE_ID::NONE;

	mIsSceneChanging = false;

	// �f���^�^�C��
	mPreTime = std::chrono::system_clock::now();
	totalTime_ = 0.0f;

	//����������̏�����
	gen_ = std::mt19937(rd_());


}


void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	// �f���^�^�C��
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - mPreTime).count() / 1000000000.0);
	mPreTime = nowTime;
	totalTime_ += deltaTime_;


	//�C��
	mFader->Update();
	if (mIsSceneChanging)
	{
		Fade();
	}
	else
	{
		mScene->Update();
	}

	// Effekseer�ɂ��Đ����̃G�t�F�N�g���X�V����B
	UpdateEffekseer2D();

}

void SceneManager::Draw(void)
{
	
	// �`���O���t�B�b�N�̈�̎w��
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();



	// �`��
	mScene->Draw();

	// �v���t�@�N�^�����O
	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		break;
	case SCENE_ID::GAME:
		break;
	case SCENE_ID::RESULT:
		break;
	}

	// Effekseer�ɂ��Đ����̃G�t�F�N�g��`�悷��B
	DrawEffekseer2D();
	
	mFader->Draw();

}

void SceneManager::Release(void)
{
	mScene->Release();
	delete mScene;

	delete mFader;

	// �V�F�[�_�\�`��̉��
	DrawShader::GetInstance().Release();


}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isFading)
{

	mWaitSceneID = nextId;

	if (isFading)
	{
		mFader->SetFade(Fader::STATE::FADE_OUT);
		mIsSceneChanging = true;
	}
	else
	{
		DoChangeScene();
	}
}

SceneManager::SCENE_ID SceneManager::GetmSceneID(void)
{
	return mSceneID;
}

float SceneManager::GetDeltaTime(void) const
{
	//return 1.0f / 60.0f;
	return deltaTime_;
}

float SceneManager::GetTotalTime(void) const
{
	return totalTime_;
}

int SceneManager::GetRand(const int& min, const int& max)
{
	//��l���z
	std::uniform_int_distribution<> dist(min, max);
	return	dist(gen_);
}

SceneManager::SceneManager(void)
{

	mSceneID = SCENE_ID::NONE;
	mWaitSceneID = SCENE_ID::NONE;

	mScene = nullptr;
	mFader = nullptr;

	mIsSceneChanging = false;

	// �f���^�^�C��
	deltaTime_ = 1.0f / 60.0f;
	totalTime_ = 0.0f;

}

SceneManager::~SceneManager(void)
{
	delete mInstance;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	mPreTime = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(void)
{

	// ���\�[�X�̉��
	ResourceManager::GetInstance().Release();

	mScene->Release();
	delete mScene;

	mSceneID = mWaitSceneID;

	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		//mScene = new TitleScene();
		break;
	case SCENE_ID::GAME:
		mScene = new GameScene();
		break;
	case SCENE_ID::RESULT:
		//mScene = new ResultScene();
		break;
		break;
	default:
		break;
	}

	mScene->Init();

	// �v�����Z�b�g
	Measure::GetInstance().Reset();

	ResetDeltaTime();

	mWaitSceneID = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{

	Fader::STATE fState = mFader->GetState();
	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		if (mFader->IsEnd())
		{
			mFader->SetFade(Fader::STATE::NONE);
			mIsSceneChanging = false;
		}
		break;
	case Fader::STATE::FADE_OUT:
		if (mFader->IsEnd())
		{
			DoChangeScene();
			mFader->SetFade(Fader::STATE::FADE_IN);
		}
		break;
	}

}


