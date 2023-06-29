#include <chrono>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Application.h"
#include "../Common/Fader.h"

#include "../Scene/TitleScene.h"
#include "../Scene/SelectScene.h"
#include "../Scene/GameScene.h"
#include "../Scene/ResultScene.h"

#include "../Utility/Measure.h"
#include "../Utility/DrawShader.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "SceneManager.h"

SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{
	//ウインドがアクティブ状態じゃなくても、処理を続行させる
	//SetAlwaysRunFlag(false);

	//マウスの非表示
	SetMouseDispFlag(false);

	// シェーダ―描画クラス初期化
	DrawShader::CreateInstance();

	// 音声管理初期化
	SoundManager::CreateInstance();


	mFader = new Fader();
	mFader->Init();

	mScene = new SelectScene();
	mScene->Init();

	mSceneID = SCENE_ID::SELECT;
	mWaitSceneID = SCENE_ID::NONE;

	mIsSceneChanging = false;

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();
	totalTime_ = 0.0f;

	//乱数生成器の初期化
	gen_ = std::mt19937(rd_());


}


void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;
	totalTime_ += deltaTime_;


	//修正
	mFader->Update();
	if (mIsSceneChanging)
	{
		Fade();
	}
	else
	{
		mScene->Update();
	}

	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer2D();

}

void SceneManager::Draw(void)
{
	
	// 描画先グラフィック領域の指定
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();



	// 描画
	mScene->Draw();

	// 要リファクタリング
	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		break;
	case SCENE_ID::SELECT:
		break;
	case SCENE_ID::GAME:
		break;
	case SCENE_ID::RESULT:
		break;
	}

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer2D();
	
	mFader->Draw();

}

void SceneManager::Release(void)
{
	mScene->Release();
	delete mScene;

	delete mFader;

	// シェーダ―描画の解放
	DrawShader::GetInstance().Release();

	//音声管理クラスの解放
	SoundManager::GetInstance().Release();
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
	//一様分布
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

	// デルタタイム
	deltaTime_ = 1.0f / 60.0f;
	totalTime_ = 0.0f;

}

SceneManager::~SceneManager(void)
{
	delete instance_;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(void)
{

	// リソースの解放
	//ResourceManager::GetInstance().Release();

	mScene->Release();
	delete mScene;

	mSceneID = mWaitSceneID;

	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		mScene = new TitleScene();
		break;
	case SCENE_ID::SELECT:
		mScene = new SelectScene();
		break;
	case SCENE_ID::GAME:
		mScene = new GameScene();
		break;
	case SCENE_ID::RESULT:
		mScene = new ResultScene();
		break;
	default:
		break;
	}

	mScene->Init();

	// 計測リセット
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


