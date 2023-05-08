#include "Buff.h"

Buff::Buff()
{
}

Buff::~Buff()
{
}

void Buff::Init(void)
{
}

void Buff::Release(void)
{
}

void Buff::SetBuff(const BUFF_TYPE& type)
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
	
	//�f�[�^�}��
	BuffData data = { type,turn };
	buff_.push_back(data);
}

bool Buff::CheckOwnBuff(const BUFF_TYPE& type)
{
	//�ړ��Ẵo�t�����L���Ă����ꍇ�Atrue��Ԃ�
	for (auto& b : buff_)
	{
		if (b.type == type)return true;
	}
	return false;
}
