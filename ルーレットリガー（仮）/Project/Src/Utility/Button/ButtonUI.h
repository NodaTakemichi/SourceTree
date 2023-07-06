#pragma once
#include"../../Common/Vector2.h"
class ButtonUI
{
public:
	ButtonUI();
	~ButtonUI();

	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;



	//ボタンの上にマウスが乗っているかどうか
	virtual bool MouseOnButton(void) = 0;
	//クリック判定
	bool PushButton(void);
	//決定（ボタンから離したとき）
	bool ButtonDecision(void);

protected:

	//座標
	Vector2 pos_;

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


private:

};

