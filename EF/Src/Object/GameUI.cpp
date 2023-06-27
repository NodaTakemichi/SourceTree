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
	cmdName_ = "";
	cmdPos_ = { 750,190 };

	//���݃^�[���̕���
	turnString_ = "";


	//�t�H���g�̓o�^
	turnFotnHandle_ = CreateFontToHandle("���b����", 28, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 1);

	cmdFontHandle_ = CreateFontToHandle("Noto Serif JP Medium", 18, -1,
		DX_FONTTYPE_ANTIALIASING_EDGE, -1, 1);

}

void GameUI::Update(void)
{
}

void GameUI::Draw(void)
{
	//���݃^�[����\��
 	auto n = turnString_.c_str();
	//���A�����A�s��
	int sizeX, sizeY, lineCnt;
	GetDrawStringSizeToHandle(
		&sizeX, &sizeY, &lineCnt, n, -1, turnFotnHandle_);

	auto fx = sizeX / 2;
	auto wx = Application::SCREEN_SIZE_X / 2;
	DrawStringToHandle(
		wx - fx, 30, n, turnCol_, turnFotnHandle_, 0xffffff);
	DrawStringToHandle(
		610, 30, "\n�̃^�[��", 0xffffff, turnFotnHandle_, 0x555555);

}

void GameUI::DrawActivSkill(void)
{

	auto name = cmdName_.c_str();		//����
	auto len = GetStringLength(name);	//������
	//���A�����A�s��
	int sizeX, sizeY, lineCnt;
	GetDrawStringSizeToHandle(
		&sizeX, &sizeY, &lineCnt, name, -1, cmdFontHandle_);

	//�g
	auto diff = 3;
	DrawBox(
		cmdPos_.x - diff, 
		cmdPos_.y - diff,
		cmdPos_.x + sizeX + diff * 2 + 5, 
		cmdPos_.y + sizeY + diff * 2 + 5,
		0xffffff, true);
	//�w�i
	DrawBox(
		cmdPos_.x, 
		cmdPos_.y,
		cmdPos_.x + sizeX + diff + 5, 
		cmdPos_.y + sizeY + diff + 5,
		0x0, true);

	//�R�}���h�l�[��
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


