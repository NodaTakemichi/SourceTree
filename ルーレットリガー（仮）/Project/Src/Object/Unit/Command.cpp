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
	//êUÇËï™ÇØ
	CastSkillType(par_.type_);
	CastSkillTarget(par_.target_);
}

void Command::Release(void)
{
}

void Command::CastSkillType(std::string type)
{
	if (type == "MISS")type_ = SKILL_TYPE::MISS;
	else if (type == "ATTACK")type_ = SKILL_TYPE::ATTACK;
	else if (type == "HEAL")type_ = SKILL_TYPE::HEAL;
	else if (type == "BUFF")type_ = SKILL_TYPE::BUFF;
	else if (type == "CMD_UP")type_ = SKILL_TYPE::CMD_UP;

	return;
}

void Command::CastSkillTarget(std::string target)
{
	if (target == "NONE")target_ = SKILL_TARGET::NONE;
	else if (target == "ENEMY")target_ = SKILL_TARGET::ENEMY;
	else if (target == "ENEMY_ALL")target_ = SKILL_TARGET::ENEMY_ALL;
	else if (target == "ENEMY_RAND")target_ = SKILL_TARGET::ENEMY_RAND;
	else if (target == "SELF")target_ = SKILL_TARGET::SELF;
	else if (target == "PLAYER")target_ = SKILL_TARGET::PLAYER;
	else if (target == "PLAUER_ALL")target_ = SKILL_TARGET::PLAUER_ALL;

	return;
}
