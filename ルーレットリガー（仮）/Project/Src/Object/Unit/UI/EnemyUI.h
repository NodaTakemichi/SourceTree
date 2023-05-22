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
	//行動中のユニットの表示
	void DrawActUnit(void)override;
	//ロックオン
	void DrawRockOn(void)override;

};

