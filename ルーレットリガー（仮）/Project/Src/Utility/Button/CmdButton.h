#pragma once
#include <string>
#include "ButtonUI.h"
class CmdButton :
    public ButtonUI
{
public:

    CmdButton();
    ~CmdButton();

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

    //ボタン生成
    void Create(const Vector2& pos, const Vector2& size, const int& cmdNum);

    //ボタンの上にマウスが乗っているかどうか
    bool MouseOnButton(void);

    //コマンド名の再セット
    void SetCmd(const int& cmdNum);


private:
    //ボタンサイズ
    Vector2 size_;

    //コマンド名
    std::string cmdName_;
    //フォント
    int fontHandle_;

    //四角形上にマウスがあるかの確認
    bool IsMouseInRect(
        const Vector2& inside, const Vector2& outside, const Vector2& size);

    //コマンドボタンシェーダー
    int psCmdBtn_;

};

