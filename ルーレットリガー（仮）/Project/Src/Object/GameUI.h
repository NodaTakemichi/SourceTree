#pragma once
#include<string>
#include"../Common/Vector2.h"
class GameUI
{
public:
	GameUI();
	~GameUI();

	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawActivSkill(void);	//発動技の表示
	void Release(void);

	//コマンドネームのセット
	void SetCmdName(std::string name);

private:

	//発動コマンド技の描画
	Vector2 cmdPos_;		//表示座標
	std::string cmdName_;	//コマンドネーム

	//フォント
	int fontHandle_;

};

