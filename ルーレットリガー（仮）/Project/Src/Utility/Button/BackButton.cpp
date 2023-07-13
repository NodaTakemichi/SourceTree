#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Utility/DrawShader.h"
#include "../AsoUtility.h"
#include "BackButton.h"

BackButton::BackButton()
{
}

BackButton::~BackButton()
{
}

void BackButton::Init(void)
{
    //�摜�̓o�^
    backImg_ = LoadGraph("Data/Image/UI/BackBtn.png");

    //�V�F�[�_�[�o�^
    psOnButton_ = LoadPixelShader("./x64/Debug/OnCircleButton.cso");

    darkness_ = 1.0f;
}

void BackButton::Update(void)
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

void BackButton::Draw(void)
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
}

void BackButton::Release(void)
{
    DeleteGraph(backImg_);

    DeleteShader(psOnButton_);
}

void BackButton::Create(Vector2 centerPos)
{
    //������
    Init();

    center_ = centerPos;

    int x, y;
    GetGraphSize(backImg_, &x, &y);
    rad_ = x / 2;

    //�\���ʒu�𔼌a�����炷
    pos_ = { center_.x - rad_,center_.y - rad_ };

}

bool BackButton::MouseOnButton(void)
{
    //�}�E�X�ʒu
    Vector2 mPos = InputManager::GetInstance().GetMousePos();

    if (IsMouseInCircle(center_, mPos, rad_))return true;

    return false;
}


bool BackButton::IsMouseInCircle(const Vector2& cPos, const Vector2& mPos, const int& rad)
{
    //���a
    int dis = static_cast<int>(AsoUtility::Distance(cPos, mPos));
    if (dis < rad)
    {
        return true;
    }

    return false;
}
