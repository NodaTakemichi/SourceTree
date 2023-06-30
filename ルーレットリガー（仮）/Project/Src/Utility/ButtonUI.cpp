#include <DxLib.h>
#include "../Manager/InputManager.h"
#include "../Utility/DrawShader.h"
#include "ButtonUI.h"

ButtonUI::ButtonUI()
{
}

ButtonUI::~ButtonUI()
{
}

void ButtonUI::Init(void)
{
	//�V�F�[�_�[�o�^
	psTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");

	buttonPs_ = psTex_;
}

void ButtonUI::Update(void)
{
	//�}�E�X���{�^����ɂ��邩�m�F
	OnButton();
}

void ButtonUI::Draw(void)
{
	auto& ds = DrawShader::GetInstance();

	//�w�ʉ摜
	ds.DrawGraphToShader(
		pos_, backImg_, buttonPs_);

	//��O�摜
	ds.DrawGraphToShader(
		pos_, frontImg_, psTex_);

}

void ButtonUI::Release(void)
{
}

void ButtonUI::Create(Vector2 pos, Vector2 size, int back, int front)
{
	//������
	Init();

	pos_ = pos;
	//size_ = size;
	backImg_ = back;
	frontImg_ = front;

	GetGraphSize(back, &size_.x, &size_.y);

}

bool ButtonUI::PushButton(void)
{
	auto& ins = InputManager::GetInstance();
	if (OnButton() && ins.IsClickMouseLeft())
	{
		return true;
	}

	return false;
}

bool ButtonUI::OnButton(void)
{
	//�}�E�X�ʒu
	auto& ins = InputManager::GetInstance();
	Vector2 mPos = ins.GetMousePos();

	if (IsMouseInRect(mPos, pos_, size_))return true;

	return false;
}

bool ButtonUI::IsMouseInRect(
	const Vector2& inside, const Vector2& outside, const Vector2& size)
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

