#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Utility/DrawShader.h"
#include "../AsoUtility.h"
#include "CircleButton.h"

CircleButton::CircleButton()
{
}

CircleButton::~CircleButton()
{
}

void CircleButton::Init(void)
{
    //�V�F�[�_�[�o�^
    psOnButton_ = LoadPixelShader("./x64/Debug/OnCircleButton.cso");

    darkness_ = 1.0f;

}

void CircleButton::Update(void)
{
    //�}�E�X���{�^����ɂ��邩�m�F
    if (MouseOnButton())
    {
        darkness_ = 2.0f;
    }

    //�{�^�����N���b�N���ꂽ���m�F
    if (PushButton())
    {
        darkness_ = 1.0f;
    }
}

void CircleButton::Draw(void)
{
    auto& ds = DrawShader::GetInstance();

    //�w�ʉ摜
    if (!MouseOnButton())
    {
        DrawGraph(pos_.x, pos_.y, backImg_, true);
        //ds.DrawGraph(pos_, backImg_);
    }
    else
    {
        COLOR_F buf = COLOR_F{
            darkness_
        };
        ds.DrawGraphToShader(
            pos_, backImg_, psOnButton_, buf);
    }

    //��O�摜
    ds.DrawGraph(pos_, frontImg_);

}

void CircleButton::Release(void)
{
    DeleteShader(psOnButton_);
}

void CircleButton::Create(Vector2 center,int back, int front)
{
    //������
    Init();

    center_ = center;
    backImg_ = back;
    frontImg_ = front;

    int x, y;
    GetGraphSize(back, &x, &y);
    rad_ = x / 2;

    //�\���ʒu�ɂ��炷
    pos_ = { center_.x - rad_,center_.y - rad_ };

}

bool CircleButton::MouseOnButton(void)
{
    //�}�E�X�ʒu
    Vector2 mPos = InputManager::GetInstance().GetMousePos();

    if (IsMouseInCircle(center_, mPos,  rad_))return true;

    return false;
}


bool CircleButton::IsMouseInCircle(const Vector2& cPos, const Vector2& mPos, const int& rad)
{
    //���a
    int dis = static_cast<int>(AsoUtility::Distance(cPos, mPos));
    if (dis < rad)
    {
        return true;
    }

    return false;
}
