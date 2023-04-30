#pragma once
#include<string>
class Command
{
public:

	//技のタイプ
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

	//技の対象
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
		//コマンド名
		std::string name_;
		//コマンドタイプ(キャスト前)
		std::string type_;
		//ターゲット(キャスト前)
		std::string target_;
	
		//技：倍率
		float times_;

	};

	Command(Par* par);
	~Command();

	void Init(void);
	//void Update(void);
	//void Draw(void);
	void Release(void);

	//名前の取得
	const std::string& GetName(void) { return par_.name_; }

	//倍率の取得
	const float& GetTimes(void) { return par_.times_; }

	//スキルタイプの取得
	const SKILL_TYPE& GetSkillType(void) { return type_; }

	//ターゲットの取得
	const SKILL_TARGET& GetSkillTarget(void) { return target_; }

private:
	//情報
	Par par_;

	//スキルタイプ
	SKILL_TYPE type_;
	//ターゲット
	SKILL_TARGET target_;


	//スキルタイプ、ターゲットをキャストする
	void CastSkillType(std::string type);
	void CastSkillTarget(std::string target);




};

