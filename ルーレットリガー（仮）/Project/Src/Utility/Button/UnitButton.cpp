#include <DxLib.h>
#include "../../Manager/DataManager/UnitDataManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/InputManager.h"
#include "../../Utility/DrawShader.h"
#include "UnitButton.h"

UnitButton::UnitButton()
{
}

UnitButton::~UnitButton()
{
}

void UnitButton::Init(void)
{

	//�t�H���g�̓o�^
	fontHandle_ = CreateFontToHandle("������", 14, 20,
		DX_FONTTYPE_ANTIALIASING_4X4);

	//�t���[���V�F�[�_�[
	psCardFrame_ = LoadPixelShader("./x64/Debug/CardFrame.cso");

	//�t���[���J���[
	fColor_ = COLOR_F(0.7f, 0.7f, 0.7f, 1.0f);
}

void UnitButton::Update(void)
{
	//�{�^���𗣂���
	if (ButtonDecision())
	{
		return;
	}

	//�{�^��������
	if (PushButton())
	{
		fColor_ = COLOR_F(1.0f, 0.4f, 0.0f, 1.0f);
		return;
	}

	//�}�E�X���{�^����ɂ���
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

	//�J�[�h�g
	int offset = 10;
	Vector2 framePos = { pos_.x - offset / 2,pos_.y - offset / 2 };
	Vector2 frameSize = { size_.x + offset,size_.y + offset };
	COLOR_F buf = COLOR_F{ totalTime };
	ds.DrawExtendGraphToShader(framePos, frameSize, -1, psCardFrame_, fColor_, buf);

	//�w�ʉ摜
	DrawGraph(pos_.x, pos_.y, backImg_, true);

	//���j�b�g
	ds.DrawExtendGraphToShader({ pos_.x,pos_.y+20 }, { size_.x,size_.x }, unitImg_);

	//���O����
	int center = pos_.x + size_.x / 2;
	//���O�@������
	auto n = name_.c_str();
	//������̕������̎擾
	int len = strlen(n);
	//������́i�����́j�������擾
	center -= GetDrawStringWidthToHandle(n, len, fontHandle_) / 2;
	DrawStringToHandle(center, pos_.y + 150, name_.c_str(), 0x111111, fontHandle_);
}

void UnitButton::Release(void)
{
}

void UnitButton::Create(Vector2 pos, int back, UnitData unit)
{
	//������
	Init();

	pos_ = pos;
	backImg_ = back;
	GetGraphSize(backImg_, &size_.x, &size_.y);

	//�摜
	unitImg_ = unit.imgHandle;
	//���O
	name_ = unit.name;
}

bool UnitButton::MouseOnButton(void)
{
	//�}�E�X�ʒu
	auto& ins = InputManager::GetInstance();
	Vector2 mPos = ins.GetMousePos();

	if (IsMouseInRect(mPos, pos_, size_))return true;


	return false;
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
