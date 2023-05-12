#include "Buff.h"

Buff::Buff()
{
}

Buff::~Buff()
{
}

void Buff::Init(void)
{
	CheckBuffTurn(buff_);
	isAlive_ = true;
}

void Buff::Release(void)
{
}

void Buff::CreateBuff(const BUFF_TYPE& buff)
{
	buff_ = buff;
	CheckBuffTurn(buff_);
	isAlive_ = true;
}

void Buff::CheckBuffTurn(const BUFF_TYPE& type)
{
	//�o�t�̕t�^
	//�o�t�̎����^�[��
	int turn = 0;
	switch (type)
	{
	case Buff::BUFF_TYPE::PALALYSIS:
		turn = 1;
		break;
	case Buff::BUFF_TYPE::AVOIDANCE:
		turn = 2;
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
