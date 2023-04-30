#pragma once
#include<string>
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

	//�R�}���h�l�[���̃Z�b�g
	void SetCmdName(std::string name);

private:

	//�����R�}���h�Z�̕`��
	Vector2 cmdPos_;		//�\�����W
	std::string cmdName_;	//�R�}���h�l�[��

	//�t�H���g
	int fontHandle_;

};

