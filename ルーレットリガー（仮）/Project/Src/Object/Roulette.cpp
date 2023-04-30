#include<DxLib.h>
#include<math.h>
#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"

#include"./Unit/Command.h"

#include"../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"

#include "Roulette.h"

Roulette::Roulette()
{
}

Roulette::~Roulette()
{
}

void Roulette::Init(void)
{
	//������
	ResetRouSpin();

	//�摜�o�^
	arrowImg_ = LoadGraph("./Data/Image/UI/arrow.png");
	rouletteImg_ = LoadGraph("./Data/Image/UI/roulette2.png");

	//�t�H���g�̕ύX
	fontHandle_=CreateFontToHandle("@�l�r ����", 20, 10, -1);

}

void Roulette::Update(void)
{
	//�f���^�^�C��
	auto delta = SceneManager::GetInstance().GetDeltaTime();
	//mTotalTime += delta;

	//���[���b�g�̉�]����
	RotateProcess();


	auto& ins = InputManager::GetInstance();
	//���N���b�N���m
	if (ins.IsTrgMouseLeft())
	{
		isRouSpin_ = false;
	}

}

void Roulette::Draw(void)
{
	int cx = Application::SCREEN_SIZE_X;
	int cy = Application::SCREEN_SIZE_Y;

	//���`��
	DrawGraph(cx / 2-50, 200.0f, arrowImg_, true);

	int rouPosX = cx / 2;
	int rouPosY = 580;

	//�o�C���j�A��ԃ��[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//���[���b�g�`��
	DrawRotaGraph(rouPosX, rouPosY,
		1.0f, AsoUtility::Deg2RadF(angle), rouletteImg_, true, false);

	//�t�H���g�T�C�Y�̕ύX
	SetFontSize(20);

	//�e�R�}���h�Z�̉�]���A���Ή�]
	auto rotSpan = AsoUtility::Deg2RadF(
		360.0f / static_cast<float>(cmdNames_.size()));
	auto rotReltive = rotSpan / 2;

	//�R�}���h�Z�̉�]�`��
	int i = 0;
	for (auto& cmdName : cmdNames_)
	{
		auto name = cmdName->GetName().c_str();

		//�R�}���h�l�[���`��
		DrawRotaStringToHandle(
			rouPosX, rouPosY,		//���W
			1.0, 1.0,				//�g�嗦
			180.0, 10.0,			//��]�̒��S���W�i���΍��W�j
			AsoUtility::Deg2RadF(angle) + (i * rotSpan) + rotReltive,	//�p�x
			0x0, fontHandle_, 0x0,	//�t�H���g
			true, name);

		//�p�x�����炷
		i++;
	}


	//�t�H���g�T�C�Y�̕ύX
	SetFontSize(16);
	//�l�A���X�g�l�C�o�[�@
	SetDrawMode(DX_DRAWMODE_NEAREST);

}

void Roulette::Release(void)
{
	DeleteGraph(arrowImg_);
	DeleteGraph(rouletteImg_);

	cmdNames_.clear();

	//�쐬�����t�H���g�n���h���̍폜
	DeleteFontToHandle(fontHandle_);
}

void Roulette::SetCommand(std::vector<Command*> cmd)
{
	cmdNames_ = cmd;
}

void Roulette::ResetRouSpin(void)
{
	angle = 0.0;
	rotPower_ = 0.0;
	isStop_ = false;
	isRouSpin_ = true;
}

Command* Roulette::GetCmd(void)
{
	//��]��
	auto rotAmount = fmod(angle, 360.0) * -1;
	//�R�}���h�̐�
	int num = static_cast<double>(cmdNames_.size());
	//���肳�ꂽ�R�}���h�𔻕ʂ���
	double angle = 0.0;
	double onwAngle = 360.0 / num;	//����̊p�x
	//�p�x����R�}���h���擾����
	for (size_t i = 0; i <= num; i++)
	{
		if (angle < rotAmount && rotAmount <= angle + onwAngle)
		{
			//�R�}���h��Ԃ�
			return cmdNames_[i];
		}

		//�p�x�����Z
		angle += onwAngle;
	}
}

void Roulette::RotateProcess(void)
{
	//��]��Ԃ����f
	if (isRouSpin_)
	{
		//��]���x�����Z
		rotPower_ = ROT_SPEED_MAX;
	}
	else
	{
		//����
		rotPower_ += 0.2f;
	}

	//���[���b�g�̉�]���x�̔���
	if (rotPower_ < 0)
	{
		//��]
		angle += rotPower_;
	}
	else
	{
		//���[���b�g��~��Ԃɂ���
		isStop_ = true;
	}

}
