#pragma once
#include<string>
#include<vector>
#include"../Common/Vector2.h"

class GameUI
{
public:
	GameUI();
	~GameUI();

	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawActivSkill(void);	//�����Z�̕\��
	void Release(void);

	//�R�}���h���̃Z�b�g
	void SetCmdName(std::string name);

	//���݃^�[���̃Z�b�g
	void SetTurnString(const std::string& name,const int& color);

private:
	//�����R�}���h�Z�̕`��
	Vector2 cmdPos_;		//�\�����W
	std::string cmdName_;	//�R�}���h�l�[��
	int cmdFontHandle_;

	//�^�[�������A�F�A�t�H���g
	std::string turnString_;
	int turnCol_;
	int turnFotnHandle_;


};

