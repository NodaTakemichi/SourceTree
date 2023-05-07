#pragma once
#include "UnitUI.h"
class PlayerUI :
    public UnitUI
{
public:
	PlayerUI(Vector2 pos, std::string& name,int& hp,int& maxHp ,int& beforHp);
	~PlayerUI();

	void Init(void)override;
	void Draw(void)override;


private:
	//���j�b�g���W
	Vector2 unitPos_;
	//���j�b�g�l�[��
	std::string& name_;

	//HP
	int& hp_;
	int& maxHp_;
	int& beforHp_;

	//�s�����̃��j�b�g�̕\��
	void DrawActUnit(void)override;
	//���b�N�I��
	void DrawRockOn(void)override;

};

