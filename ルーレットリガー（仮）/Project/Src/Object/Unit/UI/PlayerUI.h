#pragma once
#include "UnitUI.h"
class PlayerUI :
    public UnitUI
{
public:
	PlayerUI(Vector2 pos, std::string* name);
	~PlayerUI();

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

