#pragma once
#include "ButtonUI.h"
class RectButton :
    public ButtonUI
{
public:

    RectButton();
    ~RectButton();

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

    //ボタン生成
    void Create(Vector2 pos, Vector2 size, int back, int front);

    //ボタンの上にマウスが乗っているかどうか
    bool MouseOnButton(void);


private:
    //ボタンサイズ
    Vector2 size_;

    //四角形上にマウスがあるかの確認
    bool IsMouseInRect(
        const Vector2& inside, const Vector2& outside, const Vector2& size);


};

