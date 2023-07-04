#include"../../../Manager/DataManager/CmdManager.h"
#include"../../../_debug/_DebugConOut.h"
#include "Command.h"


Command::Command(const int& num):num_(num)
{
}

Command::~Command()
{
}

void Command::Init(void)
{
	//�R�}���h�̏��̎擾
	auto test = CmdManager::GetInstance().GetCmdData(num_);

	//Par& p = Par{
	//	test.name,
	//	test.type,
	//	test.target,
	//	test.times,
	//	test.buff,
	//	test.efNum
	//};
	//par_ = p;

	par_.name_ = test.name;
	par_.type_ = test.type;
	par_.target_ = test.target;
	par_.times_ = test.times;
	par_.buff_ = test.buff;
	par_.efNum_ = test.efNum;

	//�U�蕪��
	CastCmdType(par_.type_);
	CastCmdTarget(par_.target_);
	CastCmdBuff(par_.buff_);
}

void Command::Release(void)
{
}

void Command::CastCmdType(std::string type)
{
	if (type == "MISS")			type_ = CMD_TYPE::MISS;
	else if (type == "ATTACK")	type_ = CMD_TYPE::ATTACK;
	else if (type == "HEAL")	type_ = CMD_TYPE::HEAL;
	else if (type == "BUFF")	type_ = CMD_TYPE::BUFF;
	else if (type == "CMD_UP")	type_ = CMD_TYPE::CMD_UP;
	else
	{
		TRACE(type.c_str());
		TRACE("�F�R�}���h�^�C�v������U��܂���");
	}

	return;
}

void Command::CastCmdTarget(std::string target)
{
	if (target == "NONE")			target_ = CMD_TARGET::NONE;
	else if (target == "ENEMY")		target_ = CMD_TARGET::ENEMY;
	else if (target == "ENEMY_ALL")	target_ = CMD_TARGET::ENEMY_ALL;
	else if (target == "ENEMY_RAND")target_ = CMD_TARGET::ENEMY_RAND;
	else if (target == "SELF")		target_ = CMD_TARGET::SELF;
	else if (target == "PLAYER")	target_ = CMD_TARGET::PLAYER;
	else if (target == "PLAYER_ALL")target_ = CMD_TARGET::PLAYER_ALL;
	else
	{
		
		TRACE(target.c_str());
		TRACE("�F�R�}���h�^�[�Q�b�g������U��܂���\n");
	}

	return;
}

void Command::CastCmdBuff(std::string buff)
{
	if (buff == "NONE")				buff_ = Buff::BUFF_TYPE::NONE;
	else if (buff == "PALALYSIS")	buff_ = Buff::BUFF_TYPE::PALALYSIS;
	else if (buff == "POISON")		buff_ = Buff::BUFF_TYPE::POISON;
	else if (buff == "CONFUSION")	buff_ = Buff::BUFF_TYPE::CONFUSION;
	else if (buff == "AVOIDANCE")	buff_ = Buff::BUFF_TYPE::AVOIDANCE;

	else if (buff == "P_UP")	buff_ = Buff::BUFF_TYPE::A_UP;
	else if (buff == "P_DOWN")	buff_ = Buff::BUFF_TYPE::A_DOWN;
	else if (buff == "S_UP")	buff_ = Buff::BUFF_TYPE::S_UP;
	else if (buff == "S_DOWN")	buff_ = Buff::BUFF_TYPE::S_DOWN;
	else if (buff == "D_UP")	buff_ = Buff::BUFF_TYPE::D_UP;
	else if (buff == "D_DOWN")	buff_ = Buff::BUFF_TYPE::D_DOWN;

	else if (buff == "CMD_BAN")	buff_ = Buff::BUFF_TYPE::CMD_BAN;

	else
	{

		TRACE(buff.c_str());
		TRACE("�F�o�t������U��܂���\n");
	}

	return;
}
