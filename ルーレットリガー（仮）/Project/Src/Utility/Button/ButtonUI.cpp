#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Utility/DrawShader.h"
#include "ButtonUI.h"

ButtonUI::ButtonUI()
{
}

ButtonUI::~ButtonUI()
{
}

bool ButtonUI::PushButton(void)
{
	auto& ins = InputManager::GetInstance();
	if (MouseOnButton() && ins.IsClickMouseLeft())return true;

	return false;
}

bool ButtonUI::ButtonDecision(void)
{
	auto& ins = InputManager::GetInstance();
	if (MouseOnButton() && ins.IsTrgMouseLeftUp())return true;

	return false;
}
