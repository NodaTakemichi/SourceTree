#include <DxLib.h>
#include "GameUI.h"

GameUI::GameUI()
{
}

GameUI::~GameUI()
{
}

void GameUI::Init(void)
{
	cmdName_ = std::string();
	cmdPos_ = { 650,350 };

	//�t�H���g�̕ύX
	fontHandle_ = CreateFontToHandle("�l�r ����", 30, 20, -1);

}

void GameUI::Update(void)
{
}

void GameUI::Draw(void)
{
	
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
}

void GameUI::SetCmdName(std::string name)
{
	cmdName_ = name;
}
