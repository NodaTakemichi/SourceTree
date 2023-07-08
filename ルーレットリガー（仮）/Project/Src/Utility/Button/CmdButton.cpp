#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Manager/DataManager/CmdManager.h"
#include "../DrawShader.h"
#include "../AsoUtility.h"
#include "CmdButton.h"

CmdButton::CmdButton()
{
}

CmdButton::~CmdButton()
{
}

void CmdButton::Init(void)
{
	//シェーダー登録
	psOnButton_ = LoadPixelShader("./x64/Debug/OnButton.cso");
	//背面ボタン（シェーダー）


	darkness_ = 1.0f;

	fontHandle_ = CreateFontToHandle("游明朝", 12, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);
}

void CmdButton::Update(void)
{
}

void CmdButton::Draw(void)
{
	auto& ds = DrawShader::GetInstance();

	//枠
	ds.DrawExtendGraphToShader(
		pos_, size_, -1, -1, COLOR_F{}
	);

	//コマンド名座標
	Vector2 nPos = { pos_.x,pos_.y + 5 };
	nPos.x += size_.x / 2;
	nPos.x -= AsoUtility::StringLength(cmdName_, fontHandle_) / 2;
	//コマンド名
	DrawStringToHandle(
		nPos.x, nPos.y, cmdName_.c_str(), 
		GetColor(220, 220, 220), fontHandle_);
}

void CmdButton::Release(void)
{
}

void CmdButton::Create(const Vector2& pos,const Vector2& size, const int& cmdNum)
{
	//初期化
	Init();

	pos_ = pos;
	size_ = size;

	//コマンド名の取得
	cmdName_ = CmdManager::GetInstance().GetCmdData(cmdNum).name;
}

bool CmdButton::MouseOnButton(void)
{
	//マウス位置
	auto& ins = InputManager::GetInstance();
	Vector2 mPos = ins.GetMousePos();

	if (IsMouseInRect(mPos, pos_, size_))return true;


	return false;
}

void CmdButton::SetCmd(const int& cmdNum)
{
	//コマンド名の取得
	cmdName_ = CmdManager::GetInstance().GetCmdData(cmdNum).name;
}

bool CmdButton::IsMouseInRect(const Vector2& inside, const Vector2& outside, const Vector2& size)
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
