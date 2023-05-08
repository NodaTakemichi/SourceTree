#pragma once
#include<vector>
#include<string>
#include"./Buff.h"
class Command
{
public:

	//�Z�̃^�C�v
	enum class CMD_TYPE
	{
		NONE = 0, 
		MISS,
		ATTACK,
		HEAL,
		BUFF,
		CMD_UP,
		END
	};


	//�Z�̑Ώ�
	enum class CMD_TARGET
	{
		NONE = 0,
		ENEMY,
		ENEMY_ALL,
		ENEMY_RAND,
		SELF,
		PLAYER,
		PLAYER_ALL,
		END
	};

	struct Par
	{
		//�R�}���h��
		std::string name_;
		//�R�}���h�^�C�v(�L���X�g�O)
		std::string type_;
		//�^�[�Q�b�g(�L���X�g�O)
		std::string target_;
	
		//�Z�F�{��
		float times_;

		//�o�t�^�C�v(�L���X�g�O)
		std::string buff_;
	};

	Command(Par* par);
	~Command();

	void Init(void);
	//void Update(void);
	//void Draw(void);
	void Release(void);

	//���O�̎擾
	const std::string& GetName(void) { return par_.name_; }

	//�{���̎擾
	const float& GetTimes(void) { return par_.times_; }

	//�R�}���h�^�C�v�̎擾
	const CMD_TYPE& GetCmdType(void) { return type_; }

	//�^�[�Q�b�g�̎擾
	const CMD_TARGET& GetCmdTarget(void) { return target_; }

	//�o�t�̃^�C�v�̎擾
	const Buff::BUFF_TYPE& GetCmdBuff(void) { return buff_; }

private:
	//���
	Par par_;

	//�R�}���h�^�C�v
	CMD_TYPE type_;

	//�^�[�Q�b�g
	CMD_TARGET target_;

	//�^�[�Q�b�g
	Buff::BUFF_TYPE buff_;


	//�X�L���^�C�v�A�^�[�Q�b�g�A�o�t�^�C�v���L���X�g����
	void CastCmdType(std::string type);
	void CastCmdTarget(std::string target);
	void CastCmdBuff(std::string buff);




};

