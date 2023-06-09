#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "_debug/_DebugConOut.h"
#include "_debug/_DebugDispOut.h"
#include "Manager/InputManager.h"
#include "Manager/ResourceManager.h"
#include "Manager/SceneManager.h"
#include "Utility/Measure.h"

#include"_debug/_DebugConOut.h"
#include"_debug/_DebugDispOut.h"

#include "Application.h"

Application* Application::mInstance = nullptr;


void Application::CreateInstance(void)
{
	if (mInstance == nullptr)
	{
		mInstance = new Application();
	}
	mInstance->Init();
}

Application& Application::GetInstance(void)
{
	return *mInstance;
}

void Application::Init(void)
{

	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText("���[���b�g���K�[");

	// �E�B���h�E�T�C�Y
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	// DxLib�̏�����
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	mIsInitFail = false;
	if (DxLib_Init() == -1)
	{
		TRACE("DxLib �̏��������s");
		mIsInitFail = true;
		return;
	}

	_dbgSetup(SCREEN_SIZE_X, SCREEN_SIZE_Y, 255);

	// Effekseer�̏�����
	InitEffekseer();

	// �L�[���䏉����
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();

	// �f�o�b�O�@�\������
	Measure::CreateInstance();

	// ���\�[�X�Ǘ�������
	ResourceManager::CreateInstance();

	// �V�[���Ǘ�������
	SceneManager::CreateInstance();

	// ���͑��u�Ǘ�������
	InputManager::CreateInstance();
}

void Application::Run(void)
{

	auto& intpuManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		Measure::GetInstance().Start();

		_dbgStartDraw();

		intpuManager.Update();
		sceneManager.Update();

 		sceneManager.Draw();

		_dbgDraw();


		ScreenFlip();
	}

}

void Application::Release(void)
{

	// Effekseer���I������B
	Effkseer_End();

	// DxLib�I��
	if (DxLib_End() == -1)
	{
		mIsReleaseFail = true;
	}

}

bool Application::IsInitFail(void) const
{
	return mIsInitFail;
}

bool Application::IsReleaseFail(void) const
{
	return mIsReleaseFail;
}

Application::Application(void)
{
	mIsInitFail = false;
	mIsReleaseFail = false;
}

Application::~Application(void)
{
	delete mInstance;
}

void Application::InitEffekseer(void)
{
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();
}
