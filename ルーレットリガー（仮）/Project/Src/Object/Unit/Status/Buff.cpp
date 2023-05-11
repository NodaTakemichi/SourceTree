#include "Buff.h"

Buff::Buff(const BUFF_TYPE& buff)
{
	buff_ = buff;
}

Buff::~Buff()
{
}

void Buff::Init(void)
{
	GiveBuff(buff_);
	isAlive_ = true;
}

void Buff::Release(void)
{
}

void Buff::GiveBuff(const BUFF_TYPE& type)
{
	//�o�t�̕t�^
	//�o�t�̎����^�[��
	int turn = 0;
	switch (type)
	{
	case Buff::BUFF_TYPE::PALALYSIS:
	case Buff::BUFF_TYPE::AVOIDANCE:
		turn = 1;
		break;
	default:
		turn = 3;
		break;
	}


	//�f�[�^���
	turn_ = turn;
}

bool Buff::CheckOwnBuff(const BUFF_TYPE& type)
{
	//�ړ��Ẵo�t�����L���Ă����ꍇ�Atrue��Ԃ�
	if (buff_ == type)return true;

	return false;
}

bool Buff::DecBuffTurn(void)
{
	turn_--;
	if (turn_ <= 0)return true;
	return false;
}
