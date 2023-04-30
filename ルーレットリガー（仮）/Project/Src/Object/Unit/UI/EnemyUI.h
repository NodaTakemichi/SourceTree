#pragma once
#include "UnitUI.h"
class EnemyUI :
    public UnitUI
{
public:
	EnemyUI(Vector2 pos, std::string* name);
	~EnemyUI();

	void Init(void);
	void Draw(void);
	void Release(void);

	//行動中のユニットの表示
	void DrawActUnit(void);

	//ロックオン
	void DrawRockOn(void);

private:
	//ユニット座標
	Vector2 unitPos_;
	//ユニットネーム
	std::string* name_;


};

