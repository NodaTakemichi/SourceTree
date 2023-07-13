#pragma once
#include "ButtonUI.h"
class BackButton :
    public ButtonUI
{
    BackButton();
    ~BackButton();

    void Init(void)override;
    void Update(void)override;
    void Draw(void)override;
    void Release(void)override;

    //�{�^������
    void Create(Vector2 centerPos);

    //�{�^���̏�Ƀ}�E�X������Ă��邩�ǂ���
    bool MouseOnButton(void);


private:
    //���S���W
    Vector2 center_;

    //�{�^�����a
    int rad_;

    //�~�`���ɍ��W�����邩�̊m�F
    bool IsMouseInCircle(
        const Vector2& cPos, const Vector2& mPos, const int& rad);


};

