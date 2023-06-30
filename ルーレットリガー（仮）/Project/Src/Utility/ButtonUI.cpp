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
	//シェーダー登録
	psTex_ = LoadPixelShader("./x64/Debug/ReverseTexture.cso");

	buttonPs_ = psTex_;
}

void ButtonUI::Update(void)
{
	//マウスがボタン上にあるか確認
	OnButton();
}

void ButtonUI::Draw(void)
{
	auto& ds = DrawShader::GetInstance();

	//背面画像
	ds.DrawGraphToShader(
		pos_, backImg_, buttonPs_);

	//手前画像
	ds.DrawGraphToShader(
		pos_, frontImg_, psTex_);

}

void ButtonUI::Release(void)
{
}

void ButtonUI::Create(Vector2 pos, Vector2 size, int back, int front)
{
	//初期化
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
	//マウス位置
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

