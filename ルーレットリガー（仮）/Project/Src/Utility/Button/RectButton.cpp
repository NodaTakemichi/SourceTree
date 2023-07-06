#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Utility/DrawShader.h"
#include "RectButton.h"

RectButton::RectButton()
{
}

RectButton::~RectButton()
{
}

void RectButton::Init(void)
{
	//�V�F�[�_�[�o�^
	psOnButton_ = LoadPixelShader("./x64/Debug/OnButton.cso");

	darkness_ = 1.0f;

}

void RectButton::Update(void)
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

void RectButton::Draw(void)
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
	//ds.DrawGraphToShader(
	//	pos_, frontImg_, psTex_);

}

void RectButton::Release(void)
{
	DeleteShader(psOnButton_);

}

void RectButton::Create(Vector2 pos, Vector2 size, int back, int front)
{
	//������
	Init();

	pos_ = pos;
	//size_ = size;
	backImg_ = back;
	frontImg_ = front;

	GetGraphSize(back, &size_.x, &size_.y);

}

bool RectButton::MouseOnButton(void)
{
	//�}�E�X�ʒu
	auto& ins = InputManager::GetInstance();
	Vector2 mPos = ins.GetMousePos();

	if (IsMouseInRect(mPos, pos_, size_))return true;


	return false;
}

bool RectButton::IsMouseInRect(const Vector2& inside, const Vector2& outside, const Vector2& size)
{
	if (
		inside.x > outside.x &&
		inside.x < outside.x + size.x &&
		inside.y > outside.y &&
		inside.y < outside.y + size.y
		)
	{
		return true;
	}

	return false;
}
