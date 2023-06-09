#include <DxLib.h>
#include "../Application.h"
#include "GameUI.h"

GameUI::GameUI()
{
}

GameUI::~GameUI()
{
}

void GameUI::Init(void)
{
	//コマンド名
	cmdName_ = "";
	cmdPos_ = { 750,190 };

	//現在ターンの文字
	turnString_ = "";


	//フォントの登録
	turnFotnHandle_ = CreateFontToHandle("装甲明朝", 28, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	cmdFontHandle_ = CreateFontToHandle("Noto Serif JP Medium", 18, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

}

void GameUI::Update(void)
{
}

void GameUI::Draw(void)
{
	//現在ターンを表示
 	auto n = turnString_.c_str();
	//幅、高さ、行数
	int sizeX, sizeY, lineCnt;
	GetDrawStringSizeToHandle(
		&sizeX, &sizeY, &lineCnt, n, -1, turnFotnHandle_);

	auto fx = sizeX / 2;
	auto wx = Application::SCREEN_SIZE_X / 2;
	DrawStringToHandle(
		wx - fx, 30, n, turnCol_, turnFotnHandle_, 0xffffff);
	DrawStringToHandle(
		610, 30, "\nのターン", 0xffffff, turnFotnHandle_, 0x555555);

}

void GameUI::DrawActivSkill(void)
{

	auto name = cmdName_.c_str();		//文字
	auto len = GetStringLength(name);	//文字数
	//幅、高さ、行数
	int sizeX, sizeY, lineCnt;
	GetDrawStringSizeToHandle(
		&sizeX, &sizeY, &lineCnt, name, -1, cmdFontHandle_);

	//枠
	auto diff = 3;
	DrawBox(
		cmdPos_.x - diff, 
		cmdPos_.y - diff,
		cmdPos_.x + sizeX + diff * 2 + 5, 
		cmdPos_.y + sizeY + diff * 2 + 5,
		0xffffff, true);
	//背景
	DrawBox(
		cmdPos_.x, 
		cmdPos_.y,
		cmdPos_.x + sizeX + diff + 5, 
		cmdPos_.y + sizeY + diff + 5,
		0x0, true);

	//コマンドネーム
	auto sDiff = 5;
	DrawStringToHandle(
		cmdPos_.x + sDiff, cmdPos_.y + sDiff, 
		cmdName_.c_str(), 0xffffff, cmdFontHandle_);


}


void GameUI::Release(void)
{
	DeleteFontToHandle(cmdFontHandle_);
	DeleteFontToHandle(turnFotnHandle_);

}

void GameUI::SetCmdName(std::string name)
{
	cmdName_ = name;
}

void GameUI::SetTurnString(const std::string& name, const int& color)
{
	turnString_ = name;
	turnCol_ = color;
}


