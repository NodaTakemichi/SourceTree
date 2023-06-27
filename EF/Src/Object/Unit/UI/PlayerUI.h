#pragma once
#include "UnitUI.h"
class PlayerUI :
    public UnitUI
{
public:
	PlayerUI(Vector2 pos, std::string& name, int& hp, int& nowHp, int& maxHp);
	~PlayerUI();

	void Init(void)override;
	void Draw(void)override;


private:
	//�s�����̃��j�b�g�̕\��
	void DrawActUnit(void)override;
	//���b�N�I��
	void DrawRockOn(void)override;

};

