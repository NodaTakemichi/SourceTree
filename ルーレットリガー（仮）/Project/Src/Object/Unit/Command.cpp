#include"../../_debug/_DebugConOut.h"
#include "Command.h"

Command::Command(Par* par)
{
	par_ = (*par);
}

Command::~Command()
{
}

void Command::Init(void)
{
	//振り分け
	CastCmdType(par_.type_);
	CastCmdTarget(par_.target_);
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
		TRACE("：コマンドタイプを割り振れません");
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
		TRACE("：コマンドターゲットを割り振れません\n");
	}

	return;
}
