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
	//�R�}���h��
	cmdName_ = std::string();
	cmdPos_ = { 750,190 };

	//���͕\�����W
	cPos_ = { 350,610 };


	//�t�H���g�̕ύX
	fontHandle_ = CreateFontToHandle("�l�r ����", 30, 20, -1);

	//�R�����g��
	commentWindowImg_ = LoadGraph("./Data/Image/UI/�R�����g�t���[��.png");

}

void GameUI::Update(void)
{
}

void GameUI::Draw(void)
{
	auto sy = Application::SCREEN_SIZE_Y;

	//�R�����g��
	DrawGraph(0, sy - 130, commentWindowImg_, true);
	//����
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

	auto name = cmdName_.c_str();		//����
	auto len = GetStringLength(name);	//������
	//���A�����A�s��
	int sizeX, sizeY, lineCnt;
	GetDrawStringSizeToHandle(
		&sizeX, &sizeY, &lineCnt, name, -1, fontHandle_);

	//�g
	auto diff = 5;
	DrawBox(
		cmdPos_.x - diff, cmdPos_.y - diff,
		cmdPos_.x + sizeX + diff, cmdPos_.y + sizeY + diff,
		0xffffff, true);
	DrawBox(
		cmdPos_.x, cmdPos_.y,
		cmdPos_.x + sizeX, cmdPos_.y + sizeY,
		0x0, true);

	//�R�}���h�l�[��
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
	//���͂̒ǉ�
	cmts_.push_back(cmt);

}
