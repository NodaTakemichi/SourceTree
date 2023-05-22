#pragma once
#include<string>
#include<vector>
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

	//コマンド名のセット
	void SetCmdName(std::string name);

	//文章追加
	void AddCommentary(std::string cmt);

private:


	//発動コマンド技の描画
	Vector2 cmdPos_;		//表示座標
	std::string cmdName_;	//コマンドネーム

	//フォント
	int fontHandle_;

	//コメント窓
	int commentWindowImg_;

	//文章表示座標
	Vector2 cPos_;
	//文章
	std::vector<std::string>cmts_;

};

