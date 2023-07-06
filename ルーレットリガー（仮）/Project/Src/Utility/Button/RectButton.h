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

    //�{�^������
    void Create(Vector2 pos, Vector2 size, int back, int front);

    //�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
    bool MouseOnButton(void);


private:
    //�{�^���T�C�Y
    Vector2 size_;

    //�l�p�`��Ƀ}�E�X�����邩�̊m�F
    bool IsMouseInRect(
        const Vector2& inside, const Vector2& outside, const Vector2& size);


};

