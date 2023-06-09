#include <DxLib.h>
#include "../../Manager/DataManager/UnitDataManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../DrawShader.h"
#include "../AsoUtility.h"
#include "UnitButton.h"

UnitButton::UnitButton()
{
}

UnitButton::~UnitButton()
{
}

void UnitButton::Init(void)
{

	//フォントの登録
	fontHandle_ = CreateFontToHandle("游明朝", 10, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);

	//フレームシェーダー
	psCardFrame_ = LoadPixelShader("./x64/Debug/CardFrame.cso");

	//フレームカラー
	fColor_ = COLOR_F(0.7f, 0.7f, 0.7f, 1.0f);
}

void UnitButton::Update(void)
{
	//ボタンを離した
	if (ButtonDecision())
	{
		return;
	}

	//ボタン押下中
	if (PushButton())
	{
		fColor_ = COLOR_F(1.0f, 0.4f, 0.0f, 1.0f);
		return;
	}

	//マウスがボタン上にある
	if (MouseOnButton())
	{
		fColor_ = COLOR_F(1.0f, 1.0f, 0.0f, 1.0f);
		return;
	}

	fColor_ = COLOR_F(0.7f, 0.7f, 0.7f, 1.0f);
	return;


}

void UnitButton::Draw(void)
{
	auto& ds = DrawShader::GetInstance();
	auto totalTime = SceneManager::GetInstance().GetTotalTime();

	//カード枠
	int offset = 10;
	Vector2 framePos = { pos_.x - offset / 2,pos_.y - offset / 2 };
	Vector2 frameSize = { size_.x + offset,size_.y + offset };
	COLOR_F buf = COLOR_F{ totalTime };
	ds.DrawExtendGraphToShader(framePos, frameSize, -1, psCardFrame_, fColor_, buf);

	//背面画像
	DrawGraph(pos_.x, pos_.y, backImg_, true);

	//ユニット
	ds.DrawExtendGraphToShader({ pos_.x,pos_.y+20 }, { size_.x,size_.x }, unitImg_);



	//中心位置
	int center = pos_.x + size_.x / 2;
	//文字列の（半分の）長さを取得
	center -= AsoUtility::StringLength(name_, fontHandle_) / 2;
	DrawStringToHandle(center, pos_.y + 150, name_.c_str(), 0x111111, fontHandle_);
}

void UnitButton::Release(void)
{
	DeleteFontToHandle(fontHandle_);

	DeleteShader(psCardFrame_);
}

void UnitButton::Create(Vector2 pos, int back, UnitData unit)
{
	//初期化
	Init();

	pos_ = pos;
	backImg_ = back;
	GetGraphSize(backImg_, &size_.x, &size_.y);

	//画像
	unitImg_ = unit.imgHandle;
	//名前
	name_ = unit.name;
}

bool UnitButton::MouseOnButton(void)
{
	//マウス位置
	auto& ins = InputManager::GetInstance();
	Vector2 mPos = ins.GetMousePos();

	if (IsMouseInRect(mPos, pos_, size_))return true;


	return false;
}

void UnitButton::ChengeUnitData(const UnitData& data)
{
	//画像
	unitImg_ = data.imgHandle;
	//名前
	name_ = data.name;
}

bool UnitButton::IsMouseInRect(const Vector2& inside, const Vector2& outside, const Vector2& size)
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
