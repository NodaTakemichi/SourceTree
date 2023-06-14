#include<DxLib.h>
#include<math.h>
#include"../Application.h"
#include"../Utility/AsoUtility.h"
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"

#include"./Unit/Status/Command.h"

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
	angle = 0.0;
	ResetRouSpin();

	//�摜�o�^
	arrowImg_ = LoadGraph("./Data/Image/UI/arrow.png");
	rouletteImg_ = LoadGraph("./Data/Image/UI/roulette.png");
	rouFrame_ = LoadGraph("./Data/Image/UI/RouFrame.png");
	center_ = LoadGraph("./Data/Image/UI/center.png");

	//�t�H���g�̕ύX
	//fontHandle_=CreateFontToHandle("@�l�r ����", 22, 10, -1);
	fontHandle_=CreateFontToHandle("@Noto Serif JP Medium", 22, 10, -1);

}

void Roulette::Update(void)
{
	//���[���b�g�̉�]����
	RotateProcess();
}

void Roulette::Draw(void)
{
	int cx = Application::SCREEN_SIZE_X;
	int cy = Application::SCREEN_SIZE_Y;


	//���`��
	DrawGraph(cx / 2-50, 150.0f, arrowImg_, true);

	int rouPosX = cx / 2;
	int rouPosY = 530;


	//���[���b�g�g�`��
	int x, y;
	GetGraphSize(rouFrame_, &x, &y);
	DrawGraph(rouPosX-x/2, rouPosY-y/2, rouFrame_, true);

	//�o�C���j�A��ԃ��[�h
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	//���[���b�g�`��
	DrawRotaGraph(rouPosX, rouPosY,
		1.0f, AsoUtility::Deg2RadF(angle), rouletteImg_, true, false);

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
			190.0, 10.0,			//��]�̒��S���W�i���΍��W�j
			AsoUtility::Deg2RadF(angle) + (i * rotSpan) + rotReltive,	//�p�x
			0x220022, fontHandle_, 0x0,	//�t�H���g
			true, name);

		//�p�x�����炷
		i++;
	}


	//�l�A���X�g�l�C�o�[�@
	SetDrawMode(DX_DRAWMODE_NEAREST);

	//���[���b�g����
	GetGraphSize(center_, &x, &y);
	DrawGraph(rouPosX - x / 2, rouPosY - y / 2, center_, true);

}

void Roulette::Release(void)
{
	DeleteGraph(arrowImg_);
	DeleteGraph(rouletteImg_);

	cmdNames_.clear();

	//�쐬�����t�H���g�n���h���̍폜
	DeleteFontToHandle(fontHandle_);
}

void Roulette::StopRoulette(const bool& autom)
{
	if (!isRouSpin_)return;		//���Ƀu���[�L��ԂȂ�A���������Ȃ�

	bool stop = false;
	//�蓮�����������f����
	if (autom)
	{
		//���Ԃ�������u���[�L��Ԃɂ���
		stop = AsoUtility::OverTime(totalTime_, STOP_WAIT_TIME_ROU);
	}
	else
	{
		//���N���b�N���m���A�u���[�L��Ԃɂ���
		auto& ins = InputManager::GetInstance();
		stop = ins.IsTrgMouseLeft();
	}

	if (stop)isRouSpin_ = false;
}

void Roulette::SetCommand(std::vector<Command*> cmd)
{
	cmdNames_ = cmd;
}

void Roulette::ResetRouSpin(void)
{
	//angle = 0.0;		//���[���b�g�̉�]��Ԃ�߂��Ȃ�
	rotPower_ = 0.0;
	isStop_ = false;
	isRouSpin_ = true;
	totalTime_ = 0.0f;
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
		//�p�x�̈ȉ��ȏ�
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
	//��~�܂ł̃u���[�L��
	const float stopSpeed = -ROT_SPEED_MAX / ROT_BRAKE;

	float brake = AsoUtility::Lerp(
		static_cast<float>(rotPower_), 0.0f, 0.1f)*-1.0f;

	//��]�ʂ̌v�Z�i��]���u���[�L�ő��x�ύX�j
	//��]��ԁF�ō����x�A�u���[�L��ԁF���������l
	rotPower_ = isRouSpin_ ? ROT_SPEED_MAX : rotPower_ + stopSpeed;



	//��~��Ԃ����f
	if (rotPower_ < 0.1f)
	{
		//��]�ʂ�������
		angle += rotPower_;
	}
	else
	{
		//���[���b�g��~��Ԃɂ���
		isStop_ = true;
	}

}
