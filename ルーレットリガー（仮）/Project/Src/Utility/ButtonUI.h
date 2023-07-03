#pragma once
#include"../Common/Vector2.h"
class ButtonUI
{
public:
	ButtonUI();
	~ButtonUI();

	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	//ボタン生成
	void Create(Vector2 pos, Vector2 size, int back, int front);

	//クリック判定
	bool PushButton(void);

	//決定（ボタンから離したとき）
	bool ButtonDecision(void);

private:

	//座標
	Vector2 pos_;
	//ボタンサイズ
	Vector2 size_;

	//背面画像
	int backImg_;
	//手前画像
	int frontImg_;
	
	//ボタン画像シェーダー
	int buttonPs_;
	//シェーダー
	int psOnButton_;

	
	//ボタンフレームの濃さ
	float darkness_;

	//ボタンの上にマウスが乗っているかどうか
	bool onButton_;

	//ボタンの上にマウスが乗っているかどうか
	bool MouseOnButton(void);
	//四角形上に座標があるかの確認
	bool IsMouseInRect(
		const Vector2& inside,const Vector2& outside,const Vector2& size);
};

