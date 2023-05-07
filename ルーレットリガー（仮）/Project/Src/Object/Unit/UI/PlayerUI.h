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
	//ユニット座標
	Vector2 unitPos_;
	//ユニットネーム
	std::string& name_;

	//HP
	int& hp_;
	int& maxHp_;
	int& beforHp_;

	//行動中のユニットの表示
	void DrawActUnit(void)override;
	//ロックオン
	void DrawRockOn(void)override;

};

