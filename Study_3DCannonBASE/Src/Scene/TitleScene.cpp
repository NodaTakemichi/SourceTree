#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
	imgTitle_ = -1;
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	imgTitle_ = LoadGraph((Application::PATH_IMAGE + "Title.png").c_str());
}

void TitleScene::Update(void)
{

	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{

	//球体の描画
	VECTOR centre = { 0.0f,0.0f,200.0f };
	DrawSphere3D(centre, 200.0f, 5, 0xffffff, 0xffffff, true); //白

	VECTOR front = { 0.0f,0.0f,0.0f };
	DrawSphere3D(front, 100.0f, 5, 0xff0000, 0xff0000, true); //赤


	//タイトルロゴ
	DrawRotaGraph(
		Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 2 - 100,
		1.0f, 0.0, imgTitle_, true);

}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
}
