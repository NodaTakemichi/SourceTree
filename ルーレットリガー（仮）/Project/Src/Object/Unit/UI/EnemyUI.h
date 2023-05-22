#pragma once
#include "UnitUI.h"
class EnemyUI :
    public UnitUI
{
public:
	EnemyUI(Vector2 pos, std::string& name, int& nowHp, int& maxHp);
	~EnemyUI();

	void Init(void)override;
	void Draw(void)override;


private:
	//�s�����̃��j�b�g�̕\��
	void DrawActUnit(void)override;
	//���b�N�I��
	void DrawRockOn(void)override;

};

