#pragma once
#include "ButtonUI.h"
class CircleButton :
    public ButtonUI
{
public:

    CircleButton();
    ~CircleButton();

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

    //�{�^������
    void Create(Vector2 pos, int back, int front);

    //�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
    bool MouseOnButton(void);


private:
    //�{�^�����a
    int rad_;

    //�~�`���ɍ��W�����邩�̊m�F
    bool IsMouseInCircle(
        const Vector2& cPos, const Vector2& mPos, const int& rad);


};


