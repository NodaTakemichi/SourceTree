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

	//���͒ǉ�
	void AddCommentary(std::string cmt);

private:


	//�����R�}���h�Z�̕`��
	Vector2 cmdPos_;		//�\�����W
	std::string cmdName_;	//�R�}���h�l�[��

	//�t�H���g
	int fontHandle_;

	//�R�����g��
	int commentWindowImg_;

	//���͕\�����W
	Vector2 cPos_;
	//����
	std::vector<std::string>cmts_;

};

