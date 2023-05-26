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
	//行動中のユニットの表示
	void DrawActUnit(void)override;
	//ロックオン
	void DrawRockOn(void)override;

};

