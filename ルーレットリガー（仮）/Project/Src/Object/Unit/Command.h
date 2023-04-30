#pragma once
#include<string>
class Command
{
public:

	//�Z�̃^�C�v
	enum class SKILL_TYPE
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
	enum class SKILL_TARGET
	{
		NONE = 0,
		ENEMY,
		ENEMY_ALL,
		ENEMY_RAND,
		SELF,
		PLAYER,
		PLAUER_ALL,
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

	//�X�L���^�C�v�̎擾
	const SKILL_TYPE& GetSkillType(void) { return type_; }

	//�^�[�Q�b�g�̎擾
	const SKILL_TARGET& GetSkillTarget(void) { return target_; }

private:
	//���
	Par par_;

	//�X�L���^�C�v
	SKILL_TYPE type_;
	//�^�[�Q�b�g
	SKILL_TARGET target_;


	//�X�L���^�C�v�A�^�[�Q�b�g���L���X�g����
	void CastSkillType(std::string type);
	void CastSkillTarget(std::string target);




};

