#pragma once
#include "UnitUI.h"
class EnemyUI :
    public UnitUI
{
public:
	EnemyUI(Vector2 pos, std::string& name, int& hp, int& maxHp, int& beforHp);
	~EnemyUI();

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

