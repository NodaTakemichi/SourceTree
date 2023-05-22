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
	cmdName_ = std::string();
	cmdPos_ = { 750,190 };

	//文章表示座標
	cPos_ = { 350,610 };


	//フォントの変更
	fontHandle_ = CreateFontToHandle("ＭＳ 明朝", 30, 20, -1);

	//コメント窓
	commentWindowImg_ = LoadGraph("./Data/Image/UI/コメントフレーム.png");

}

void GameUI::Update(void)
{
}

void GameUI::Draw(void)
{
	auto sy = Application::SCREEN_SIZE_Y;

	//コメント窓
	DrawGraph(0, sy - 130, commentWindowImg_, true);
	//文章
	DrawTriangle(
		cPos_.x, cPos_.y,
		cPos_.x + 20, cPos_.y + 10,
		cPos_.x, cPos_.y + 20,
		0xffffff, true);

	Vector2 cPos = { cPos_.x + 30,cPos_.y };
	int num = 0;
	for (auto& cmt : cmts_)
	{
		//getdrawstringsize
		DrawStringToHandle(
			cPos.x, cPos.y + num * 20,
			cmt.c_str(), fontHandle_, 0xffffff);
		num++;
	}



}

void GameUI::DrawActivSkill(void)
{

	auto name = cmdName_.c_str();		//文字
	auto len = GetStringLength(name);	//文字数
	//幅、高さ、行数
	int sizeX, sizeY, lineCnt;
	GetDrawStringSizeToHandle(
		&sizeX, &sizeY, &lineCnt, name, -1, fontHandle_);

	//枠
	auto diff = 5;
	DrawBox(
		cmdPos_.x - diff, cmdPos_.y - diff,
		cmdPos_.x + sizeX + diff, cmdPos_.y + sizeY + diff,
		0xffffff, true);
	DrawBox(
		cmdPos_.x, cmdPos_.y,
		cmdPos_.x + sizeX, cmdPos_.y + sizeY,
		0x0, true);

	//コマンドネーム
	auto sDiff = 5;
	DrawString(cmdPos_.x + sDiff, cmdPos_.y + sDiff, cmdName_.c_str(), 0xffffff);


}


void GameUI::Release(void)
{
	DeleteFontToHandle(fontHandle_);
	DeleteGraph(commentWindowImg_);

}

void GameUI::SetCmdName(std::string name)
{
	cmdName_ = name;
}

void GameUI::AddCommentary(std::string cmt)
{
	//文章の追加
	cmts_.push_back(cmt);

}
